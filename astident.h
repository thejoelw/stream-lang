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

    void hoist_ident_decl(AstBlock *scope);
    void apply_bind(BindDesc bind_desc);

    Stream *execute(Context *context);

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

    unsigned int stack_id = 0;
};

#endif // ASTIDENT_H
