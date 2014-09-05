#include "astexpr.h"

void AstExpr::init()
{
    hoist_ident_decl(0);

    BindDesc bind_desc;

    //bind_desc.exp_in = ;
    //bind_desc.exp_out = ;

    //bind_desc.imp_in = ;
    //bind_desc.imp_out = ;

    //bind_desc.auto_out = ;

    bind_desc.stack_start = 1;
    bind_desc.ident_decl = 0;

    apply_bind(bind_desc);
}
