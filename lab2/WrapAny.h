#pragma once
#include "Any.h"
#include <memory>

class WrapAny
{
    friend std::ostream &operator << (std::ostream &os, const WrapAny &any);
public:
    template <typename T>
    explicit WrapAny(const T &value)
        : any_{new Any<T>(value)}
    {}

    ~WrapAny();
    WrapAny (WrapAny &&) = default;
    WrapAny &operator = (WrapAny &&) = default;

    WrapAny (const WrapAny &other);
    WrapAny &operator = (const WrapAny &other);

    WrapAny operator + (const WrapAny &other) const;
    WrapAny& operator += (const WrapAny &other);
    WrapAny operator ++ (int);

    bool operator == (const WrapAny &other) const;

private:
    WrapAny(IAny::Ptr any);
    void print(std::ostream &os) const;

private:
    IAny::Ptr any_;
};
