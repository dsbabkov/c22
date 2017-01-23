#pragma once

#include <algorithm>

template <typename T>
class Range{
    T min_, max_;

public:
    constexpr explicit Range(const T &min = {}, const T &max = {})
        : min_{std::min(min, max)}
        , max_{std::max(min, max)}
    {}

    constexpr Range(const Range &) = default;

    constexpr T min() const{
        return min_;
    }

    constexpr T max() const{
        return max_;
    }

    constexpr bool contains(const T &value) const{
        return min_ <= value && value <= max_;
    }

    constexpr T validate(const T &value) const{
        return contains(value) ?
                    value:
                    fitInvalid(value);
    }

private:
    constexpr T fitInvalid(const T &value) const{
        return value < min_ ?
                    min_ :
                    max_;
    }
};

template <typename T>
constexpr Range<T> makeRange(const T &min = {}, const T &max = {}){
    return Range<T>{min, max};
}
