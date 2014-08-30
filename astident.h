#ifndef ASTIDENT_H
#define ASTIDENT_H

#include "astexpr.h"

class AstIdent : public AstExpr
{
public:
    AstIdent(std::string symbol, bool declare = false)
        : symbol(symbol)
        , declare(declare)
    {}

    std::string to_string(unsigned int indent = 0)
    {
        if (declare) {return "+" + symbol;}
        else {return symbol;}
    }

    static AstIdent * const ImplicitIn;
    static AstIdent * const ImplicitOut;

protected:
    std::string symbol;
    bool declare;
};

#endif // ASTIDENT_H
