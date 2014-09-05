#include "context.h"

Context *Context::new_frame(unsigned int push_size)
{
    Context *res = new Context(stack);

    Stream *add = new Stream[push_size];
    Stream *add_end = add + push_size;

    while (add < add_end)
    {
        res->stack.push_back(add);
        add++;
    }

    return res;
}

Stream *Context::resolve(unsigned int i)
{
    assert(i < stack.size());
    return stack[i];
}
