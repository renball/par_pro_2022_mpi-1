// Copyright Yablonskii Dmitriy

#include "../../../modules/task_2/yablonskii_d_star/star.h"


MPI_Comm making_star(const MPI_Comm oldComm) {

    int points;
    MPI_Comm_size(oldComm, &points);


    int *idp = new int[points];
    idp[0] = points - 1;

    for (int i = 1; i < points; i++) {
        idp[i] = idp[0] + i;
    }


    int size_of_e = 2 * (points - 1);
    int *rebro = new int[size_of_e];
    int i = 0;
    for (; i < points - 1; i++) {
        rebro[i] = i + 1;
    }
    for (; i < size_of_e; i++) {
        rebro[i] = 0;
    }


    int pereshtuka = 0;


    MPI_Comm star;
    MPI_Graph_create(oldComm, points, idp, rebro, pereshtuka, &star);

    return star;
}

bool this_is_star_bool(const MPI_Comm curComm) {

    int status;
    MPI_Topo_test(curComm, &status);
    if (status != MPI_GRAPH) {
        return false;
    }


    int points;
    int ese_rebra;
    MPI_Graphdims_get(curComm, &points, &ese_rebra);

    int size_of_e = 2 * (points - 1);
    if (ese_rebra != size_of_e) {
        return false;
    }


    int *idp = new int[points];
    int *rebro = new int[size_of_e];
    MPI_Graph_get(curComm, points, size_of_e, idp, rebro);
    for (int i = 0; i < points; i++) {
        if (idp[i] != i + points - 1) {
            return false;
        }
    }
    int i = 0;
    for (; i < points - 1; i++) {
        if (rebro[i] != i + 1) {
            return false;
        }
    }
    for (; i < size_of_e; i++) {
        if (rebro[i] != 0) {
            return false;
        }
    }

    return true;
}
