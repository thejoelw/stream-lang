%{

/*
 * Parser.y file
 * To generate the parser run: "bison Parser.y"
 */

#include "Expression.h"
#include "Parser.h"
#include "Lexer.h"

#include <iostream>

int yyerror(SExpression **expression, yyscan_t scanner, const char *msg) {
    // Add error handling routine as needed
}

%}

%code requires {

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

}

%output  "Parser.c"
%defines "Parser.h"

%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { SExpression **expression }
%parse-param { yyscan_t scanner }

%code requires
{
    #include <string>
}

%union {
    int value;
    SExpression *expression;
    std::string *string;
}

%token LAPPLY
%token RAPPLY
%token FLOW
%token LFLOW
%token RFLOW
%token PIPE
%token LPIPE
%token RPIPE

%token LPAREN
%token RPAREN
%token LBRACKET
%token RBRACKET
%token LBRACE
%token RBRACE

%token STREAM_LEN
%token STREAM_FIRST
%token STREAM_LAST

%token BREAK

%token <string> NUMBER
%token <string> DECL_IDENT
%token <string> IDENTIFIER

/* %type <expression> expr */

%%

body
    : %empty
    | stream
    | body BREAK stream { std::cout << "break" << std::endl; }
    ;

block
    : LBRACE body RBRACE { std::cout << "brace_func" << std::endl; }
    | LBRACKET body RBRACKET { std::cout << "bracket_func" << std::endl; }
    | LPAREN body RPAREN { std::cout << "paren_func" << std::endl; }
    ;

stream
    : DECL_IDENT { std::cout << "Declared an identifier: " << *$1 << std::endl; }
    | IDENTIFIER { std::cout << "Using an identifier as a stream: " << *$1 << std::endl; }
    | NUMBER { std::cout << "Using a number as a stream: " << *$1 << std::endl; }
    | block { std::cout << "Using a block as a stream" << std::endl; }
    | stream stream { std::cout << "Action ''" << std::endl; }
    | stream LAPPLY stream { std::cout << "Action '<-'" << std::endl; }
    | stream RAPPLY stream { std::cout << "Action '->'" << std::endl; }
    | stream FLOW stream { std::cout << "Action '='" << std::endl; }
    | stream LFLOW stream { std::cout << "Action '<='" << std::endl; }
    | stream RFLOW stream { std::cout << "Action '=>'" << std::endl; }
    | stream PIPE stream { std::cout << "Action '|'" << std::endl; }
    | stream LPIPE stream { std::cout << "Action '<|'" << std::endl; }
    | stream RPIPE stream { std::cout << "Action '|>'" << std::endl; }
    | stream STREAM_LEN {}
    | stream STREAM_FIRST {}
    | stream STREAM_LAST {}
    ;

%%
