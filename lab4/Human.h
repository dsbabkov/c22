#pragma once

#include <string>
#include <set>
#include <memory>
#include <cassert>
#include <iostream>
#include <algorithm>

class Human: public std::enable_shared_from_this<Human>{
    struct WeakPtrHumanCompare{
        bool operator() (const std::weak_ptr<Human> &left, const std::weak_ptr<Human> &right) const{
            return left.lock().get() < right.lock().get();
        }
    };

    std::string name_;
//    bool isAlive_;
    std::shared_ptr <Human> mom_;
    std::shared_ptr <Human> dad_;
    std::set<std::weak_ptr<Human>, WeakPtrHumanCompare> children_;

public:
    explicit Human(const std::string &name, bool /*isAlive*/ = true)
        : name_{name}
//        , isAlive_{isAlive_}
        , mom_{}
        , dad_{}
        , children_{}
    {}

    Human(const Human &) = default;
    Human(Human &&) = default;
    Human &operator = (const Human &) = default;
    Human &operator = (Human &&) = default;

    static std::shared_ptr<Human> child(const std::string &name, const std::shared_ptr<Human> &mom = {}, const std::shared_ptr<Human> &dad = {}){
        auto result = std::make_shared<Human>(name);
        result->setMom(mom);
        result->setDad(dad);
        return result;
    }

    void printTree(unsigned tab = 0) const;

private:
    void setParent(std::shared_ptr<Human> &parent, const std::shared_ptr<Human> &newParent){
        assert(parent == mom_ || parent == dad_);

        if (parent){
            parent->children_.erase(shared_from_this());
        }
        parent = newParent;
        if (parent){
            newParent->children_.insert(shared_from_this());
        }
    }

    void setMom(const std::shared_ptr<Human> &mom){
        setParent(mom_, mom);
    }

    void setDad(const std::shared_ptr<Human> &dad){
        setParent(dad_, dad);
    }
};

void Human::printTree(unsigned tab) const{
    for (unsigned i = 0; i < tab; ++i){
        std::cout << ' ';
    }

    std::cout << name_ << '\n';
    for (const std::weak_ptr<Human> &child: children_){
        child.lock()->printTree(tab + 1);
    }
}
