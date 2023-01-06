// Copyright Yablonskii Dmitriy

#include <gtest/gtest.h>
#include "../../../modules/task_2/yablonskii_d_star/star.h"
#include <gtest-mpi-listener.hpp>

TEST(star_test, can_create_star) {
    ASSERT_NO_THROW(making_star(MPI_COMM_WORLD));
}

TEST(star_test, no_throw_test) {
    ASSERT_NO_THROW(this_is_star_bool(MPI_COMM_WORLD));
}

TEST(star_test, check_random_topology) {
    int rank, points;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &points);

    int* idp = new int[points];
    int* rebra = new int[2 * points];
    for (int i = 0; i < points; i++) {
        idp[i] = 2 + i * 2;
        rebra[i * 2] = (points - 1 + i) % points;
        rebra[(i * 2) + 1] = (points + 1 + i) % points;
    }
    MPI_Comm comm;
    MPI_Graph_create(MPI_COMM_WORLD, points, idp, rebra, 0, &comm);
    if (rank == 0 && points != 1) {
        EXPECT_FALSE(this_is_star_bool(comm));
    }
}

TEST(star_test, check_is_star_topology) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm star = making_star(MPI_COMM_WORLD);
    if (rank == 0) {
        EXPECT_TRUE(this_is_star_bool(star));
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
