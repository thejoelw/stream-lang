#ifndef BIGNUM_H
#define BIGNUM_H

#include <cstdint>

class BigNum
{
public:
    BigNum();

    virtual std::int_fast8_t cmp(const BigNum &op, bool ignore_lt = false, bool ignore_gt = false) = 0;
};


#include <string>
#include <vector>

class BigNumDiscrete
{
public:
    BigNumDiscrete()
    {}

    /*
    bool from_string(std::string num, unsigned int base)
    {
        std::string::iterator i = num.crbegin();

        std::uint64_t cur = 0;
        std::uint64_t prod = 1;
        while (i != num.crend())
        {
            unsigned int digit = *i - '0';
            if (digit >= base) {return false;}

            cur += digit * prod;
            prod *= base;

            if (prod > 0xFFFFFFFF)
            {

            }

            i++;
        }

        negative = (i != num.cend() && *i == '-');
        if (negative) {i++;}

        while (i != num.cend())
        {

            i++;
        }
    }
    */

    bool negative;
    std::vector<std::uint32_t> parts;
};

#endif // BIGNUM_H
