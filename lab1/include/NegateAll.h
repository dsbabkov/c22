#pragma once

#include <string>

std::string operator - (const std::string &line){
    std::string result = line;

    for (char &ch: result){
        if (('A' <= ch && ch <= 'Z') ||
                ('a' <= ch && ch <= 'z')){
            ch ^= 0x20;
        }
    }

    return result;
}

template <typename C>
void NegateAll(C &container){
    for (auto &value: container){
        value = -value;
    }
}
