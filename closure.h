#ifndef CLOSURE_H
#define CLOSURE_H

#include <vector>

#include "astblock.h"
#include "context.h"
#include "stream.h"

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
