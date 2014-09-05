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

    void hoist_ident_decl(AstBlock *scope);
    void apply_bind(BindDesc bind_desc);

    Stream *execute(Context *context);

    std::string to_string(unsigned int indent = 0)
    {
        return "(" + target->to_string(indent) + " <= " + source->to_string(indent) + ")";
    }

protected:
    AstExpr *target;
    AstExpr *source;
};

#endif // ASTFLOW_H
