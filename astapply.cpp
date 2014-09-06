#include "astapply.h"

#include "stream.h"

void AstApply::apply_bind(AstBlock *scope)
{
    func->apply_bind(scope);
    input->apply_bind(scope);
}

void AstApply::set_stack_start(unsigned int stack_size)
{
    func->set_stack_start(stack_size);
    input->set_stack_start(stack_size);
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
