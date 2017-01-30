%{

/*
 * Parser.y file
 * To generate the parser run: "bison Parser.y"
 */

#include "Parser.h"
#include "Lexer.h"
#include "astexpr.h"
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
    #include "astsame.h"
}

%union
{
    std::string *str;
    AstBlock *function;
    AstExpr *expr;
}

%token LMAP
%token RMAP
%token LREDUCE
%token RREDUCE
%token LAPPLY
%token RAPPLY
%token LASSIGN
%token RASSIGN
%token ASSIGN

%token LPAREN
%token RPAREN
%token LBRACKET
%token RBRACKET
%token LBRACE
%token RBRACE

%token DIRECTIVE

%token SAME

%token BREAK
%token <STR> NUMBER
%token <STR> PRIVATE_IDENT
%token <STR> PUBLIC_IDENT
%token <STR> UNBOUND_IDENT
%token <STR> IDENTIFIER

%token <STR> STRING

%type <function> main
%type <function> body
%type <expr> block
%type <expr> expr

%start main

%%

main
    : body { *tree = $$ = $1; }
    ;

body
    : %empty { $$ = new AstBlock(); }
    | expr { $$ = new AstBlock(); $$->add_expr($1); }
    | body BREAK expr { $$ = $1; $$->add_expr($3); }
    ;

block
    : LBRACE body RBRACE { $$ = $2; }
    | LBRACKET body RBRACKET { $$ = $2; $2->add_flags(AstBlock::implicit_out); }
    ;

expr
    : LPAREN body RPAREN { $$ = new AstParen($2); }
    | NUMBER { $$ = new AstNumber(*$1); }
    | PRIVATE_IDENT { $$ = new AstIdent($1->substr(1), AstIdent::Type::DeclPrivate); }
    | PUBLIC_IDENT { $$ = new AstIdent($1->substr(1), AstIdent::Type::DeclPublic); }
    | UNBOUND_IDENT { $$ = new AstIdent($1->substr(1), AstIdent::Type::Unbound); }
    | IDENTIFIER { $$ = new AstIdent(*$1, AstIdent::Type::Reference); }
    | STRING { /* $$ = new AstString(*$1); */ }
    | block { $$ = $1; }
    | expr expr { $$ = new AstCompose($1, $2); }

    | expr LMAP expr { $$ = new AstMap($1, $3); }
    | expr RMAP expr { $$ = new AstMap($3, $1); }
    | expr LREDUCE expr { $$ = new AstReduce($1, $3); }
    | expr RREDUCE expr { $$ = new AstReduce($3, $1); }
    | expr LAPPLY expr { $$ = new AstApply($1, $3); }
    | expr RAPPLY expr { $$ = new AstApply($3, $1); }
    | expr ASSIGN expr { $$ = new AstAssign($1, $3); }
    | expr LASSIGN expr { $$ = new AstAssign($1, $3); }
    | expr RASSIGN expr { $$ = new AstAssign($3, $1); }
    | expr SAME expr { $$ = new AstSame($1, $3); }

    | LMAP expr { $$ = new AstMap(new AstIdent(AstIdent::ImplicitOut), $2); }
    | RMAP expr { $$ = new AstMap($2, new AstIdent(AstIdent::ImplicitIn)); }
    | LREDUCE expr { $$ = new AstReduce(new AstIdent(AstIdent::ImplicitOut), $2); }
    | RREDUCE expr { $$ = new AstReduce($2, new AstIdent(AstIdent::ImplicitIn)); }
    | LAPPLY expr { $$ = new AstApply(new AstIdent(AstIdent::ImplicitOut), $2); }
    | RAPPLY expr { $$ = new AstApply($2, new AstIdent(AstIdent::ImplicitIn)); }
    | ASSIGN expr { $$ = new AstAssign(new AstIdent(AstIdent::ImplicitOut), $2); }
    | LASSIGN expr { $$ = new AstAssign(new AstIdent(AstIdent::ImplicitOut), $2); }
    | RASSIGN expr { $$ = new AstAssign($2, new AstIdent(AstIdent::ImplicitIn)); }

    | expr LMAP { $$ = new AstMap($1, new AstIdent(AstIdent::ImplicitIn)); }
    | expr RMAP { $$ = new AstMap(new AstIdent(AstIdent::ImplicitOut), $1); }
    | expr LREDUCE { $$ = new AstReduce($1, new AstIdent(AstIdent::ImplicitIn)); }
    | expr RREDUCE { $$ = new AstReduce(new AstIdent(AstIdent::ImplicitOut), $1); }
    | expr LAPPLY { $$ = new AstApply($1, new AstIdent(AstIdent::ImplicitIn)); }
    | expr RAPPLY { $$ = new AstApply(new AstIdent(AstIdent::ImplicitOut), $1); }
    | expr ASSIGN { $$ = new AstAssign($1, new AstIdent(AstIdent::ImplicitIn)); }
    | expr LASSIGN { $$ = new AstAssign($1, new AstIdent(AstIdent::ImplicitIn)); }
    | expr RASSIGN { $$ = new AstAssign(new AstIdent(AstIdent::ImplicitOut), $1); }
    ;

%%
