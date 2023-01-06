// Copyright Yablonskii Dmitriy
#ifndef MODULES_TASK_2_YABLONSKII_D_STAR_STAR_H_
#define MODULES_TASK_2_YABLONSKII_D_STAR_STAR_H_

#include <mpi.h>
#include <iostream>

MPI_Comm making_star(const MPI_Comm oldComm);

bool this_is_star_bool(const MPI_Comm curComm);

#endif  // MODULES_TASK_2_YABLONSKII_D_STAR_STAR_H_
