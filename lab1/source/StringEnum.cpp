#include "StringEnum.h"

EnumStringBase globalEnumStringBase;

IEnumStrings::~IEnumStrings() = default;

EnumStringsException::EnumStringsException(const std::__cxx11::string &message)
    : message_{message}
{
}

const char *EnumStringsException::what() const noexcept
{
    return message_.c_str();
}
