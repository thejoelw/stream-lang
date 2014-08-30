#ifndef ASTNUMBER_H
#define ASTNUMBER_H

#include "astexpr.h"

class AstNumber : public AstExpr
{
public:
    AstNumber(std::string number)
        : number(number)
    {}

protected:
    std::string number;
};

#endif // ASTNUMBER_H
