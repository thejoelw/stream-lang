#ifndef ASTFUNCTION_H
#define ASTFUNCTION_H

#include "astexpr.h"

#define TO_STRING_INDENT_CHAR ' '
#define TO_STRING_INDENT_REPEAT 4
#define TO_STRING_EXPR_BREAK "\n"

class AstFunction : public AstExpr
{
public:
    enum Type {TypeMajor, TypeMinor};

    typedef unsigned int BindFlag;

    // Binds the literal in/out keywords to the function's input/output streams:
    // {in => out}
    static constexpr BindFlag BindInOut       = 0x01;

    // Binds implicit relation calls to the function's input/output streams:
    // {-> my_stream}
    // {my_stream =>}
    static constexpr BindFlag BindImplicitRel = 0x02;

    // Binds identifier declarations to a new stream in the current function's scope:
    // {+my_stream}
    static constexpr BindFlag BindIdentDecl   = 0x04;

    // Binds automatic streaming to the function's output stream:
    // [123]
    static constexpr BindFlag BindAutoOut     = 0x08;


    AstFunction(Type type = TypeMajor)
        : type(type)
    {}

    void set_type(Type type)
    {
        this->type = type;
    }

    void add_expr(AstExpr *expr)
    {
        exprs.push_back(expr);
    }

    void bind(BindFlag flag)
    {
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

        switch (type)
        {
        case TypeMajor:
            return "{" + str + indent_block + "}";

        case TypeMinor:
            return "[" + str + indent_block + "]";

        default:
            return std::string("<< Unknown block type >>");
        }
    }

protected:
    Type type;
    std::vector<AstExpr*> exprs;
};

#endif // ASTFUNCTION_H
