// Copyright 2023 Yablonskiy Dmitriy

#ifndef MODULES_TASK_2_YABLONSKII_D_STAR_STAR_H_
#define MODULES_TASK_2_YABLONSKII_D_STAR_STAR_H_

#include <mpi.h>
#include <iostream>

MPI_Comm Making_star(const MPI_Comm com);
bool Is_this_a_star_mmm(const MPI_Comm check_com);

#endif  // MODULES_TASK_2_YABLONSKII_D_STAR_STAR_H_
