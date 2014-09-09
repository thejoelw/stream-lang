#include "astnumber.h"

#include "stream.h"
#include "number.h"

void AstNumber::apply_bind(AstBlock *scope)
{
}

void AstNumber::set_stack_start(unsigned int stack_size)
{
}

Stream *AstNumber::execute(Context *context)
{
    Stream *res = new Stream();

    Object *closure = new Number(stod(number));
    res->flow_from(closure);

    return res;
}
