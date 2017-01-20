#pragma once
#include <memory>
#include <iosfwd>

class IAny
{
    template<typename T>
    friend struct std::default_delete;

    template <typename T>
    friend class Any;

    friend class WrapAny;

    using Ptr = std::unique_ptr<IAny>;
//    using Ptr = IAny*;

    virtual ~IAny();
    virtual Ptr clone() const = 0;

    virtual Ptr operator + (const IAny &other) const = 0;
    virtual IAny &operator += (const IAny &other) = 0;
    virtual Ptr operator ++(int) = 0;

    virtual bool operator == (const IAny &other) const = 0;

    virtual void print(std::ostream &os) const = 0;
};
