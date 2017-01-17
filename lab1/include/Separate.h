#pragma once

#include <functional>
#include <algorithm>

template<typename CIn, typename COut1, typename COut2, typename Predicate>
void Separate(const CIn &inputContainer, COut1 &outputContainer1, COut2 &outputContainer2, Predicate predicate){
    for (const auto &value: inputContainer){
        predicate(value) ?
            outputContainer1.push_back(value) :
            outputContainer2.push_back(value);
    }
}
