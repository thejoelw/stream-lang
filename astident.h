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

    void apply_bind(AstBlock *scope);
    void set_stack_start(unsigned int stack_size);

    Stream *execute(Context *context);

    std::string to_string(unsigned int indent = 0)
    {
        if (declare) {return "+" + symbol;}
        else {return symbol;}
    }

    static const std::string ImplicitIn;
    static const std::string ImplicitOut;
    static const std::string AutoOut;

protected:
    std::string symbol;
    bool declare;

    unsigned int stack_id = 0;
};

#endif // ASTIDENT_H
