#ifndef OBJECT_H
#define OBJECT_H

class Stream;

class Object
{
public:
    Object()
    {}

    virtual Stream *execute(Object *in) = 0;
};

#endif // OBJECT_H
