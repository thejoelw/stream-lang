#include "astident.h"

void AstIdent::apply_bind(AstBlock *scope)
{
    stack_id = scope->hoist_ident(symbol, declare);
}

void AstIdent::set_stack_start(unsigned int stack_size)
{
}

Stream *AstIdent::execute(Context *context)
{
    return (*context)[stack_id];
}

const std::string AstIdent::ImplicitIn = "/* << implicit in >> */";
const std::string AstIdent::ImplicitOut = "/* << implicit out >> */";
const std::string AstIdent::AutoOut = "/* << auto out >> */";
