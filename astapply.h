#ifndef ASTAPPLY_H
#define ASTAPPLY_H

#include "astexpr.h"

class AstApply : public AstExpr
{
public:
    AstApply(AstExpr *func, AstExpr *input)
        : func(func)
        , input(input)
    {}

    std::string to_string(unsigned int indent = 0)
    {
        return "(" + func->to_string(indent) + " <- " + input->to_string(indent) + ")";
    }

protected:
    AstExpr *func;
    AstExpr *input;
};

#endif // ASTAPPLY_H
