// Copyright Yablonskii Dmitriy

#include <gtest/gtest.h>
#include "../../../modules/task_2/yablonskii_d_star/star.h"
#include <gtest-mpi-listener.hpp>

TEST(star_test, can_create_star) {
    ASSERT_NO_THROW(makingstarComm(MPI_COMM_WORLD));
}

TEST(star_test, no_throw_test) {
    ASSERT_NO_THROW(boolstartop(MPI_COMM_WORLD));
}

TEST(star_test, check_random_topology) {
    int rank, points;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &points);

    int* id = new int[points];
    int* reb = new int[2 * points];
    for (int i = 0; i < points; i++) {
        id[i] = 2 + i * 2;
        reb[i * 2] = (points - 1 + i) % points;
        reb[(i * 2) + 1] = (points + 1 + i) % points;
    }
    MPI_Comm comm;
    MPI_Graph_create(MPI_COMM_WORLD, points, id, reb, 0, &comm);
    if (rank == 0 && points != 1) {
        EXPECT_FALSE(boolstartop(comm));
    }
}

TEST(star_test, check_is_star_topology) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm star = makingstarComm(MPI_COMM_WORLD);
    if (rank == 0) {
        EXPECT_TRUE(boolstartop(star));
    }
}

TEST(star_test, check_is_not_star_topology) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        EXPECT_FALSE(boolstartop(MPI_COMM_WORLD));
    }
}

int main(int argc, char **argv) {
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
