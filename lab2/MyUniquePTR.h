#pragma once

template <typename T>
class MyUniquePTR{
public:
    explicit MyUniquePTR(T *p = {})
        : p_{p}
    {}

    MyUniquePTR (MyUniquePTR && other)
        : p_{other.p_}
    {
        other.p_ = {};
    }
    MyUniquePTR &operator = (MyUniquePTR &&other){
        delete p_;
        p_ = other.p_;
        other.p_ = {};
    }

    ~MyUniquePTR(){
        delete p_;
    }

    MyUniquePTR (const MyUniquePTR &) = delete;
    MyUniquePTR &operator = (const MyUniquePTR &) = delete;

    T *operator-> () const {
        return p_;
    }
    T &operator* () const {
        return *p_;
    }

private:
    T *p_;
};

template <typename T>
MyUniquePTR<T> makeUnique(const T &value = {}){
    return MyUniquePTR<T>(new T(value));
}
