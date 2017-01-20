#include <string>
std::string operator ++(std::string &string, int){
    return string;
}

#include "WrapAny.h"
#include <vector>
#include <iterator>
#include <list>
#include <algorithm>
#include "MyUniquePTR.h"


int main()
{
    WrapAny n1(1);
    WrapAny n2(2);
    WrapAny n3(3);

    n1 += n2;
    n3 = n1 + n2;

    WrapAny d1(1.1);
    WrapAny d2(2.2);
    WrapAny d3(3.3);

    d1 += d2;
    d3 = d1 + d2;

    WrapAny s1(std::string("AAA"));
    WrapAny s2(std::string("BBB"));
    WrapAny s3(std::string("CCC"));

    s1 += s2;
    s3 = s1 + s2;

    std::vector<WrapAny> v;
    v.push_back(WrapAny(33));
    v.push_back(WrapAny(5.5));
    v.push_back(WrapAny(std::string("aa")));

    for (const auto& x : v) { std::cout << x <<' '; }

    auto it = std::find(v.cbegin(), v.cend(), WrapAny(33));

    {
        MyUniquePTR<std::string> p1(new std::string("test"));
        std::cout << p1->c_str();
        std::string a = *p1;
        //MyUniquePTR<A> p2=p1; //здесь компилятор должен выдавать ошибку
        MyUniquePTR<std::string> p3(new std::string("test2"));
        MyUniquePTR<std::string> p4(std::move(p3));
        //p3 = p2; //и здесь компилятор должен выдавать ошибку
        std::vector< MyUniquePTR<std::string>> v; //как проинициализировать???
        for (const std::string &line: {"my", "unique", "lines"}){
            v.push_back(makeUnique(line));
        }
        std::list< MyUniquePTR<std::string>> l;
        //как скопировать из v в l ???
        for (const auto &value: v){
            l.push_back(makeUnique(*value));
        }
        std::cout << std::endl;
    }

    return 0;
}

