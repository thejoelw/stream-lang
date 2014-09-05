/*
 * main.c file
 */

#include "astblock.h"
#include "stream.h"

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

int evaluate(AstBlock *e)
{
    return 0;
}

int main(void)
{
    char parse_test[] = "+my_stream = (1, 2), my_stream <= 3/* comment */, my_stream -> {in + 1} =>";
    char closure_test[] = "+class = {=> +local, [local /* stack_id: 1 */] =>}, +closure = class 123, closure[] =>";

    char *test = closure_test;

    AstBlock *tree = getAST(test);

    AstBlock *input = new AstBlock();
    input->apply_bind();

    Stream *output = new Stream();
    //output->on_flow();

    tree->call(0, input, output);

    int result = evaluate(tree);

    printf("Result of '%s' is %d\n", test, result);

    std::cout << tree->to_string() << std::endl;

    return 0;
}
