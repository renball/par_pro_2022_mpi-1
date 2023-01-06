// Copyright 2022 Churkin Alexander
#ifndef MODULES_TASK_1_YABLONSKII_D_VECTOR_SUM_VECTOR_SUM_H
#define MODULES_TASK_1_YABLONSKII_D_VECTOR_SUM_VECTOR_SUM_H

#include <vector>
#include <string>

std::vector<int> getRandomVector(int size);

void printVector(const std::string& name, const std::vector<int>& vec);

int getSumSequential(std::vector<int> vec);

int getSumParallel(const std::vector<int>& globalVector, int global_vector_size);

#endif  // MODULES_TASK_1_YABLONSKII_D_VECTOR_SUM_VECTOR_SUM_H
