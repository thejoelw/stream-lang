#ifndef ASTFUNCTION_H
#define ASTFUNCTION_H

#include "astexpr.h"

#include "stream.h"

#define TO_STRING_INDENT_CHAR ' '
#define TO_STRING_INDENT_REPEAT 4
#define TO_STRING_EXPR_BREAK "\n"

class AstBlock : public AstExpr
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

    // Binds automatic streaming to the function's output stream:
    // [123]
    static constexpr BindFlags BindAutoOut     = 1 << 2;

    // Binds identifier declarations to a new stream in the current function's scope:
    // {+my_stream}
    static constexpr BindFlags BindIdentDecl   = 1 << 3;

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

    void set_bind(const BindFlags flags);

    void hoist_ident_decl(AstBlock *scope);
    void apply_bind(BindDesc bind_desc);

    Stream *execute(Context *context);

    void add_decl(std::string symbol);
    unsigned int resolve_ident(std::string symbol);

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
    BindFlags bind = BindNone;

    AstBlock *parent_scope;
    unsigned int stack_start;
    std::vector<std::string> declared_symbols;

    Stream *in_stream;
    Stream *out_stream;

    std::vector<AstExpr*> exprs;
};

#endif // ASTFUNCTION_H
