#pragma once

#include <algorithm>
#include <functional>
#include <vector>
#include <initializer_list>

template <typename T>
class RangedUniqueVector{
public:
    enum class Order{
        AscendingOrder,
        DescendingOrder
    };

public:
    explicit RangedUniqueVector(const std::pair<T, T> &range)
        : range_ {range}
    {
        if (range_.first > range_.second){
            std::swap(range_.first, range_.second);
        }
    }

    RangedUniqueVector(const std::pair<T, T> &range, std::initializer_list<T> list)
        : RangedUniqueVector(range, list.begin(), list.end())
    {}

    template <typename InputIterator>
    RangedUniqueVector(const std::pair<T, T> &range, InputIterator begin, InputIterator end)
        : range_{range}
    {
        std::copy_if(begin, end, std::back_inserter(v_), conditionLambda());
    }

    RangedUniqueVector(const RangedUniqueVector &) = default;
    RangedUniqueVector(RangedUniqueVector &&) = default;
    RangedUniqueVector &operator = (const RangedUniqueVector &) = default;
    RangedUniqueVector &operator = (RangedUniqueVector &&) = default;


    RangedUniqueVector &operator << (std::initializer_list<T> list){
        std::copy_if(list.begin(), list.end(), std::back_inserter(v_), conditionLambda());
        return *this;
    }

    void remove(std::initializer_list<T> list){
        v_.erase(std::remove_if(v_.begin(), v_.end(),
                                [list](const T &value){return contains(list, value);}), v_.cend());
    }

    void sort(Order order = Order::AscendingOrder){
        if (order == Order::AscendingOrder){
            std::sort(v_.begin(), v_.end());
        }
        else{
            std::sort(v_.rbegin(), v_.rend());
        }
    }

    std::pair<T, T> range() const
    {
        return range_;
    }

    void setRange(const std::pair<T, T> &range)
    {
        range_ = range;
    }

private:
    template <typename C>
    static bool contains(const C &container, const T &value){
        return std::find(std::cbegin(container), std::cend(container), value) != std::cend(container);
    }

    bool valueInRange(const T &value) const {
        return range_.first <= value && value <= range_.second;
    }

    bool canAdd(const T &value) const{
        return !contains(v_, value) &&
                valueInRange(value);

    }

    auto conditionLambda() const{
        return [this](const T &value){return canAdd(value);};
    }


private:
    std::vector<T> v_;
    std::pair<T, T> range_;
};




