#pragma once
#include <iostream>

template <typename C>
void PrintAnyCont(const C &container){
    for (auto it = std::begin(container), end = std::end(container); it != end; ++it){
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}
