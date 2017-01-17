#pragma once

#include <algorithm>
#include <vector>

template <typename C1, typename C2>
auto SumCont(const C1 &left, const C2 &right){
    using std::size;
    using std::cbegin;
    using std::cend;

    using ValueType = decltype(*cbegin(left) + *cbegin(right));
    using ResultContainer = std::vector<ValueType>;

    ResultContainer result;

    auto magic = [](const auto &val1, const auto &val2){return val1 + val2;};

    if (size(left) < size(right)){
        result = std::move(ResultContainer(cbegin(right), cend(right)));
        std::transform(cbegin(left), cend(left), cbegin(result), std::begin(result), magic);
    }
    else {
        result = std::move(ResultContainer(cbegin(left), cend(left)));
        std::transform(cbegin(right), cend(right), cbegin(result), std::begin(result), magic);
    }

    return result;
}
