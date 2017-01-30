#ifndef NUMBER_H
#define NUMBER_H

#include "object.h"

class Number : public Object
{
public:
    Number(double value)
        : value(value)
    {}

    Stream *execute(Object *in);

    std::string to_string();

    static const Object *ArgPlus;
    static const Object *ArgMinus;
    static const Object *ArgMul;
    static const Object *ArgDiv;
    static const Object *ArgMod;

protected:
    double value;
};

#endif // NUMBER_H
