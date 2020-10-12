// Copyright 2020 Kustova Anastasiya
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./max_vector.h"
TEST(Parallel_Operations_MPI, Test_can_count_Max) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vec;
    const int len = 100;
    if (rank == 0) {
        vec = getRandomVector(len);
    }
    ASSERT_NO_THROW(getParallelOperations(vec, len));
}

TEST(Parallel_Operations_MPI, Test_Max) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vec;
    const int len = 100;
    if (rank == 0) {
        vec = getRandomVector(len);
    }
    int parallel_max = getParallelOperations(vec, len);
    if (rank == 0) {
        int usual_max = getSequentialOperations(vec);
        ASSERT_EQ(usual_max, parallel_max);
    }
}


TEST(Parallel_Operations_MPI, Test_can_find_local_max) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vec = {3, 4, 9, -6};
    if (rank == 0) {
        int usual_max = getSequentialOperations(vec);
        ASSERT_EQ(9, usual_max);
    }
}


TEST(Parallel_Operations_MPI, Test_can_gen_random_vector) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int len = 100;
    if (rank == 0) {
        ASSERT_NO_THROW(getRandomVector(len));
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
