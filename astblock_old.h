#ifndef ASTFUNCTION_H
#define ASTFUNCTION_H

#include "astexpr.h"

#define TO_STRING_INDENT_CHAR ' '
#define TO_STRING_INDENT_REPEAT 4
#define TO_STRING_EXPR_BREAK "\n"

class AstBlock : public AstExpr
{
public:
    typedef unsigned int Flags;

    static constexpr Flags implicit_out = 1;

    /*
    friend AstFunction::BindFlag operator|(AstFunction::BindFlag a, AstFunction::BindFlag b);
    friend AstFunction::BindFlag operator&(AstFunction::BindFlag a, AstFunction::BindFlag b);
    friend AstFunction::BindFlag operator^(AstFunction::BindFlag a, AstFunction::BindFlag b);
    friend AstFunction::BindFlag operator~(AstFunction::BindFlag a);
    friend AstFunction::BindFlag operator|=(AstFunction::BindFlag &a, AstFunction::BindFlag b);
    friend AstFunction::BindFlag operator&=(AstFunction::BindFlag &a, AstFunction::BindFlag b);
    friend AstFunction::BindFlag operator^=(AstFunction::BindFlag &a, AstFunction::BindFlag b);
    */

    AstBlock()
    {}

    void add_expr(AstExpr *expr)
    {
        exprs.push_back(expr);
    }

    void set_bind(const Flags flags);

    void apply_bind(AstBlock *scope);
    void set_stack_start(unsigned int stack_size);

    unsigned int hoist_ident(std::string symbol, bool declare);

    Stream *execute(Context *context);

    std::string to_string(unsigned int indent = 0)
    {
        std::string indent_block = std::string(indent * TO_STRING_INDENT_REPEAT, TO_STRING_INDENT_CHAR);
        indent++;
        std::string indent_expr = std::string(indent * TO_STRING_INDENT_REPEAT, TO_STRING_INDENT_CHAR);

        std::string str = TO_STRING_EXPR_BREAK;
        std::vector<AstExpr*>::iterator i = exprs.begin();
        while (i != exprs.end())
        {
            str += indent_expr;
            str += (*i)->to_string(indent);
            str += TO_STRING_EXPR_BREAK;

            i++;
        }

        switch (bind)
        {
        case AstBlock::BindInOut | AstBlock::BindImplicitRel | AstBlock::BindIdentDecl:
            return "{" + str + indent_block + "}";

        case AstBlock::BindImplicitRel | AstBlock::BindAutoOut:
            return "[" + str + indent_block + "]";

        case AstBlock::BindAutoOut:
            return "(" + str + indent_block + ")";

        default:
            return std::string("<< Unknown block type >>");
        }
    }

protected:
    Flags bind = BindNone;

    AstBlock *parent_scope;
    bool bind_ident_decl;
    unsigned int stack_start;
    std::vector<std::string> declared_symbols;

    std::vector<AstExpr*> exprs;
};

#endif // ASTFUNCTION_H
