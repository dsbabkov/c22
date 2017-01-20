#pragma once

#include <map>
#include <string>
#include <initializer_list>
#include <memory>
#include <exception>
#include <typeinfo>

class IEnumStrings{
public:
    virtual ~IEnumStrings();
};

class EnumStringBase{
    template <typename Enum>
    friend void DeclareEnumStrings(const std::map<std::string, Enum> &);
    template <typename Enum>
    friend Enum stringToEnum (const std::string &string);
    template <typename Enum>
    friend std::string enumToString(const Enum &value);

private:
    std::map<const char *, std::unique_ptr<IEnumStrings>> records_;
};

class EnumStringsException: public std::exception
{
public:
    explicit EnumStringsException(const std::string &message = {});
    virtual const char *what() const noexcept override;
private:
    std::string message_;
};

extern EnumStringBase globalEnumStringBase;

template <typename T>
class EnumStrings: public IEnumStrings{
    using StringMap = std::map<std::string, T>;
public:
    EnumStrings(const StringMap &map)
        : map_{map}
    {}
    EnumStrings(const EnumStrings &) = default;
    EnumStrings(EnumStrings &&) = default;
    EnumStrings &operator =(const EnumStrings &) = default;
    EnumStrings &operator =(EnumStrings &&) = default;

    T stringToEnum(const std::string &string) const{
        try{
            return map_.at(string);
        }
        catch (const std::out_of_range &){
            throw EnumStringsException("Key \"" + string + "\" not found");
        }
    }

    std::string enumToString(const T &value) const{
        for (const auto &pair: map_){
            if (pair.second == value){
                return pair.first;
            }
        }
        throw EnumStringsException("String value for enum value not found");
    }

private:
     StringMap map_;
};

template <typename Enum>
void DeclareEnumStrings(const std::map<std::string, Enum> &map){
    globalEnumStringBase.records_[typeid(EnumStrings<Enum>).name()].reset(new EnumStrings<Enum>(map));
}

template <typename Enum>
Enum stringToEnum (const std::string &string){
    const EnumStrings<Enum> *enumStrings = reinterpret_cast<const EnumStrings<Enum> *>(
                globalEnumStringBase.records_.at(typeid(EnumStrings<Enum>).name()).get());
    return enumStrings->stringToEnum(string);
}

template <typename Enum>
std::string enumToString(const Enum &value){
    const EnumStrings<Enum> *enumStrings = reinterpret_cast<const EnumStrings<Enum> *>(
                globalEnumStringBase.records_.at(typeid(EnumStrings<Enum>).name()).get());
    return enumStrings->enumToString(value);
}
