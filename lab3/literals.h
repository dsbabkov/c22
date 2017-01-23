#pragma once
#include <stdexcept>
#include <string>
#include <climits>

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

std::string operator"" _toBinStr(unsigned long long value){
    if (!value){
        return "0b0";
    }

    constexpr uint nBits = CHAR_BIT *sizeof(value);
    static const auto bit = [](unsigned long long value, uint i)->int{return (value >> i) & 1;};

    uint i = nBits - 1;
    for(; !bit(value, i); --i);

    std::string result("0b");
    for (; i < nBits; --i){
        result += std::to_string(bit(value, i));
    }
    return result;
}
