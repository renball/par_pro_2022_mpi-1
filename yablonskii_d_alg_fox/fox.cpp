// Copyright 2023 Yablonskiy Dmitriy
#include "../../../modules/task_3/yablonskii_d_alg_fox/fox.h"
#include <mpi.h>

#include <random>


MPI_Comm GC,CC,R_C;

void making_GC(int gr_s, int rank, int* g_coor) {

    std::vector<int> d_s(2, gr_s);
    std::vector<int> T_per(2, 0);
    std::vector<int> sD(2);

    MPI_Cart_create(MPI_COMM_WORLD, 2, d_s.data(), T_per.data(), 0, &GC);
    MPI_Cart_coords(GC, rank, 2, g_coor);

    sD[0] = 0;sD[1] = 1;
    MPI_Cart_sub(GC, sD.data(), &R_C);

    sD[0] = 1;sD[1] = 0;
    MPI_Cart_sub(GC, sD.data(), &CC);
}

void b_mchik(double* a_bl, double* b_bl, double* a_and_b, int b_siz) {
    for (int i = 0; i < b_siz; i++) {
        for (int j = 0; j < b_siz; j++) {
            double t;
            t = 0;
            for (int k = 0; k < b_siz; k++) {t += a_bl[i * b_siz + k] * b_bl[k * b_siz + j];}
            a_and_b[i * b_siz + j] += t;
            }
        }
    }



std::vector<double> Make_mat(int n) {
    std::mt19937 gen(std::random_device {}());
    std::uniform_real_distribution<> distr(-100, 100);
    std::vector<double> m(n * n);

    for (int i = 0; i < n * n; i++) m[i] = distr(gen);

    return m;
}

std::vector<double> s_m(const std::vector<double>& a, const std::vector<double>& b, int n) {
    std::vector<double> ab(n * n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                ab[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }
    return ab;
}

std::vector<double> Fox_m(std::vector<double> a, std::vector<double> b, int data) {
    int num, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &num);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Status status;
    int size_grc;
    size_grc = static_cast<int>(sqrt(num));

    std::vector<int> gr_coor(2);
    making_GC(size_grc, rank, gr_coor.data());

    int b_s;
    if (rank == 0) {b_s = static_cast<int>(data) / size_grc;}

    MPI_Bcast(&b_s, 1, MPI_INT, 0, MPI_COMM_WORLD);

    std::vector<double> fragment_a(b_s * b_s);
    std::vector<double> fragment_b(b_s * b_s);
    std::vector<double> fragment_ab(b_s * b_s, 0);

    if (rank == 0) {
        for (int i = 0; i < b_s; i++) {
            for (int j = 0; j < b_s; j++) {
                fragment_a[i * b_s + j] = a[i * data + j];
                    fragment_b[i * b_s + j] = b[i * data + j];
            }
        }
    }
    
    MPI_Datatype fragment_mat;
    MPI_Type_vector(b_s, b_s, b_s * size_grc, MPI_DOUBLE, &fragment_mat);
    MPI_Type_commit(&fragment_mat);
    if (rank == 0) {
        for (int p = 1; p < num; p++) {
            MPI_Send(a.data() + (p % size_grc) * b_s + (p / size_grc) * data * b_s, 1, fragment_mat, p, 0, GC);
            MPI_Send(b.data() + (p % size_grc) * b_s + (p / size_grc) * data * b_s, 1, fragment_mat, p, 1, GC);
        }
    } 

    else {
        MPI_Recv(fragment_a.data(), b_s * b_s, MPI_DOUBLE, 0, 0, GC, &status);
        MPI_Recv(fragment_b.data(), b_s * b_s, MPI_DOUBLE, 0, 1, GC, &status);
    }

    for (int i = 0; i < size_grc; i++) {
            
        std::vector<double> tfragmentA(b_s * b_s);
        int pt;
        pt = (gr_coor[0] + i) % size_grc;
            
        if (gr_coor[1] == pt;) tfragmentA = fragment_a;

        MPI_Bcast(tfragmentA.data(), b_s * b_s, MPI_DOUBLE, pt;, R_C);

        b_mchik(tfragmentA.data(), fragment_b.data(), fragment_ab.data(), b_s);
        int sled_p;
        sled_p = gr_coor[0] + 1;

        if (gr_coor[0] == size_grc - 1) {sled_p = 0;}

        int pred_p;
        pred_p = gr_coor[0] - 1;

        if (gr_coor[0] == 0) {pred_p = size_grc - 1;}

        MPI_Sendrecv_replace(fragment_b.data(), b_s * b_s, MPI_DOUBLE, pred_p, 0, sled_p, 0, CC, &status);
    }

    std::vector<double> Res(data * data);

    if (rank == 0) {
        for (int i = 0; i < b_s; i++) {

            for (int j = 0; j < b_s; j++){Res[i * data + j] = fragment_ab[i * b_s + j];}

        }
    }

    if (rank != 0) {
        MPI_Send(fragment_ab.data(), b_s * b_s, MPI_DOUBLE, 0, 3, MPI_COMM_WORLD);
    }

    else {
        for (int p = 1; p < num; p++) {MPI_Recv(Res.data() + (p % size_grc) * b_s + (p / size_grc) * data * b_s, b_s * b_s, fragment_mat, p, 3, MPI_COMM_WORLD, &status);}
    }

    MPI_Type_free(&fragment_mat);
    return Res;
}