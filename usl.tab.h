/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_USL_TAB_H_INCLUDED
# define YY_YY_USL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    STRING_LITERAL = 259,          /* STRING_LITERAL  */
    VARIABLE_REF = 260,            /* VARIABLE_REF  */
    URL_PATTERN = 261,             /* URL_PATTERN  */
    NUMBER = 262,                  /* NUMBER  */
    IF = 263,                      /* IF  */
    ELSE = 264,                    /* ELSE  */
    URL = 265,                     /* URL  */
    TITLE = 266,                   /* TITLE  */
    DESCRIPTION = 267,             /* DESCRIPTION  */
    TEMPLATE = 268,                /* TEMPLATE  */
    ACCESS = 269,                  /* ACCESS  */
    SEO = 270,                     /* SEO  */
    META_TAGS = 271,               /* META_TAGS  */
    NAVIGATION = 272,              /* NAVIGATION  */
    LINKS = 273,                   /* LINKS  */
    FOOTER = 274,                  /* FOOTER  */
    TEXT = 275,                    /* TEXT  */
    GENERATE_CONTENT = 276,        /* GENERATE_CONTENT  */
    REDIRECT = 277,                /* REDIRECT  */
    KEYWORDS = 278,                /* KEYWORDS  */
    FUNCTION = 279,                /* FUNCTION  */
    ASSIGN = 280,                  /* ASSIGN  */
    LBRACE = 281,                  /* LBRACE  */
    RBRACE = 282,                  /* RBRACE  */
    LPAREN = 283,                  /* LPAREN  */
    RPAREN = 284,                  /* RPAREN  */
    COMMA = 285,                   /* COMMA  */
    COLON = 286,                   /* COLON  */
    DOT = 287,                     /* DOT  */
    NEWLINE = 288,                 /* NEWLINE  */
    ERROR_TOKEN = 289,             /* ERROR_TOKEN  */
    LOWER_THAN_ELSE = 290          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 40 "usl.y"

    int int_val;
    char* string_val;
    struct ASTNode* ast_node;

#line 105 "usl.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_USL_TAB_H_INCLUDED  */
