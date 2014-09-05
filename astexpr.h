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

#include "stream.h"
#include "context.h"

class AstExpr
{
protected:
    struct BindDesc
    {
        Stream *exp_in;
        Stream *exp_out;

        Stream *imp_in;
        Stream *imp_out;

        Stream *auto_out;

        unsigned int stack_start;
        AstBlock *ident_decl;
    };

public:
    AstExpr()
    {}

    virtual ~AstExpr()
    {}

    void init();

    virtual void hoist_ident_decl(AstBlock *scope) = 0;
    virtual void apply_bind(BindDesc bind_desc) = 0;

    virtual Stream *execute(Context *context) = 0;

    virtual std::string to_string(unsigned int indent = 0) = 0;
    //virtual llvm::Value *to_code() = 0;
};

#endif // ASTNODE_H
