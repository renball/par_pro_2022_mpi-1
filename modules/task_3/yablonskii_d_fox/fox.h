// Copyright 2023 Yablonskii Dmitriy


#ifndef MODULES_TASK_3_YABLONSKII_D_FOX_FOX_H_
#define MODULES_TASK_3_YABLONSKII_D_FOX_FOX_H_

#include <vector>

namespace MyNs {
    std::vector<double> createmat(size_t size);

    std::vector<double> normOp(const std::vector<double>& a, const std::vector<double>& b, size_t size);

    std::vector<double> opfox(std::vector<double> a, std::vector<double> b, size_t data);
}  // namespace MyNs


#endif  //  MODULES_TASK_3_YABLONSKII_D_FOX_FOX_H_
