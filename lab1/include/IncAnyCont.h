#pragma once

template <typename C>
void IncAnyCont(C &container){
    for (auto &value: container){
        ++value;
    }
}
