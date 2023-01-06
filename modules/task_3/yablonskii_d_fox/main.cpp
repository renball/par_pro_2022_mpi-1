// Copyright 2023 Yablonskii Dmitriy


#include <gtest/gtest.h>
#include <cmath>
#include "../../../modules/task_3/yablonskii_d_fox/fox.h"
#include <gtest-mpi-listener.hpp>

TEST(Fox, Matrix1X1) {
    int pc_Rank, Num_pc;
    MPI_Comm_rank(MPI_COMM_WORLD, &pc_Rank);
    MPI_Comm_size(MPI_COMM_WORLD, &Num_pc);
    int size = 1;
    int BLK = static_cast<int>(sqrt(Num_pc));
    if (BLK * BLK == Num_pc) {
        std::vector<double> a, b, ab_fox;
        int dob = size % BLK;
        if (dob) {
            size += BLK - (size % BLK);
        }
        if (pc_Rank == 0) {
            a = myns::creatmat(size);
            b = myns::creatmat(size);
        }
        ab_fox = myns::fM(a, b, size);
        if (pc_Rank == 0) {
            std::vector<double> ab_seq = myns::sM(a, b, size);
            for (int i = 0; i < size * size; i++) {
                ASSERT_NEAR(ab_fox[i], ab_seq[i], 0.0001);
            }
        }
    }
}

TEST(Fox, Matrix5X5) {
    int pc_Rank, Num_pc;
    MPI_Comm_rank(MPI_COMM_WORLD, &pc_Rank);
    MPI_Comm_size(MPI_COMM_WORLD, &Num_pc);
    int size = 5;
    int BLK = static_cast<int>(sqrt(Num_pc));
    if (BLK * BLK == Num_pc) {
        std::vector<double> a, b, ab_fox;
        int dob = size % BLK;
        if (dob) {
            size += BLK - (size % BLK);
        }
        if (pc_Rank == 0) {
            a = myns::creatmat(size);
            b = myns::creatmat(size);
        }
        ab_fox = myns::fM(a, b, size);
        if (pc_Rank == 0) {
            std::vector<double> ab_seq = myns::sM(a, b, size);
            for (int i = 0; i < size * size; i++) {
                ASSERT_NEAR(ab_fox[i], ab_seq[i], 0.0001);
            }
        }
    }
}

TEST(Fox, Matrix10X10) {
    int pc_Rank, Num_pc;
    MPI_Comm_rank(MPI_COMM_WORLD, &pc_Rank);
    MPI_Comm_size(MPI_COMM_WORLD, &Num_pc);
    int size = 10;
    int BLK = static_cast<int>(sqrt(Num_pc));
    if (BLK * BLK == Num_pc) {
        std::vector<double> a, b, ab_fox;
        int dob = size % BLK;
        if (dob) {
            size += BLK - (size % BLK);
        }
        if (pc_Rank == 0) {
            a = myns::creatmat(size);
            b = myns::creatmat(size);
        }
        ab_fox = myns::fM(a, b, size);
        if (pc_Rank == 0) {
            std::vector<double> ab_seq = myns::sM(a, b, size);
            for (int i = 0; i < size * size; i++) {
                ASSERT_NEAR(ab_fox[i], ab_seq[i], 0.0001);
            }
        }
    }
}

TEST(Fox, Matrix20X20) {
    int pc_Rank, Num_pc;
    MPI_Comm_rank(MPI_COMM_WORLD, &pc_Rank);
    MPI_Comm_size(MPI_COMM_WORLD, &Num_pc);
    int size = 20;
    int BLK = static_cast<int>(sqrt(Num_pc));
    if (BLK * BLK == Num_pc) {
        std::vector<double> a, b, ab_fox;
        int dob = size % BLK;
        if (dob) {
            size += BLK - (size % BLK);
        }
        if (pc_Rank == 0) {
            a = myns::creatmat(size);
            b = myns::creatmat(size);
        }
        ab_fox = myns::fM(a, b, size);
        if (pc_Rank == 0) {
            std::vector<double> ab_seq = myns::sM(a, b, size);
            for (int i = 0; i < size * size; i++) {
                ASSERT_NEAR(ab_fox[i], ab_seq[i], 0.0001);
            }
        }
    }
}

TEST(Fox, Matrix50X50) {
    int pc_Rank, Num_pc;
    MPI_Comm_rank(MPI_COMM_WORLD, &pc_Rank);
    MPI_Comm_size(MPI_COMM_WORLD, &Num_pc);
    int size = 50;
    int BLK = static_cast<int>(sqrt(Num_pc));
    if (BLK * BLK == Num_pc) {
        std::vector<double> a, b, ab_fox;
        int dob = size % BLK;
        if (dob) {
            size += BLK - (size % BLK);
        }
        if (pc_Rank == 0) {
            a = myns::creatmat(size);
            b = myns::creatmat(size);
        }
        ab_fox = myns::fM(a, b, size);
        if (pc_Rank == 0) {
            std::vector<double> ab_seq = myns::sM(a, b, size);
            for (int i = 0; i < size * size; i++) {
                ASSERT_NEAR(ab_fox[i], ab_seq[i], 0.0001);
            }
        }
    }
}

TEST(Fox, Matrix100X100) {
    int pc_Rank, Num_pc;
    MPI_Comm_rank(MPI_COMM_WORLD, &pc_Rank);
    MPI_Comm_size(MPI_COMM_WORLD, &Num_pc);
    int size = 100;
    int BLK = static_cast<int>(sqrt(Num_pc));
    if (BLK * BLK == Num_pc) {
        std::vector<double> a, b, ab_fox;
        int dob = size % BLK;
        if (dob) {
            size += BLK - (size % BLK);
        }
        if (pc_Rank == 0) {
            a = myns::creatmat(size);
            b = myns::creatmat(size);
        }
        ab_fox = myns::fM(a, b, size);
        if (pc_Rank == 0) {
            std::vector<double> ab_seq = myns::sM(a, b, size);
            for (int i = 0; i < size * size; i++) {
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
