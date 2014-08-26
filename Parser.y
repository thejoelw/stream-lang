%{

/*
 * Parser.y file
 * To generate the parser run: "bison Parser.y"
 */

#include "Parser.h"
#include "Lexer.h"
#include "astnode.h"

#include <iostream>

int yyerror(AstNode **expression, yyscan_t scanner, const char *msg) {
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
%parse-param { AstNode **expression }
%parse-param { yyscan_t scanner }

%code requires
{
    #include <string>
    #include "astnode.h"
}

%define api.value.type union

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

%token <std::string> NUMBER
%token <std::string> DECL_IDENT
%token <std::string> IDENTIFIER

%type <AstFunction*> body
%type <AstFunction*> block
%type <AstStream*> stream

%%

body
    : %empty { $$ = new AstFunction(); }
    | stream { $$ = new AstFunction(); $$->add_stream($1); }
    | body BREAK stream { $$ = $1; $$->add_stream($3); }
    ;

block
    : LBRACE body RBRACE { $$ = $2; $2->set_type(FUNCTION_MAJOR); }
    | LBRACKET body RBRACKET { $$ = $2; $2->set_type(FUNCTION_MINOR); }
    | LPAREN body RPAREN { $$ = $2 /* (...) :=: -> [...] => */; $2->set_type(FUNCTION_MINOR); }
    ;

stream
    : DECL_IDENT { $$ = new AstStreamIdent(*$1, true); }
    | IDENTIFIER { $$ = new AstStreamIdent(*$1, false); }
    | NUMBER { $$ = new AstStreamNumber(*$1); }
    | block { $$ = new AstStreamBlock($1); }
    | stream stream { $$ = $2->apply_to($1); }
    | stream LAPPLY stream { $$ = $3->apply_to($1); }
    | stream RAPPLY stream { $$ = $1->apply_to($3); }
    | stream FLOW stream { $$ = $3->flow_to($1); }
    | stream LFLOW stream { $$ = $3->flow_to($1); }
    | stream RFLOW stream { $$ = $1->flow_to($3); }
    | stream PIPE stream { $$ = $1->pipe_to($3); }
    | stream LPIPE stream { $$ = $3->pipe_to($1); }
    | stream RPIPE stream { $$ = $1->pipe_to($3); }
    | stream STREAM_LEN { $$ = new AstStreamLength($1); }
    | stream STREAM_FIRST { $$ = new AstStreamFirst($1); }
    | stream STREAM_LAST { $$ = new AstStreamLast($1); }
    ;

%%
