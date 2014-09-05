#ifndef ASTNUMBER_H
#define ASTNUMBER_H

#include "astexpr.h"

class AstNumber : public AstExpr
{
public:
    AstNumber(std::string number)
        : number(number)
    {}

    void apply_bind(AstBlock *scope);
    void set_stack_start(unsigned int stack_size);

    Stream *execute(Context *context);

    std::string to_string(unsigned int indent = 0)
    {
        return number;
    }

protected:
    std::string number;
};

#endif // ASTNUMBER_H
