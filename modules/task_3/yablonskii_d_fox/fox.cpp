// Copyright 2023 Yablonskii Dmitriy


#include "../../../modules/task_3/yablonskii_d_fox/fox.h"
#include <mpi.h>

#include <random>

namespace {
    MPI_Comm GC; MPI_Comm CC; MPI_Comm RC;

    void makingGcomms(int gs, int prank, int* gc) {
        std::vector<int> dS(2, gs);
        std::vector<int> T_per(2, 0);
        std::vector<int> sbd(2);
        MPI_Cart_create(MPI_COMM_WORLD, 2, dS.data(), T_per.data(), 0, &GC);
        MPI_Cart_coords(GC, prank, 2, gc);
        sbd[0] = 0;
        sbd[1] = 1;
        MPI_Cart_sub(GC, sbd.data(), &RC);
        sbd[0] = 1;
        sbd[1] = 0;
        MPI_Cart_sub(GC, sbd.data(), &CC);
    }

    void blockMult(double* a_Bl, double* b_Bl, double* a_b_Bl, size_t bS) {
        for (size_t i = 0; i < bS; i++) {
            for (size_t j = 0; j < bS; j++) {
                double t = 0;
                for (int k = 0; k < bS; k++) {
                    t += a_Bl[i * bS + k] * b_Bl[k * bS + j];
                }
                a_b_Bl[i * bS + j] += t;
            }
        }
    }

}  // namespace

namespace MyNs {
    std::vector<double> createmat(size_t n) {
        std::mt19937 gen(std::random_device {}());
        std::uniform_real_distribution<> distr(-100, 100);
        std::vector<double> vector(n * n);
        for (size_t i = 0; i < n * n; i++) {
            vector[i] = distr(gen);
        }

        return vector;
    }

    std::vector<double> normOp(const std::vector<double>& a, const std::vector<double>& b, size_t n) {
        if (a.n() != b.n()) {
            throw "ERROR";
        }

        std::vector<double> ab(n * n, 0);
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                for (size_t k = 0; k < n; k++) {
                    ab[i * n + j] += a[i * n + k] * b[k * n + j];
                }
            }
        }

        return ab;
    }

    std::vector<double> opfox(std::vector<double> a, std::vector<double> b, size_t n) {
        int Nummpc, Rankkpc;
        MPI_Comm_size(MPI_COMM_WORLD, &Nummpc);
        MPI_Comm_rank(MPI_COMM_WORLD, &Rankkpc);

        MPI_Status status;
        int grS = static_cast<int>(sqrt(Nummpc));
        if (grS * grS != Nummpc) {
            throw "ERROR";
        }
        std::vector<int> grCo(2);
        makingGcomms(grS, Rankkpc, grCo.data());
        int Bl_s;
        if (Rankkpc == 0) {
            Bl_s = static_cast<int>(n) / grS;
        }
        MPI_Bcast(&Bl_s, 1, MPI_INT, 0, MPI_COMM_WORLD);
        std::vector<double> block_a(Bl_s * Bl_s);
        std::vector<double> block_b(Bl_s * Bl_s);
        std::vector<double> block_ab(Bl_s * Bl_s, 0);
        if (Rankkpc == 0) {
            for (int i = 0; i < Bl_s; i++) {
                for (int j = 0; j < Bl_s; j++) {
                    block_a[i * Bl_s + j] = a[i * n + j];
                    block_b[i * Bl_s + j] = b[i * n + j];
                }
            }
        }
        MPI_Datatype Bl_Matrix;
        MPI_Type_vector(Bl_s, Bl_s, Bl_s * grS, MPI_DOUBLE, &Bl_Matrix);
        MPI_Type_commit(&Bl_Matrix);
        if (Rankkpc == 0) {
            for (int p = 1; p < Nummpc; p++) {
                MPI_Send(a.data() + (p % grS) * Bl_s + (p / grS) * n * Bl_s, 1, Bl_Matrix, p, 0, GC);
                MPI_Send(b.data() + (p % grS) * Bl_s + (p / grS) * n * Bl_s, 1, Bl_Matrix, p, 1, GC);
            }
        } else {
            MPI_Recv(block_a.data(), Bl_s * Bl_s, MPI_DOUBLE, 0, 0, GC, &status);
            MPI_Recv(block_b.data(), Bl_s * Bl_s, MPI_DOUBLE, 0, 1, GC, &status);
        }
        for (int i = 0; i < grS; i++) {
            std::vector<double> t_BL_a(Bl_s * Bl_s);
            int p_t = (grCo[0] + i) % grS;
            if (grCo[1] == p_t) {
                t_BL_a = block_a;
            }
            MPI_Bcast(t_BL_a.data(), Bl_s * Bl_s, MPI_DOUBLE, p_t, RC);
            blockMult(t_BL_a.data(), block_b.data(), block_ab.data(), Bl_s);
            int Next_p = grCo[0] + 1;
            if (grCo[0] == grS - 1)
                Next_p = 0;
            int pred_p = grCo[0] - 1;
            if (grCo[0] == 0)
                pred_p = grS - 1;
            MPI_Sendrecv_replace(block_b.data(), Bl_s * Bl_s, MPI_DOUBLE, pred_p, 0, Next_p, 0, CC, &status);
        }
        std::vector<double> res(n * n);
        if (Rankkpc == 0) {
            for (int i = 0; i < Bl_s; i++) {
                for (int j = 0; j < Bl_s; j++)
                    res[i * n + j] = block_ab[i * Bl_s + j];
            }
        }
        if (Rankkpc != 0) {
            MPI_Send(block_ab.data(), Bl_s * Bl_s, MPI_DOUBLE, 0, 3, MPI_COMM_WORLD);
        } else {
            for (int p = 1; p < Nummpc; p++) {
                MPI_Recv(res.data() + (p % grS) * Bl_s + (p / grS) * n * Bl_s,
                    Bl_s * Bl_s, Bl_Matrix, p, 3, MPI_COMM_WORLD, &status);
            }
        }
        MPI_Type_free(&Bl_Matrix);
        return res;
    }
}  // namespace MyNs

