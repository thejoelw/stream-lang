/*
 * main.c file
 */

#include "astexpr.h"

#include "Parser.h"
#include "Lexer.h"
#include "astexpr.h"

#include <stdio.h>

int yyparse(AstFunction **tree, yyscan_t scanner);

AstFunction *getAST(const char *expr)
{
    AstFunction *tree;
    yyscan_t scanner;
    YY_BUFFER_STATE state;

    if (yylex_init(&scanner)) {
        // couldn't initialize
        return NULL;
    }

    state = yy_scan_string(expr, scanner);

    if (yyparse(&tree, scanner)) {
        // error parsing
        return NULL;
    }

    yy_delete_buffer(state, scanner);

    yylex_destroy(scanner);

    return tree;
}

int evaluate(AstFunction *e)
{
    return 0;
}

int main(void)
{
    char test[] = "+my_stream = (1, 2), my_stream <= 3/* comment */, my_stream -> {in + 1} =>";

    AstFunction *tree = getAST(test);

    int result = evaluate(tree);

    printf("Result of '%s' is %d\n", test, result);

    std::cout << tree->to_string() << std::endl;

    return 0;
}
