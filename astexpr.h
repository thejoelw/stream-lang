#ifndef ASTNODE_H
#define ASTNODE_H

#include <iostream>

#include "llvm/Analysis/Verifier.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

class AstExpr
{
public:
    AstExpr()
    {}

    virtual ~AstExpr()
    {}

    virtual std::string to_string(unsigned int indent = 0) = 0;
    //virtual llvm::Value *to_code() = 0;
};

#endif // ASTNODE_H
