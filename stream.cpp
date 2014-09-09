#include "stream.h"

#include "closure.h"

Stream *Stream::apply_to(Object *func)
{
    Stream *res = new Stream();

    std::vector<Object*>::iterator i = funcs.begin();
    while (i != funcs.end())
    {
        func->execute(*i)->set_flows_to(res);
        i++;
    }

    return res;
}

Stream *Stream::apply_from(Object *func)
{
    Stream *res = new Stream();

    std::vector<Object*>::iterator i = funcs.begin();
    while (i != funcs.end())
    {
        (*i)->execute(func)->set_flows_to(res);
        i++;
    }

    return res;
}

void Stream::flow_from(Object *func)
{
    // Add a single Closure to this stream.

    funcs.push_back(func);

    std::vector<Stream*>::iterator i;

    i = applies_to.begin();
    while (i != applies_to.end())
    {
        (*i)->apply_from(func);
        i++;
    }

    i = applies_from.begin();
    while (i != applies_from.end())
    {
        (*i)->apply_to(func);
        i++;
    }

    i = flows_to.begin();
    while (i != flows_to.end())
    {
        (*i)->flow_from(func);
        i++;
    }
}

void Stream::set_applies_to(Stream *stream, Stream *out)
{
    std::vector<Object*>::iterator i = funcs.begin();
    while (i != funcs.end())
    {
        stream->apply_from(*i)->set_flows_to(out);
        i++;
    }

    applies_to.push_back(stream);
}

void Stream::set_applies_from(Stream *stream, Stream *out)
{
    std::vector<Object*>::iterator i = funcs.begin();
    while (i != funcs.end())
    {
        stream->apply_to(*i)->set_flows_to(out);
        i++;
    }

    applies_from.push_back(stream);
}

void Stream::set_flows_to(Stream *stream)
{
    std::vector<Object*>::iterator i = funcs.begin();
    while (i != funcs.end())
    {
        stream->flow_from(*i);
        i++;
    }

    flows_to.push_back(stream);
}

void Stream::set_flows_from(Stream *stream)
{
    // Nothing to do here
}
