#pragma once

#include <string>

template <typename C>
void NegateAll(C &container){
    for (auto &value: container){
        value = -value;
    }
}
