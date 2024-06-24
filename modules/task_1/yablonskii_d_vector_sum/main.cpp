// Copyright 2023 Yablonskii Dmitriy
#include <gtest/gtest.h>
#include "./ops_mpi.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_stand_s_1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int> full_vec_s;
    const int vec_si = 5;
    if (rank == 0) {
        full_vec_s = { 1, 2, 3, 4, 5};
    }
    int psma = ps(full_vec_s, vec_si);
    
    if (rank == 0) {
        int true_stand_sma = 15;
        ASSERT_EQ(true_stand_sma, psma);
    }
}

TEST(Parallel_Operations_MPI, Test_stand_s_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> full_vec_s;
    const int vec_si = 10;

    if (rank == 0) full_vec_s = rand_vec(vec_si);

    int psma = ps(full_vec_s, vec_si);

    if (rank == 0) {
        int true_stand_sma = stand_s(full_vec_s);
        ASSERT_EQ(true_stand_sma, psma);
    }
}

TEST(Parallel_Operations_MPI, Test_stand_s_3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> full_vec_s;
    const int vec_si = 200;

    if (rank == 0) full_vec_s = rand_vec(vec_si);

    int psma = ps(full_vec_s, vec_si);

    if (rank == 0) {
        int true_stand_sma = stand_s(full_vec_s);
        ASSERT_EQ(true_stand_sma, psma);
    }
}

TEST(Parallel_Operations_MPI, Test_stand_s_4) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> full_vec_s;
    const int vec_si = 3000;

    if (rank == 0) full_vec_s = rand_vec(vec_si);

    int psma = ps(full_vec_s, vec_si);

    if (rank == 0) {
        int true_stand_sma = stand_s(full_vec_s);
        ASSERT_EQ(true_stand_sma, psma);
    }
}

TEST(Parallel_Operations_MPI, Test_stand_s_5) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> full_vec_s;
    const int vec_si = 40000;

    if (rank == 0) full_vec_s = rand_vec(vec_si);

    int psma = ps(full_vec_s, vec_si);

    if (rank == 0) {
        int true_stand_sma = stand_s(full_vec_s);
        ASSERT_EQ(true_stand_sma, psma);
    }
}

TEST(Parallel_Operations_MPI, Test_stand_s_6) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> full_vec_s;
    const int vec_si = 500000;

    if (rank == 0) full_vec_s = rand_vec(vec_si);

    int psma = ps(full_vec_s, vec_si);

    if (rank == 0) {
        int true_stand_sma = stand_s(full_vec_s);
        ASSERT_EQ(true_stand_sma, psma);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
