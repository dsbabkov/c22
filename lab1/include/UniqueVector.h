#pragma once

#include <algorithm>
#include <functional>
#include <vector>
#include <initializer_list>

template <typename T>
class UniqueVector{
public:
    enum class Order{
        AscendingOrder,
        DescendingOrder
    };

public:
    UniqueVector(std::initializer_list<T> list = {})
        : UniqueVector(list.begin(), list.end())
    {
    }

    template <typename InputIterator>
    UniqueVector(InputIterator begin, InputIterator end){
        std::copy_if(begin, end, std::back_inserter(v_),
                     [this](const T &value){return !contains(v_, value);});
    }

    UniqueVector(const UniqueVector &) = default;
    UniqueVector(UniqueVector &&) = default;
    UniqueVector &operator = (const UniqueVector &) = default;
    UniqueVector &operator = (UniqueVector &&) = default;

    UniqueVector &operator << (std::initializer_list<T> list){
        std::copy_if(list.begin(), list.end(), std::back_inserter(v_),
                     [this](const T &value){return !contains(v_, value);});
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

private:
    template <typename C>
    static bool contains(const C &container, const T &value){
        return std::find(std::cbegin(container), std::cend(container), value) != std::cend(container);
    }

private:
    std::vector<T> v_;
};
