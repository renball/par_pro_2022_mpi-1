// Copyright 2023 Yablonskii Dmitriy
#include <gtest/gtest.h>
#include "./ops_mpi.h"
#include <gtest-mpi-listener.hpp>

TEST(Parallel_Operations_MPI, Test_Sum_1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int> main_vec;
    const int vec_size = 14;
    if (rank == 0) {
        main_vec = { 1, 2, 3, 4, 5, 10, 7, 8, 90, 6, 11, 12, 59, 18 };
    }
    int fullsumm = par_summa(main_vec, vec_size);
    if (rank == 0) {
        int truesumm = 236;
        ASSERT_EQ(truesumm, fullsumm);
    }
}

TEST(Parallel_Operations_MPI, Test_Sum_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> main_vec;
    const int vec_size = 26;

    if (rank == 0) {
        main_vec = rand_vec(vec_size);
    }
    int fullsumm = par_summa(main_vec, vec_size);
    if (rank == 0) {
        int truesumm = stand_summa(main_vec);
        ASSERT_EQ(truesumm, fullsumm);
    }
}

TEST(Parallel_Operations_MPI, Test_Sum_3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> main_vec;
    const int vec_size = 151;

    if (rank == 0) {
        main_vec = rand_vec(vec_size);
    }
    int fullsumm = par_summa(main_vec, vec_size);
    if (rank == 0) {
        int truesumm = stand_summa(main_vec);
        ASSERT_EQ(truesumm, fullsumm);
    }
}

TEST(Parallel_Operations_MPI, Test_Sum_4) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> main_vec;
    const int vec_size = 543;

    if (rank == 0) {
        main_vec = rand_vec(vec_size);
    }
    int fullsumm = par_summa(main_vec, vec_size);
    if (rank == 0) {
        int truesumm = stand_summa(main_vec);
        ASSERT_EQ(truesumm, fullsumm);
    }
}

TEST(Parallel_Operations_MPI, Test_Sum_5) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> main_vec;
    const int vec_size = 1001;

    if (rank == 0) {
        main_vec = rand_vec(vec_size);
    }
    int fullsumm = par_summa(main_vec, vec_size);
    if (rank == 0) {
        int truesumm = stand_summa(main_vec);
        ASSERT_EQ(truesumm, fullsumm);
    }
}

TEST(Parallel_Operations_MPI, Test_Sum_6) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> main_vec;
    const int vec_size = 1500;

    if (rank == 0) {
        main_vec = rand_vec(vec_size);
    }
    int fullsumm = par_summa(main_vec, vec_size);
    if (rank == 0) {
        int truesumm = stand_summa(main_vec);
        ASSERT_EQ(truesumm, fullsumm);
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
