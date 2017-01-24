#pragma once

#include <stdexcept>
#include <array>
#include <climits>

class ConstBit{
    unsigned char bit0_:1;
    unsigned char bit1_:1;
    unsigned char bit2_:1;
    unsigned char bit3_:1;
    unsigned char bit4_:1;
    unsigned char bit5_:1;
    unsigned char bit6_:1;
    unsigned char bit7_:1;

    static constexpr uint nBits = 8;

public:
    constexpr ConstBit (unsigned char ch)
        : bit0_{static_cast<unsigned char>((ch >> 0) & 1)}
        , bit1_{static_cast<unsigned char>((ch >> 1) & 1)}
        , bit2_{static_cast<unsigned char>((ch >> 2) & 1)}
        , bit3_{static_cast<unsigned char>((ch >> 3) & 1)}
        , bit4_{static_cast<unsigned char>((ch >> 4) & 1)}
        , bit5_{static_cast<unsigned char>((ch >> 5) & 1)}
        , bit6_{static_cast<unsigned char>((ch >> 6) & 1)}
        , bit7_{static_cast<unsigned char>((ch >> 7) & 1)}
    {
    }

    constexpr bool bit(uint n) const{
        if (n >= nBits){
            throw std::invalid_argument("Bad bit number got");
        }


        return charArray()[n];
    }

private:
    constexpr std::array<unsigned char, nBits> charArray() const{
        return {{
            bit0_,
            bit1_,
            bit2_,
            bit3_,
            bit4_,
            bit5_,
            bit6_,
            bit7_
        }};
    }
};
