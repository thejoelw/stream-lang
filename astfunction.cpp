#include "astfunction.h"

/*
AstFunction::BindFlag operator|(AstFunction::BindFlag a, AstFunction::BindFlag b)
{ return static_cast<AstFunction::BindFlag>(static_cast<int>(a) | static_cast<int>(b)); }

AstFunction::BindFlag operator&(AstFunction::BindFlag a, AstFunction::BindFlag b)
{ return static_cast<AstFunction::BindFlag>(static_cast<int>(a) & static_cast<int>(b)); }

AstFunction::BindFlag operator^(AstFunction::BindFlag a, AstFunction::BindFlag b)
{ return static_cast<AstFunction::BindFlag>(static_cast<int>(a) ^ static_cast<int>(b)); }

AstFunction::BindFlag operator~(AstFunction::BindFlag a)
{ return static_cast<AstFunction::BindFlag>(~static_cast<int>(a)); }

AstFunction::BindFlag operator|=(AstFunction::BindFlag &a, AstFunction::BindFlag b)
{ return a = static_cast<AstFunction::BindFlag>(static_cast<int>(a) | static_cast<int>(b)); }

AstFunction::BindFlag operator&=(AstFunction::BindFlag &a, AstFunction::BindFlag b)
{ return a = static_cast<AstFunction::BindFlag>(static_cast<int>(a) & static_cast<int>(b)); }

AstFunction::BindFlag operator^=(AstFunction::BindFlag &a, AstFunction::BindFlag b)
{ return a = static_cast<AstFunction::BindFlag>(static_cast<int>(a) ^ static_cast<int>(b)); }
*/

void AstFunction::bind(BindFlags flag)
{
    flag &= ~bound;
    bound |= flag;

    if (flag & BindInOut)
    {
    }

    if (flag & BindImplicitRel)
    {
    }

    if (flag & BindIdentDecl)
    {
    }

    if (flag & BindAutoOut)
    {
    }
}

void AstFunction::call(AstFunction *in, Stream *out)
{
    std::vector<AstExpr*>::iterator i = exprs.begin();
    while (i != exprs.end())
    {
        i++;
    }
}
