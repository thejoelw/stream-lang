#include "astsame.h"

#include <set>

#include "stream.h"

void AstSame::apply_bind(AstBlock *scope)
{
    op1->apply_bind(scope);
    op2->apply_bind(scope);
}

void AstSame::set_stack_start(unsigned int stack_size)
{
    op1->set_stack_start(stack_size);
    op2->set_stack_start(stack_size);
}

Stream *AstSame::execute(Context *context)
{
    Stream *res = new Stream();

    Stream *op1_stream = op1->execute(context);
    Stream *op2_stream = op2->execute(context);

    std::set<Object*> set;

    std::vector<Object*>::const_iterator i;

    i = op1_stream->get_vector().cbegin();
    while (i != op1_stream->get_vector().cend())
    {
        set.insert(*i);
        i++;
    }

    i = op2_stream->get_vector().cbegin();
    while (i != op2_stream->get_vector().cend())
    {
        if (set.count(*i))
        {
            res->flow_from(*i);
        }

        i++;
    }

    return res;
}
