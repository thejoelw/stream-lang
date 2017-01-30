#include "astexpr.h"

void AstExpr::init()
{
    apply_bind(0);
    set_stack_start(0);
}

unsigned int AstExpr::next_js_ident = 0;
