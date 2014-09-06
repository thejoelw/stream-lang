/*
 * main.c file
 */

#include "astblock.h"
#include "stream.h"
#include "context.h"

#include "Parser.h"
#include "Lexer.h"

#include <stdio.h>

int yyparse(AstBlock **tree, yyscan_t scanner);

AstBlock *getAST(const char *expr)
{
    AstBlock *tree;
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

int main(void)
{
    char parse_test[] = "+my_stream = (1, 2), my_stream <= 3/* comment */, my_stream -> {in + 1} =>";
    char closure_test[] = "+class = {=> +local, [local /* stack_id: 1 */] =>}, +closure = class 123, closure[] =>";

    char *test = closure_test;

    AstBlock *tree = getAST(test);
    tree->init();

    std::cout << tree->to_string() << std::endl;

    AstBlock *input = new AstBlock();
    input->init();

    Stream *output = tree->execute(new Context());

    return 0;
}
