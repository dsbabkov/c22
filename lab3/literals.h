#pragma once
#include <stdexcept>

constexpr int charToBin(char ch){
    if (ch != '0' && ch != '1'){
        throw std::invalid_argument("Argument has to be 0 or 1");
    }
    return ch == '0' ? 0 : 1;
}

constexpr int operator "" _b(const char *str, unsigned long count){
    return count ?
            (charToBin(*str) << (count - 1)) + operator""_b(str + 1, count - 1) :
                0;
}
