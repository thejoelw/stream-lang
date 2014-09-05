#ifndef CLOSURE_H
#define CLOSURE_H

#include <vector>

#include "astblock.h"
#include "context.h"

class AstBlock;

class Closure
{
public:
    Closure(AstBlock *func, Context *context)
        : func(func)
        , context(*context)
    {}

protected:
    AstBlock *func;
    Context context;
};

#endif // CLOSURE_H
