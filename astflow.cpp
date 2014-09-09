#include "astflow.h"

#include "stream.h"

void AstFlow::apply_bind(AstBlock *scope)
{
    source->apply_bind(scope);
    target->apply_bind(scope);
}

void AstFlow::set_stack_start(unsigned int stack_size)
{
    source->set_stack_start(stack_size);
    target->set_stack_start(stack_size);
}

Stream *AstFlow::execute(Context *context)
{
    Stream *source_stream = source->execute(context);
    Stream *target_stream = target->execute(context);

    source_stream->set_flows_to(target_stream);
    target_stream->set_flows_from(source_stream);

    return source_stream;
}
