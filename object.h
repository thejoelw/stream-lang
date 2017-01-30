#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class Stream;

class Object
{
public:
    Object()
    {}

    virtual Stream *execute(Object *in) = 0;
    virtual std::string to_string() = 0;

    static const Object *ArgDebug;
};

#endif // OBJECT_H
