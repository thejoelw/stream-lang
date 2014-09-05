#include "astapply.h"

void AstApply::hoist_ident_decl(AstBlock *scope)
{
    func->hoist_ident_decl(scope);
    input->hoist_ident_decl(scope);
}

void AstApply::apply_bind(BindDesc bind_desc)
{
    func->apply_bind(bind_desc);
    input->apply_bind(bind_desc);
}

Stream *AstApply::execute(Context *context)
{
    Stream *res = new Stream();

    Stream *func_stream = func->execute(context);
    Stream *input_stream = input->execute(context);

    func_stream->set_applies_from(input_stream, res);
    input_stream->set_applies_to(func_stream, res);

    return res;
}
