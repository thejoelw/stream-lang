%{

/*
 * Lexer.l file
 * To generate the lexical analyzer run: "flex Lexer.l"
 */

#include "Parser.h"
#include "astexpr.h"

#include <stdio.h>
#include <iostream>
#include <string>

#define SAVE_TOKEN (yylval->str = new std::string(yytext, yyleng));
#define TOKEN(t) (yylval.token = t)

#pragma clang diagnostic push
// Ignore about 20 "register storage class specifier is deprecated" warnings from flex code
#pragma clang diagnostic ignored "-Wdeprecated-register"

%}

%option outfile="Lexer.cpp" header-file="Lexer.h"
%option warn nodefault

%option reentrant noyywrap never-interactive nounistd
%option bison-bridge



IDNT_START  [a-zA-Z_]
IDNT_CONT   [a-zA-Z_0-9]
IDNT_SYMBOL [~!@%&*+\-|;<>?/]
IDNT        {IDNT_START}{IDNT_CONT}+|{IDNT_SYMBOL}+

%x comment
%x str_single_quote
%x str_double_quote
%x str_dot

%%

    std::string *string_buf;

"/*"            BEGIN(comment);
<comment>{
    [^*]*       /* eat anything that's not a '*' */
    "*"+[^*/]*  /* eat up '*'s not followed by '/'s */
    "*"+"/"     BEGIN(INITIAL);
}

"<-"        { printf("return LAPPLY;\n"); return LAPPLY; }
"->"        { printf("return RAPPLY;\n"); return RAPPLY; }
"="         { printf("return FLOW;\n"); return FLOW; }
"<="        { printf("return LFLOW;\n"); return LFLOW; }
"=>"        { printf("return RFLOW;\n"); return RFLOW; }

"("         { printf("return LPAREN;\n"); return LPAREN; }
")"         { printf("return RPAREN;\n"); return RPAREN; }
"["         { printf("return LBRACKET;\n"); return LBRACKET; }
"]"         { printf("return RBRACKET;\n"); return RBRACKET; }
"{"         { printf("return LBRACE;\n"); return LBRACE; }
"}"         { printf("return RBRACE;\n"); return RBRACE; }

"#"         { printf("return STREAM_LEN;\n"); return STREAM_LEN; }
"^"         { printf("return STREAM_FIRST;\n"); return STREAM_FIRST; }
"$"         { printf("return STREAM_LAST;\n"); return STREAM_LAST; }

"=="        { printf("return SAME;\n"); return SAME; }

[\r\n,]     { printf("return BREAK;\n"); return BREAK; }
[ \t]*      { printf("Skipping blanks: '%s'\n", yytext); }
[0-9]+      { printf("return NUMBER; // %s\n", yytext); SAVE_TOKEN; return NUMBER; }
"+"{IDNT}   { printf("return DECL_IDENT; // %s\n", yytext); SAVE_TOKEN; return DECL_IDENT; }
{IDNT}      { printf("return IDENTIFIER; // %s\n", yytext); SAVE_TOKEN; return IDENTIFIER; }

\'          { string_buf = new std::string(); BEGIN(str_single_quote); }
\"          { string_buf = new std::string(); BEGIN(str_double_quote); }
\.          { string_buf = new std::string(); BEGIN(str_dot); }

<str_single_quote,str_double_quote,str_dot>{
    \\[0-7]{1,3} {
        /* octal escape sequence */
        unsigned int result;

        sscanf( yytext + 1, "%o", &result );

        if ( result > 0xff )
        {
            /* error, constant is out-of-bounds */
        }

        string_buf->append(1, result);
    }

    \\[0-9]+    {
        /* generate error - bad escape sequence; something
         * like '\48' or '\0777777'
         */
    }

    \\n        { string_buf->append(1, '\n'); }
    \\t        { string_buf->append(1, '\t'); }
    \\r        { string_buf->append(1, '\r'); }
    \\b        { string_buf->append(1, '\b'); }
    \\f        { string_buf->append(1, '\f'); }

    \\(.|\n)   { string_buf->append(1, yytext[1]); }
}

<str_single_quote>[^\\\']+  { string_buf->append(yytext); }
<str_double_quote>[^\\\"]+  { string_buf->append(yytext); }
<str_dot>[a-zA-Z_0-9]+      { string_buf->append(yytext); }

<str_single_quote>\'        { yylval->str = string_buf; BEGIN(INITIAL); return STRING; }
<str_double_quote>\"        { yylval->str = string_buf; BEGIN(INITIAL); return STRING; }
<str_dot>[^\\a-zA-Z_0-9]    { yylval->str = string_buf; BEGIN(INITIAL); return STRING; }

.           { printf("Did not recognize: '%s'\n", yytext); }

%%

#pragma clang diagnostic pop

int yyerror(const char *msg) {
    fprintf(stderr,"Error:%s\n",msg); return 0;
}
