#ifndef ASTCOMPOSE_H
#define ASTCOMPOSE_H

#include "astexpr.h"

class AstCompose : public AstExpr
{
public:
    AstCompose(AstExpr *left, AstExpr *right)
        : left(left)
        , right(right)
    {}

    void apply_bind(AstBlock *scope);
    void set_stack_start(unsigned int stack_size);

    Stream *execute(Context *context);

    std::string to_string(unsigned int indent = 0) const
    {
        return "(" + left->to_string(indent) + " " + right->to_string(indent) + ")";
    }

    std::string to_js() const {
        return "let " + get_js_ident() + " = compose(" + left->get_js_ident() + ", " + right->get_js_ident() + ");\n";
    }

protected:
    AstExpr *left;
    AstExpr *right;
};

#endif // ASTCOMPOSE_H
