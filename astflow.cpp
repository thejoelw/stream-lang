#include "astflow.h"

void AstFlow::hoist_ident_decl(AstBlock *scope)
{
    source->hoist_ident_decl(scope);
    target->hoist_ident_decl(scope);
}

void AstFlow::apply_bind(BindDesc bind_desc)
{
    source->apply_bind(bind_desc);
    target->apply_bind(bind_desc);
}

Stream *AstFlow::execute(Context *context)
{
    Stream *res = new Stream();

    Stream *source_stream = source->execute(context);
    Stream *target_stream = target->execute(context);

    source_stream->set_flows_to(target_stream, res);

    return res;
}
