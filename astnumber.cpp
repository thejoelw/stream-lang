#include "astnumber.h"

void AstNumber::apply_bind(AstBlock *scope)
{
}

void AstNumber::set_stack_start(unsigned int stack_size)
{
}

Stream *AstNumber::execute(Context *context)
{
    Stream *res = new Stream();

    Closure *closure = 0;
    // TODO: Make closure actually a number

    res->flow_from(closure);

    return res;
}
