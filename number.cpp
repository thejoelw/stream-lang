#include "number.h"

#include "stream.h"
#include "closure.h"

Stream *Number::execute(Object *in)
{
    Stream *res = new Stream();

    if (in == Number::ArgPlus)
    {
        // Return a function that accepts another number and outputs the sum.
    }
    else if (in == Number::ArgMinus)
    {
    }
    else if (in == Number::ArgMul)
    {
    }
    else if (in == Number::ArgDiv)
    {
    }
    else if (in == Number::ArgMod)
    {
    }

    return res;
}

const Object *Number::ArgPlus = new Closure();
const Object *Number::ArgMinus = new Closure();
const Object *Number::ArgMul = new Closure();
const Object *Number::ArgDiv = new Closure();
const Object *Number::ArgMod = new Closure();
