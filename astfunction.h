#ifndef ASTFUNCTION_H
#define ASTFUNCTION_H

#include "astexpr.h"

#define TO_STRING_INDENT_CHAR ' '
#define TO_STRING_INDENT_REPEAT 4
#define TO_STRING_EXPR_BREAK "\n"

class AstFunction : public AstExpr
{
public:
    typedef unsigned int BindFlags;

    static constexpr BindFlags BindNone        = 0;

    // Binds the literal in/out keywords to the function's input/output streams:
    // {in => out}
    static constexpr BindFlags BindInOut       = 1 << 0;

    // Binds implicit relation calls to the function's input/output streams:
    // {-> my_stream}
    // {my_stream =>}
    static constexpr BindFlags BindImplicitRel = 1 << 1;

    // Binds identifier declarations to a new stream in the current function's scope:
    // {+my_stream}
    static constexpr BindFlags BindIdentDecl   = 1 << 2;

    // Binds automatic streaming to the function's output stream:
    // [123]
    static constexpr BindFlags BindAutoOut     = 1 << 3;

    /*
    friend AstFunction::BindFlag operator|(AstFunction::BindFlag a, AstFunction::BindFlag b);
    friend AstFunction::BindFlag operator&(AstFunction::BindFlag a, AstFunction::BindFlag b);
    friend AstFunction::BindFlag operator^(AstFunction::BindFlag a, AstFunction::BindFlag b);
    friend AstFunction::BindFlag operator~(AstFunction::BindFlag a);
    friend AstFunction::BindFlag operator|=(AstFunction::BindFlag &a, AstFunction::BindFlag b);
    friend AstFunction::BindFlag operator&=(AstFunction::BindFlag &a, AstFunction::BindFlag b);
    friend AstFunction::BindFlag operator^=(AstFunction::BindFlag &a, AstFunction::BindFlag b);
    */

    AstFunction()
    {}

    void add_expr(AstExpr *expr)
    {
        exprs.push_back(expr);
    }

    void bind(BindFlags flag)
    {
        flag &= ~bound;
        bound |= flag;

        if (flag & BindInOut)
        {
        }

        if (flag & BindImplicitRel)
        {
        }

        if (flag & BindIdentDecl)
        {
        }

        if (flag & BindAutoOut)
        {
        }
    }

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

        switch (bound)
        {
        case AstFunction::BindInOut | AstFunction::BindImplicitRel | AstFunction::BindIdentDecl:
            return "{" + str + indent_block + "}";

        case AstFunction::BindImplicitRel | AstFunction::BindAutoOut:
            return "[" + str + indent_block + "]";

        case AstFunction::BindAutoOut:
            return "(" + str + indent_block + ")";

        default:
            return std::string("<< Unknown block type >>");
        }
    }

protected:
    BindFlags bound = BindNone;
    std::vector<AstExpr*> exprs;
};

#endif // ASTFUNCTION_H
