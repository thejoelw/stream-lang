#ifndef ASTIDENT_H
#define ASTIDENT_H

#include "astexpr.h"

class AstIdent : public AstExpr
{
public:
    AstIdent(std::string symbol, bool declare = false)
        : symbol(symbol)
    {}

protected:
    std::string symbol;
    bool declare;
};

#endif // ASTIDENT_H
