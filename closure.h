#ifndef CLOSURE_H
#define CLOSURE_H

#include <vector>

#include "context.h"

class AstExpr;

class Closure
{
public:
    Closure(std::vector<AstExpr*> &exprs, Context *context)
        : exprs(exprs)
        , context(*context)
    {}

    Stream *execute(Closure *in);

protected:
    std::vector<AstExpr*> &exprs;
    Context context;
};

#endif // CLOSURE_H
