#include "astblock.h"

#ifndef ASTNODE_H
#define ASTNODE_H

#include <iostream>
#include <string>

#include "llvm/Analysis/Verifier.h"
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
    {}

    virtual ~AstExpr()
    {}

    void init();

    virtual void apply_bind(AstBlock *scope) = 0;
    virtual void set_stack_start(unsigned int stack_size) = 0;

    virtual Stream *execute(Context *context) = 0;

    virtual std::string to_string(unsigned int indent = 0) = 0;
    //virtual llvm::Value *to_code() = 0;
};

#endif // ASTNODE_H
