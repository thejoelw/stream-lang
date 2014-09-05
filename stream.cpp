#include "stream.h"

void Stream::apply_from(Closure *in, Stream *out)
{
    std::vector<AstFunction*>::iterator i = funcs.begin();
    while (i != funcs.end())
    {
        AstFunction *func = *i;
        out->flow_from(func->call(in, out));
        i++;
    }
}

void Stream::flow_from(Closure *func)
{
    funcs.push_back(func);

    std::vector<Stream*>::iterator i;

    i = applies_to.begin();
    while (i != applies_to.end())
    {
        i++;
    }
}

void Stream::set_applies_to(Stream *stream, Stream *out)
{
}

void Stream::set_applies_from(Stream *stream, Stream *out)
{
}

void Stream::set_flows_to(Stream *stream, Stream *out)
{
}
