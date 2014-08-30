%{

/*
 * Parser.y file
 * To generate the parser run: "bison Parser.y"
 */

#include "Parser.h"
#include "Lexer.h"
#include "astexpr.h"

#include <iostream>

int yyerror(AstExpr **expression, yyscan_t scanner, const char *msg) {
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
%parse-param { AstExpr **expression }
%parse-param { yyscan_t scanner }

%code requires
{
    #include <string>
    #include "astexpr.h"
    #include "astident.h"
    #include "astnumber.h"
    #include "astblock.h"
    #include "astapply.h"
    #include "astflow.h"
}

%union
{
    std::string *string;
    AstBlock *body;
    AstBlock *block;
    AstExpr *expr;
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

%type <body> body
%type <block> block
%type <expr> expr

%%

body
    : %empty { $$ = new AstBlock(); }
    | expr { $$ = new AstBlock(); $$->add_expr($1); }
    | body BREAK expr { $$ = $1; $$->add_expr($3); }
    ;

block
    : LBRACE body RBRACE { $$ = $2; $2->set_type(AstBlock::TYPE_MAJOR); }
    | LBRACKET body RBRACKET { $$ = $2; $2->set_type(AstBlock::TYPE_MINOR); }
    | LPAREN body RPAREN { $$ = $2 /* (...) :=: -> [...] => */; $2->set_type(AstBlock::TYPE_MINOR); }
    ;

expr
    : DECL_IDENT { $$ = new AstIdent($1->substr(1), true); }
    | IDENTIFIER { $$ = new AstIdent(*$1, false); }
    | NUMBER { $$ = new AstNumber(*$1); }
    | block { $$ = $1; }
    | expr expr { $$ = new AstApply($1, $2); }
    | expr LAPPLY expr { $$ = new AstApply($1, $3); }
    | expr RAPPLY expr { $$ = new AstApply($3, $1); }
    | expr FLOW expr { $$ = new AstFlow($1, $3); }
    | expr LFLOW expr { $$ = new AstFlow($1, $3); }
    | expr RFLOW expr { $$ = new AstFlow($3, $1); }
    | expr PIPE expr { /* $$ = new AstPipe($3, $1); */ }
    | expr LPIPE expr { /* $$ = new AstPipe($1, $3); */ }
    | expr RPIPE expr { /* $$ = new AstPipe($3, $1); */ }
    | expr STREAM_LEN { /* $$ = new AstLength($1); */ }
    | expr STREAM_FIRST { /* $$ = new AstFirst($1); */ }
    | expr STREAM_LAST { /* $$ = new AstLast($1); */ }
    ;

%%
