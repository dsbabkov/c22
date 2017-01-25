#pragma once
#include <iostream>

class Book{
    std::string author_;
    std::string title_;
    unsigned year_;
public:
    Book(const std::string &author, const std::string &title, unsigned year)
        : author_{author},
          title_{title},
          year_{year}
    {}
    std::string author() const {return author_;}
//        void setAuthor(const std::string &author);
    std::string title() const {return title_;}
//        void setTitle(const std::string &title);
    unsigned year() const {return year_;}
//        void setYear(const unsigned &year);
};

