#ifndef ASTFLOW_H
#define ASTFLOW_H

#include "astexpr.h"

class AstFlow : public AstExpr
{
public:
    AstFlow(AstExpr *target, AstExpr *source)
        : target(target)
        , source(source)
    {}

protected:
    AstExpr *target;
    AstExpr *source;
};

#endif // ASTFLOW_H
