#ifndef ASTSAME_H
#define ASTSAME_H

#include "astexpr.h"

class AstSame : public AstExpr
{
public:
    AstSame(AstExpr *op1, AstExpr *op2)
        : op1(op1)
        , op2(op2)
    {}

    void apply_bind(AstBlock *scope);
    void set_stack_start(unsigned int stack_size);

    Stream *execute(Context *context);

    std::string to_string(unsigned int indent = 0)
    {
        return "(" + op1->to_string(indent) + " == " + op2->to_string(indent) + ")";
    }

protected:
    AstExpr *op1;
    AstExpr *op2;
};

#endif // ASTSAME_H
