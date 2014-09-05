#include "astident.h"

void AstIdent::hoist_ident_decl(AstBlock *scope)
{
    if (declare)
    {
        scope->add_decl(symbol);
    }
}

void AstIdent::apply_bind(BindDesc bind_desc)
{
    stack_id = bind_desc.ident_decl->resolve_ident(symbol);
}

Stream *AstIdent::execute(Context *context)
{
    return context->resolve(stack_id);
}

AstIdent * const AstIdent::ImplicitIn = new AstIdent("/* << implicit in >> */");
AstIdent * const AstIdent::ImplicitOut = new AstIdent("/* << implicit out >> */");
