#include "WrapAny.h"

WrapAny::WrapAny(const WrapAny &other)
    : any_{other.any_->clone()}
{
}

WrapAny::~WrapAny() = default;

WrapAny &WrapAny::operator =(const WrapAny &other)
{
    if (this == &other){
        return *this;
    }

    *any_ = *other.any_;
    return *this;
}

WrapAny WrapAny::operator +(const WrapAny &other) const
{
    return WrapAny(*any_ + *other.any_);
}

WrapAny &WrapAny::operator +=(const WrapAny &other)
{
    *any_ += *other.any_;
    return *this;
}

WrapAny WrapAny::operator ++(int)
{
    return {(*any_)++};
}

bool WrapAny::operator ==(const WrapAny &other) const
{
    return *any_ == *other.any_;
}

WrapAny::WrapAny(IAny::Ptr any)
    : any_(std::move(any))
{
}

void WrapAny::print(std::ostream &os) const
{
    any_->print(os);
}

std::ostream &operator << (std::ostream &os, const WrapAny &any){
    any.print(os);
    return os;
}
