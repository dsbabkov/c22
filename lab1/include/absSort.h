#pragma once

#include <algorithm>
#include <cmath>

template <typename C>
void absSort(C &container){
    std::sort(std::begin(container), std::end(container),
              [](const auto &left, const auto &right){return std::abs(left) < std::abs(right);});
}
