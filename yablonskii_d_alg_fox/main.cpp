// Copyright 2023 Yablonskiy Dmitriy
#include <gtest/gtest.h>
#include <cmath>
#include "../../../modules/task_3/yablonskii_d_alg_fox/fox.h"
#include <gtest-mpi-listener.hpp>

TEST(f1, mat_1) {
    int rank, num;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num);
    int n = 1;

    int quadros = static_cast<int>(sqrt(num));
    
    if (quadros * quadros == num) {
        std::vector<double> a, b, AxB_f;

        int dobav = n % quadros;

        if (dobav) {
            n += quadros - (n % quadros);
        }
        if (rank == 0) {
            a = Make_mat(n);
            b = Make_mat(n);
        }
        AxB_f = Fox_m(a, b, n);
        if (rank == 0) {
            std::vector<double> a_s_b = s_m(a, b, n);
            for (int i = 0; i < n * n; i++) {
                ASSERT_NEAR(AxB_f[i], a_s_b[i], 0.0001);
            }
        }
    }
}

TEST(f2, mat_5) {
    int rank, num;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num);
    int n = 5;
    int quadros = static_cast<int>(sqrt(num));
    if (quadros * quadros == num) {
        std::vector<double> a, b, AxB_f;
        int dobav = n % quadros;
        if (dobav) {
            n += quadros - (n % quadros);
        }
        if (rank == 0) {
            a = Make_mat(n);
            b = Make_mat(n);
        }
        AxB_f = Fox_m(a, b, n);
        if (rank == 0) {
            std::vector<double> a_s_b = s_m(a, b, n);
            for (int i = 0; i < n * n; i++) {
                ASSERT_NEAR(AxB_f[i], a_s_b[i], 0.0001);
            }
        }
    }
}

TEST(f3, mat_10) {
    int rank, num;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num);
    int n = 10;
    int quadros = static_cast<int>(sqrt(num));
    if (quadros * quadros == num) {
        std::vector<double> a, b, AxB_f;
        int dobav = n % quadros;
        if (dobav) {
            n += quadros - (n % quadros);
        }
        if (rank == 0) {
            a = Make_mat(n);
            b = Make_mat(n);
        }
        AxB_f = Fox_m(a, b, n);
        if (rank == 0) {
            std::vector<double> a_s_b = s_m(a, b, n);
            for (int i = 0; i < n * n; i++) {
                ASSERT_NEAR(AxB_f[i], a_s_b[i], 0.0001);
            }
        }
    }
}


TEST(f4, mat_100) {
    int rank, num;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num);
    int n = 100;
    int quadros = static_cast<int>(sqrt(num));
    if (quadros * quadros == num) {
        std::vector<double> a, b, AxB_f;
        int dobav = n % quadros;
        if (dobav) {
            n += quadros - (n % quadros);
        }
        if (rank == 0) {
            a = Make_mat(n);
            b = Make_mat(n);
        }
        AxB_f = Fox_m(a, b, n);
        if (rank == 0) {
            std::vector<double> a_s_b = s_m(a, b, n);
            for (int i = 0; i < n * n; i++) {
                ASSERT_NEAR(AxB_f[i], a_s_b[i], 0.0001);
            }
        }
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::dobavGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners &listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
