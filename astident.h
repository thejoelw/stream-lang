#ifndef ASTIDENT_H
#define ASTIDENT_H

#include "astexpr.h"

class AstIdent : public AstExpr
{
public:
    enum class Type {DeclPrivate, DeclPublic, Unbound, Reference};

    AstIdent(std::string symbol, Type type)
        : symbol(symbol)
        , type(type)
    {}

    void apply_bind(AstBlock *scope);
    void set_stack_start(unsigned int stack_size);

    Stream *execute(Context *context);

    std::string to_string(unsigned int indent = 0)
    {
        switch (type) {
            case Type::DeclPrivate: return "-" + symbol;
            case Type::DeclPublic: return "+" + symbol;
            case Type::Unbound: return "." + symbol;
            case Type::Reference: return symbol;
        }
    }

    static const std::string ImplicitIn;
    static const std::string ImplicitOut;
    static const std::string AutoOut;

protected:
    std::string symbol;
    Type type;

    unsigned int stack_id = 0;
};

#endif // ASTIDENT_H
