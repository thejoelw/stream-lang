#include "astblock.h"

/*
AstBlock::BindFlag operator|(AstFunction::BindFlag a, AstFunction::BindFlag b)
{ return static_cast<AstFunction::BindFlag>(static_cast<int>(a) | static_cast<int>(b)); }

AstBlock::BindFlag operator&(AstFunction::BindFlag a, AstFunction::BindFlag b)
{ return static_cast<AstFunction::BindFlag>(static_cast<int>(a) & static_cast<int>(b)); }

AstBlock::BindFlag operator^(AstFunction::BindFlag a, AstFunction::BindFlag b)
{ return static_cast<AstFunction::BindFlag>(static_cast<int>(a) ^ static_cast<int>(b)); }

AstBlock::BindFlag operator~(AstFunction::BindFlag a)
{ return static_cast<AstFunction::BindFlag>(~static_cast<int>(a)); }

AstBlock::BindFlag operator|=(AstFunction::BindFlag &a, AstFunction::BindFlag b)
{ return a = static_cast<AstFunction::BindFlag>(static_cast<int>(a) | static_cast<int>(b)); }

AstBlock::BindFlag operator&=(AstFunction::BindFlag &a, AstFunction::BindFlag b)
{ return a = static_cast<AstFunction::BindFlag>(static_cast<int>(a) & static_cast<int>(b)); }

AstBlock::BindFlag operator^=(AstFunction::BindFlag &a, AstFunction::BindFlag b)
{ return a = static_cast<AstFunction::BindFlag>(static_cast<int>(a) ^ static_cast<int>(b)); }
*/

void AstBlock::set_bind(const BindFlags flags)
{
    bind |= flags;
}

void AstBlock::hoist_ident_decl(AstBlock *scope)
{
    parent_scope = scope;

    if (bind & BindIdentDecl)
    {
        scope = this;
    }

    std::vector<AstExpr*>::iterator i = exprs.begin();
    while (i != exprs.end())
    {
        (*i)->hoist_ident_decl(scope);
        i++;
    }
}

void AstBlock::apply_bind(BindDesc bind_desc)
{
    stack_start = bind_desc.stack_start;
    bind_desc.stack_start += declared_symbols.size();

    if (bind & BindInOut)
    {
        //bind_desc.exp_in = 12345678;
    }

    if (bind & BindImplicitRel)
    {

    }

    if (bind & BindAutoOut)
    {

    }

    if (bind & BindIdentDecl)
    {
        hoist_ident_decl(this);
        bind_desc.ident_decl = this;
    }

    /*
    struct BindDesc
    {
        Stream *exp_in;
        Stream *exp_out;

        Stream *imp_in;
        Stream *imp_out;

        Stream *auto_out;

        unsigned int stack_start;
        AstFunction *ident_decl;
    };
    */

    std::vector<AstExpr*>::iterator i = exprs.begin();
    while (i != exprs.end())
    {
        (*i)->apply_bind(bind_desc);
        i++;
    }
}

Stream *AstBlock::execute(Context *context)
{
    Closure *closure = new Closure(this, context);

    Stream *res = new Stream();
    res->add_func(func);
    return res;
}

void AstBlock::call(Context *context)
{
    Context *new_context = context->new_frame(declared_symbols.size());

    Stream *res = new Stream();

    std::vector<AstExpr*>::iterator i = exprs.begin();
    while (i != exprs.end())
    {
        (*i)->execute(new_context)->set_flows_to(res);
        i++;
    }

    return res;
}


void AstBlock::add_decl(std::string symbol)
{
    declared_symbols.push_back(symbol);
}

unsigned int AstBlock::resolve_ident(std::string symbol)
{
    std::vector<std::string>::iterator i = declared_symbols.begin();
    while (i != declared_symbols.end())
    {
        if (*i == symbol)
        {
            return stack_start + (i - declared_symbols.begin());
        }
        i++;
    }

    if (parent_scope)
    {
        return parent_scope->resolve_ident(symbol);
    }
    else
    {
        std::cerr << "Identifier \"" << symbol << "\" not declared in this scope." << std::endl;
        return 0;
    }
}
