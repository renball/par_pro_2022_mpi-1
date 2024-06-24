// Copyright 2023 Yablonskii Dmitriy
#include <mpi.h>
#include <math.h>
#include <iostream>
#include <random>
#include <algorithm>
#include "../../../modules/test_tasks/test_mpi/ops_mpi.h"

std::vector<int> rand_vec(int size) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = gen() % 10;
    }
    return vec;
}

int stand_s(std::vector<int> V) {
    int s = 0;
    for (int i = 0; i < V.size(); i++) 
        s += V[i];
    
    return s;
}

int ps(std::vector<int> Vector, int size) {
    int PR, PN;
    MPI_Comm_size(MPI_COMM_WORLD, &PN);
    MPI_Comm_rank(MPI_COMM_WORLD, &PR);

    int d = size / PN;
    if (d == 0) d = 1;

    int t;
    if (PN < size)
        t = PN;
    else
        t = size;

    std::vector<int> cur_vec(d);

    if (PR == 0) {
        cur_vec = std::vector<int>(Vector.begin(), Vector.begin() + d);

        for (int i = 1; i < t; i++) 
            MPI_Send(Vector.data() + i * d, d, MPI_INT, i, 0, MPI_COMM_WORLD);
        
    } 
    else if (PR < size) {
        MPI_Status status;
        MPI_Recv(cur_vec.data(), d, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    if (PR == 0) {
        if (size % t > 0) {

            int j = 0;
            cur_vec.resize(cur_vec.size() + size % PN);

            for (int i = (size - size % PN); i < size; i++) {
                cur_vec[j + d] = Vector[i];
                j++;
            }
        }
    }

    int fulsum = 0;
    int cursum = 0;
    if (PR < size) cursum = sum(cur_vec);
    MPI_Reduce(&cursum, &fulsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    return fulsum;
}
