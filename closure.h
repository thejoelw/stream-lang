#ifndef CLOSURE_H
#define CLOSURE_H

#include <vector>

#include "object.h"
#include "context.h"

class AstExpr;

class Closure : public Object
{
public:
    Closure()
        : num_decls(0)
    {}

    Closure(std::vector<AstExpr*> exprs, unsigned int num_decls, Context *context)
        : exprs(exprs)
        , num_decls(num_decls)
        , context(*context)
    {}

    Stream *execute(Object *in);

    std::string to_string();

protected:
    unsigned int num_decls;
    std::vector<AstExpr*> exprs;
    Context context;
};

#endif // CLOSURE_H
