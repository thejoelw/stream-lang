#ifndef ASTBLOCK_H
#define ASTBLOCK_H

#include "astexpr.h"

class AstBlock : public AstExpr
{
public:
    enum Type {TYPE_MAJOR, TYPE_MINOR};

    AstBlock(Type type = TYPE_MAJOR)
        : type(type)
    {}

    void set_type(Type type)
    {
        this->type = type;
    }

    void add_expr(AstExpr *expr)
    {
        exprs.push_back(expr);
    }

protected:
    Type type;
    std::vector<AstExpr*> exprs;
};

#endif // ASTBLOCK_H
