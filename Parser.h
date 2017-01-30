/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 20 "Parser.y" /* yacc.c:1909  */


#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

#line 38 "Parser.y" /* yacc.c:1909  */

    #include <string>
    #include "astexpr.h"
    #include "astident.h"
    #include "astnumber.h"
    #include "astblock.h"
    #include "astapply.h"
    #include "astflow.h"
    #include "astsame.h"

#line 63 "Parser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    LMAP = 258,
    RMAP = 259,
    LREDUCE = 260,
    RREDUCE = 261,
    LAPPLY = 262,
    RAPPLY = 263,
    LASSIGN = 264,
    RASSIGN = 265,
    ASSIGN = 266,
    LPAREN = 267,
    RPAREN = 268,
    LBRACKET = 269,
    RBRACKET = 270,
    LBRACE = 271,
    RBRACE = 272,
    DIRECTIVE = 273,
    SAME = 274,
    BREAK = 275,
    NUMBER = 276,
    PRIVATE_IDENT = 277,
    PUBLIC_IDENT = 278,
    UNBOUND_IDENT = 279,
    IDENTIFIER = 280,
    STRING = 281
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 50 "Parser.y" /* yacc.c:1909  */

    std::string *str;
    AstBlock *function;
    AstExpr *expr;

#line 108 "Parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (AstBlock **tree, yyscan_t scanner);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
