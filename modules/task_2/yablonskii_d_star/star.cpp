// Copyright 2023 Yablonskii Dmitriy

#include "../../../modules/task_2/yablonskii_d_star/star.h"


MPI_Comm makingstar(const MPI_Comm oldComm) {

    int points;
    MPI_Comm_size(oldComm, &points);


    int *id = new int[points];
    id[0] = points - 1;
    for (int i = 1; i < points; i++) {
        id[i] = id[0] + i;
    }

    int rebsize = 2 * (points - 1);
    int *rebra = new int[rebsize];
    int i = 0;
    for (; i < points - 1; i++) {
        rebra[i] = i + 1;
    }
    for (; i < rebsize; i++) {
        rebra[i] = 0;
    }


    int remake = 0;

    MPI_Comm starComm;
    MPI_Graph_create(oldComm, points, id, rebra, remake, &starComm);

    return starComm;
}

bool boolforstar(const MPI_Comm curComm) {

    int status;
    MPI_Topo_test(curComm, &status);
    if (status != MPI_GRAPH) {
        return false;
    }


    int points;
    int newreb;
    MPI_Graphdims_get(curComm, &points, &newreb);

    int rebsize = 2 * (points - 1);
    if (newreb != rebsize) {
        return false;
    }


    int *id = new int[points];
    int *rebra = new int[rebsize];
    MPI_Graph_get(curComm, points, rebsize, id, rebra);
    for (int i = 0; i < points; i++) {
        if (id[i] != i + points - 1) {
            return false;
        }
    }
    int i = 0;
    for (; i < points - 1; i++) {
        if (rebra[i] != i + 1) {
            return false;
        }
    }
    for (; i < rebsize; i++) {
        if (rebra[i] != 0) {
            return false;
        }
    }

    return true;
}
