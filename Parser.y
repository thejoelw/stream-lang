%{

/*
 * Parser.y file
 * To generate the parser run: "bison Parser.y"
 */

#include "Parser.h"
#include "Lexer.h"
#include "astblock.h"

#include <iostream>

int yyerror(AstBlock **expression, yyscan_t scanner, const char *msg) {
    // Add error handling routine as needed
}

%}

%code requires {

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

}

%output  "Parser.cpp"
%defines "Parser.h"

%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { AstBlock **tree }
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
    AstBlock *function;
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

%type <function> main
%type <function> body
%type <expr> block
%type <expr> expr

%start main

%%

main
    : body { *tree = $$ = $1; $1->bind(AstBlock::BindInOut | AstBlock::BindImplicitRel | AstBlock::BindIdentDecl); }
    ;

body
    : %empty { $$ = new AstBlock(); }
    | expr { $$ = new AstBlock(); $$->add_expr($1); }
    | body BREAK expr { $$ = $1; $$->add_expr($3); }
    ;

block
    : LBRACE body RBRACE { $$ = $2; $2->bind(AstBlock::BindInOut | AstBlock::BindImplicitRel | AstBlock::BindIdentDecl); }
    | LBRACKET body RBRACKET { $$ = $2; $2->bind(AstBlock::BindImplicitRel | AstBlock::BindAutoOut); }
    | LPAREN body RPAREN { $$ = new AstApply($2, AstIdent::ImplicitIn); $2->bind(AstBlock::BindAutoOut); }
    ;

expr
    : DECL_IDENT { $$ = new AstIdent($1->substr(1), true); }
    | IDENTIFIER { $$ = new AstIdent(*$1); }
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

    | LAPPLY expr { $$ = new AstApply(AstIdent::ImplicitOut, $2); }
    | RAPPLY expr { $$ = new AstApply($2, AstIdent::ImplicitIn); }
    | FLOW expr { $$ = new AstFlow(AstIdent::ImplicitOut, $2); }
    | LFLOW expr { $$ = new AstFlow(AstIdent::ImplicitOut, $2); }
    | RFLOW expr { $$ = new AstFlow($2, AstIdent::ImplicitIn); }
    | PIPE expr { /* $$ = new AstPipe($2, AstIdent::ImplicitIn); */ }
    | LPIPE expr { /* $$ = new AstPipe(AstIdent::ImplicitOut, $2); */ }
    | RPIPE expr { /* $$ = new AstPipe($2, AstIdent::ImplicitIn); */ }
    | STREAM_LEN { /* $$ = new AstLength(AstIdent::ImplicitIn); */ }
    | STREAM_FIRST { /* $$ = new AstFirst(AstIdent::ImplicitIn); */ }
    | STREAM_LAST { /* $$ = new AstLast(AstIdent::ImplicitIn); */ }

    | expr LAPPLY { $$ = new AstApply($1, AstIdent::ImplicitIn); }
    | expr RAPPLY { $$ = new AstApply(AstIdent::ImplicitOut, $1); }
    | expr FLOW { $$ = new AstFlow($1, AstIdent::ImplicitIn); }
    | expr LFLOW { $$ = new AstFlow($1, AstIdent::ImplicitIn); }
    | expr RFLOW { $$ = new AstFlow(AstIdent::ImplicitOut, $1); }
    | expr PIPE { /* $$ = new AstPipe(AstIdent::ImplicitOut, $1); */ }
    | expr LPIPE { /* $$ = new AstPipe($1, AstIdent::ImplicitIn); */ }
    | expr RPIPE { /* $$ = new AstPipe(AstIdent::ImplicitOut, $1); */ }

    | LAPPLY { $$ = new AstApply(AstIdent::ImplicitOut, AstIdent::ImplicitIn); }
    | RAPPLY { $$ = new AstApply(AstIdent::ImplicitOut, AstIdent::ImplicitOut); }
    | FLOW { $$ = new AstFlow(AstIdent::ImplicitOut, AstIdent::ImplicitIn); }
    | LFLOW { $$ = new AstFlow(AstIdent::ImplicitOut, AstIdent::ImplicitIn); }
    | RFLOW { $$ = new AstFlow(AstIdent::ImplicitOut, AstIdent::ImplicitOut); }
    | PIPE { /* $$ = new AstPipe(AstIdent::ImplicitOut, AstIdent::ImplicitOut); */ }
    | LPIPE { /* $$ = new AstPipe(AstIdent::ImplicitOut, AstIdent::ImplicitIn); */ }
    | RPIPE { /* $$ = new AstPipe(AstIdent::ImplicitOut, AstIdent::ImplicitOut); */ }
    ;

%%
