#ifndef ASTEXPR_H
#define ASTEXPR_H

#include <iostream>
#include <string>

class AstExpr
{
public:
    AstExpr()
        : js_ident("_" + std::to_string(++next_js_ident))
    {}

    std::string get_js_ident() const {return js_ident;}

    virtual std::string to_string(unsigned int indent = 0) const = 0;
    //virtual llvm::Value *to_code() = 0;

private:
    std::string js_ident;

    static unsigned int next_js_ident;
};

#endif // ASTEXPR_H
