// Copyright 2023 Yablonskii Dmitriy


#include <gtest/gtest.h>
#include <cmath>
#include "../../../modules/task_3/yablonskii_d_fox/fox.h"
#include <gtest-mpi-listener.hpp>

TEST(Fox, Matrix1X1) {
    int Rankpc, Numpc;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rankpc);
    MPI_Comm_size(MPI_COMM_WORLD, &Numpc);
    size_t n = 1;
    int bk = static_cast<int>(sqrt(Numpc));
    if (bk * bk == Numpc) {
        std::vector<double> a, b, ab_fox;
        int dob = n % bk;
        if (dob) {
            n += bk - (n % bk);
        }
        if (Rankpc == 0) {
            a = MyNs::createmat(n);
            b = MyNs::createmat(n);
        }
        ab_fox = MyNs::opfox(a, b, n);
        if (Rankpc == 0) {
            std::vector<double> ab_seq = MyNs::normOp(a, b, n);
            for (int i = 0; i < n * n; i++) {
                ASSERT_NEAR(ab_fox[i], ab_seq[i], 0.0001);
            }
        }
    }
}

TEST(Fox, Matrix5X5) {
    int Rankpc, Numpc;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rankpc);
    MPI_Comm_size(MPI_COMM_WORLD, &Numpc);
    size_t n = 5;
    int bk = static_cast<int>(sqrt(Numpc));
    if (bk * bk == Numpc) {
        std::vector<double> a, b, ab_fox;
        int dob = n % bk;
        if (dob) {
            n += bk - (n % bk);
        }
        if (Rankpc == 0) {
            a = MyNs::createmat(n);
            b = MyNs::createmat(n);
        }
        ab_fox = MyNs::opfox(a, b, n);
        if (Rankpc == 0) {
            std::vector<double> ab_seq = MyNs::normOp(a, b, n);
            for (int i = 0; i < n * n; i++) {
                ASSERT_NEAR(ab_fox[i], ab_seq[i], 0.0001);
            }
        }
    }
}

TEST(Fox, Matrix10X10) {
    int Rankpc, Numpc;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rankpc);
    MPI_Comm_size(MPI_COMM_WORLD, &Numpc);
    size_t n = 10;
    int bk = static_cast<int>(sqrt(Numpc));
    if (bk * bk == Numpc) {
        std::vector<double> a, b, ab_fox;
        int dob = n % bk;
        if (dob) {
            n += bk - (n % bk);
        }
        if (Rankpc == 0) {
            a = MyNs::createmat(n);
            b = MyNs::createmat(n);
        }
        ab_fox = MyNs::opfox(a, b, n);
        if (Rankpc == 0) {
            std::vector<double> ab_seq = MyNs::normOp(a, b, n);
            for (int i = 0; i < n * n; i++) {
                ASSERT_NEAR(ab_fox[i], ab_seq[i], 0.0001);
            }
        }
    }
}

TEST(Fox, Matrix20X20) {
    int Rankpc, Numpc;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rankpc);
    MPI_Comm_size(MPI_COMM_WORLD, &Numpc);
    size_t n = 20;
    int bk = static_cast<int>(sqrt(Numpc));
    if (bk * bk == Numpc) {
        std::vector<double> a, b, ab_fox;
        int dob = n % bk;
        if (dob) {
            n += bk - (n % bk);
        }
        if (Rankpc == 0) {
            a = MyNs::createmat(n);
            b = MyNs::createmat(n);
        }
        ab_fox = MyNs::opfox(a, b, n);
        if (Rankpc == 0) {
            std::vector<double> ab_seq = MyNs::normOp(a, b, n);
            for (int i = 0; i < n * n; i++) {
                ASSERT_NEAR(ab_fox[i], ab_seq[i], 0.0001);
            }
        }
    }
}

TEST(Fox, Matrix50X50) {
    int Rankpc, Numpc;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rankpc);
    MPI_Comm_size(MPI_COMM_WORLD, &Numpc);
    size_t n = 50;
    int bk = static_cast<int>(sqrt(Numpc));
    if (bk * bk == Numpc) {
        std::vector<double> a, b, ab_fox;
        int dob = n % bk;
        if (dob) {
            n += bk - (n % bk);
        }
        if (Rankpc == 0) {
            a = MyNs::createmat(n);
            b = MyNs::createmat(n);
        }
        ab_fox = MyNs::opfox(a, b, n);
        if (Rankpc == 0) {
            std::vector<double> ab_seq = MyNs::normOp(a, b, n);
            for (int i = 0; i < n * n; i++) {
                ASSERT_NEAR(ab_fox[i], ab_seq[i], 0.0001);
            }
        }
    }
}

TEST(Fox, Matrix100X100) {
    int Rankpc, Numpc;
    MPI_Comm_rank(MPI_COMM_WORLD, &Rankpc);
    MPI_Comm_size(MPI_COMM_WORLD, &Numpc);
    size_t n = 100;
    int bk = static_cast<int>(sqrt(Numpc));
    if (bk * bk == Numpc) {
        std::vector<double> a, b, ab_fox;
        int dob = n % bk;
        if (dob) {
            n += bk - (n % bk);
        }
        if (Rankpc == 0) {
            a = MyNs::createmat(n);
            b = MyNs::createmat(n);
        }
        ab_fox = MyNs::opfox(a, b, n);
        if (Rankpc == 0) {
            std::vector<double> ab_seq = MyNs::normOp(a, b, n);
            for (int i = 0; i < n * n; i++) {
                ASSERT_NEAR(ab_fox[i], ab_seq[i], 0.0001);
            }
        }
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners &listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
