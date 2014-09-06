#ifndef CONTEXT_H
#define CONTEXT_H

#include <vector>

class Stream;

class Context : public std::vector<Stream*>
{
    using std::vector<Stream*>::vector;
};

#endif // CONTEXT_H
