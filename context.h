#ifndef CONTEXT_H
#define CONTEXT_H

#include <vector>

#include "stream.h"

class Stream;

class Context
{
public:
    Context();

    void enter_frame(unsigned int size);
    void leave_frame(unsigned int size);

    Stream *resolve(unsigned int i);

protected:
    Context(std::vector<Stream*> stack)
        : stack(stack)
    {}

    std::vector<Stream*> stack;
};

#endif // CONTEXT_H
