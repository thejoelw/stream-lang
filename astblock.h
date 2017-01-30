#ifndef ASTBLOCK_H
#define ASTBLOCK_H

#include <vector>

#include "astexpr.h"

class AstBlock : public AstExpr {
public:
    AstBlock();

    void add_expr(AstExpr *expr) {
        exprs.push_back(expr);
    }

private:
    std::vector<AstExpr *> exprs;
};

#endif // ASTBLOCK_H
