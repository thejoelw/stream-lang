#include "astblock.h"

#ifndef ASTNODE_H
#define ASTNODE_H

#include <iostream>
#include <string>

//#include "llvm/Analysis/Verifier.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

class AstBlock;
class Stream;
class Context;

class AstExpr
{
public:
    AstExpr()
        : js_ident("_" + std::to_string(++next_js_ident))
    {}

    /*
    virtual ~AstExpr()
    {}
    */

    void init();

    virtual void apply_bind(AstBlock *scope) = 0;
    virtual void set_stack_start(unsigned int stack_size) = 0;

    virtual Stream *execute(Context *context) = 0;

    std::string get_js_ident() const {return js_ident;}

    virtual std::string to_string(unsigned int indent = 0) const = 0;
    //virtual llvm::Value *to_code() = 0;

private:
    std::string js_ident;

    static unsigned int next_js_ident;
};

#endif // ASTNODE_H
