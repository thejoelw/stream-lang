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

#define SAVE_TOKEN yylval->string = new std::string(yytext, yyleng);
#define TOKEN(t) (yylval.token = t)

%}

%option outfile="Lexer.cpp" header-file="Lexer.h"
%option warn nodefault

%option reentrant noyywrap never-interactive nounistd
%option bison-bridge



IDNT_START  [a-zA-Z_]
IDNT_CONT   [a-zA-Z_0-9]
/* IDNT_SYMBOL [~!@$%^&*_+\-=|;<>?/] */
IDNT_SYMBOL [~!@$%^&*_+\-=|;<>?/]
IDNT        {IDNT_START}{IDNT_CONT}+|{IDNT_SYMBOL}+

%x comment
%x string

%%

"/*"            BEGIN(comment);
<comment>{
    [^*]*       /* eat anything that's not a '*' */
    "*"+[^*/]*  /* eat up '*'s not followed by '/'s */
    "*"+"/"     BEGIN(0);
}

"<-"        { printf("return LAPPLY;\n"); return LAPPLY; }
"->"        { printf("return RAPPLY;\n"); return RAPPLY; }
"="         { printf("return FLOW;\n"); return FLOW; }
"<="        { printf("return LFLOW;\n"); return LFLOW; }
"=>"        { printf("return RFLOW;\n"); return RFLOW; }
"|"         { printf("return PIPE;\n"); return PIPE; }
"<|"        { printf("return LPIPE;\n"); return LPIPE; }
"|>"        { printf("return RPIPE;\n"); return RPIPE; }

"("         { printf("return LPAREN;\n"); return LPAREN; }
")"         { printf("return RPAREN;\n"); return RPAREN; }
"["         { printf("return LBRACKET;\n"); return LBRACKET; }
"]"         { printf("return RBRACKET;\n"); return RBRACKET; }
"{"         { printf("return LBRACE;\n"); return LBRACE; }
"}"         { printf("return RBRACE;\n"); return RBRACE; }

"#"         { printf("return STREAM_LEN;\n"); return STREAM_LEN; }
"^"         { printf("return STREAM_FIRST;\n"); return STREAM_FIRST; }
"$"         { printf("return STREAM_LAST;\n"); return STREAM_LAST; }

[\r\n,]     { printf("return BREAK;\n"); return BREAK; }
[ \t]*      { printf("Skipping blanks: '%s'\n", yytext); }
[0-9]+      { printf("return NUMBER; // %s\n", yytext); SAVE_TOKEN; return NUMBER; }
"+"{IDNT}   { printf("return DECL_IDENT; // %s\n", yytext); SAVE_TOKEN; return DECL_IDENT; }
{IDNT}      { printf("return IDENTIFIER; // %s\n", yytext); SAVE_TOKEN; return IDENTIFIER; }

        char string_buf[MAX_STR_CONST];
        char *string_buf_ptr;

\"      string_buf_ptr = string_buf; BEGIN(string);

<string>\"        { /* saw closing quote - all done */
        BEGIN(INITIAL);
        *string_buf_ptr = '\0';
        /* return string constant token type and
         * value to parser
         */
        }

<string>\n        {
        /* error - unterminated string constant */
        /* generate error message */
        }

<string>\\[0-7]{1,3} {
        /* octal escape sequence */
        int result;

        (void) sscanf( yytext + 1, "%o", &result );

        if ( result > 0xff )
                /* error, constant is out-of-bounds */

        *string_buf_ptr++ = result;
        }

<string>\\[0-9]+ {
        /* generate error - bad escape sequence; something
         * like '\48' or '\0777777'
         */
        }

<string>\\n  *string_buf_ptr++ = '\n';
<string>\\t  *string_buf_ptr++ = '\t';
<string>\\r  *string_buf_ptr++ = '\r';
<string>\\b  *string_buf_ptr++ = '\b';
<string>\\f  *string_buf_ptr++ = '\f';

<string>\\(.|\n)  *string_buf_ptr++ = yytext[1];

<string>[^\\\n\"]+        {
        char *yptr = yytext;

        while ( *yptr )
                *string_buf_ptr++ = *yptr++;
        }


.           { printf("Did not recognize: '%s'\n", yytext); }

%%

int yyerror(const char *msg) {
    fprintf(stderr,"Error:%s\n",msg); return 0;
}
