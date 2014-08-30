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

protected:
    AstExpr *func;
    AstExpr *input;
};

#endif // ASTAPPLY_H
