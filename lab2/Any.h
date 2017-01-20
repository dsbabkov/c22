#pragma once
#include "IAny.h"
#include <iostream>

template <typename T>
class Any: public IAny
{
public:
    explicit Any(const T &value)
        : value_{value}
    {}

    virtual IAny::Ptr operator + (const IAny &other) const override{
        return IAny::Ptr(new Any(value_ + dynamic_cast<const Any &>(other).value_));
    }

    virtual IAny &operator += (const IAny &other) override{
        value_ += dynamic_cast<const Any &>(other).value_;
        return *this;
    }

    virtual IAny::Ptr operator ++(int) override{
        IAny::Ptr result(new Any(value_++));
        return result;
    }

    virtual IAny::Ptr clone() const override{
        return IAny::Ptr(new Any(value_));
    }

    virtual bool operator == (const IAny &other) const override{
        return typeid(other) == typeid(*this) &&
                value_ == static_cast<const Any &>(other).value_;
    }

    virtual void print(std::ostream &os) const override{
        os << value_;
    }

private:
    T value_;
};
