/*
 * main.c file
 */

#include "astnode.h"

#include "Parser.h"
#include "Lexer.h"
#include "astnode.h"

#include <stdio.h>

int yyparse(AstNode **expression, yyscan_t scanner);

AstNode *getAST(const char *expr)
{
    AstNode *expression;
    yyscan_t scanner;
    YY_BUFFER_STATE state;

    if (yylex_init(&scanner)) {
        // couldn't initialize
        return NULL;
    }

    state = yy_scan_string(expr, scanner);

    if (yyparse(&expression, scanner)) {
        // error parsing
        return NULL;
    }

    yy_delete_buffer(state, scanner);

    yylex_destroy(scanner);

    return expression;
}

int evaluate(AstNode *e)
{
    /*
    switch (e->type) {
        case eVALUE:
            return e->value;
        case eMULTIPLY:
            return evaluate(e->left) * evaluate(e->right);
        case ePLUS:
            return evaluate(e->left) + evaluate(e->right);
        default:
            // shouldn't be here
            return 0;
    }
    */
}

int main(void)
{
    char test[] = "+my_stream = (1, 2), my_stream <= 3, my_stream -> {in + 1}";

    AstNode *e = NULL;
    int result = 0;

    e = getAST(test);

    result = evaluate(e);

    printf("Result of '%s' is %d\n", test, result);

    return 0;
}
