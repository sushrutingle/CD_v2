/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "usl.y"

/*
 * URL-based Specification Language (USL) Parser
 * YACC Specification File for USL Compiler
 * 
 * This file defines the syntax and grammar rules for USL
 * and builds an Abstract Syntax Tree (AST) for semantic analysis
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symbol_table.h"

/* External functions from lexer */
extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;
extern void print_lexical_error_table();
extern void print_token_table();
extern void reset_lexer();

/* Global variables */
ASTNode* ast_root = NULL;
SymbolTable* global_symbol_table = NULL;
int parse_error_count = 0;
int last_error_line = -1;  // Track the line number of the last error to avoid duplicates

/* Function prototypes */
void yyerror(const char* s);
void print_parse_tree(ASTNode* node, int depth);
void print_parse_tree_helper(ASTNode* node, int depth, int is_last[], int parent_depth);
int semantic_analysis(ASTNode* root);


#line 109 "usl.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "usl.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_STRING_LITERAL = 4,             /* STRING_LITERAL  */
  YYSYMBOL_VARIABLE_REF = 5,               /* VARIABLE_REF  */
  YYSYMBOL_URL_PATTERN = 6,                /* URL_PATTERN  */
  YYSYMBOL_NUMBER = 7,                     /* NUMBER  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_URL = 10,                       /* URL  */
  YYSYMBOL_TITLE = 11,                     /* TITLE  */
  YYSYMBOL_DESCRIPTION = 12,               /* DESCRIPTION  */
  YYSYMBOL_TEMPLATE = 13,                  /* TEMPLATE  */
  YYSYMBOL_ACCESS = 14,                    /* ACCESS  */
  YYSYMBOL_SEO = 15,                       /* SEO  */
  YYSYMBOL_META_TAGS = 16,                 /* META_TAGS  */
  YYSYMBOL_NAVIGATION = 17,                /* NAVIGATION  */
  YYSYMBOL_LINKS = 18,                     /* LINKS  */
  YYSYMBOL_FOOTER = 19,                    /* FOOTER  */
  YYSYMBOL_TEXT = 20,                      /* TEXT  */
  YYSYMBOL_GENERATE_CONTENT = 21,          /* GENERATE_CONTENT  */
  YYSYMBOL_REDIRECT = 22,                  /* REDIRECT  */
  YYSYMBOL_KEYWORDS = 23,                  /* KEYWORDS  */
  YYSYMBOL_FUNCTION = 24,                  /* FUNCTION  */
  YYSYMBOL_ASSIGN = 25,                    /* ASSIGN  */
  YYSYMBOL_LBRACE = 26,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 27,                    /* RBRACE  */
  YYSYMBOL_LPAREN = 28,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 29,                    /* RPAREN  */
  YYSYMBOL_COMMA = 30,                     /* COMMA  */
  YYSYMBOL_COLON = 31,                     /* COLON  */
  YYSYMBOL_DOT = 32,                       /* DOT  */
  YYSYMBOL_NEWLINE = 33,                   /* NEWLINE  */
  YYSYMBOL_ERROR_TOKEN = 34,               /* ERROR_TOKEN  */
  YYSYMBOL_LOWER_THAN_ELSE = 35,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 36,                  /* $accept  */
  YYSYMBOL_program = 37,                   /* program  */
  YYSYMBOL_statement_list = 38,            /* statement_list  */
  YYSYMBOL_statement = 39,                 /* statement  */
  YYSYMBOL_variable_declaration = 40,      /* variable_declaration  */
  YYSYMBOL_page_definition = 41,           /* page_definition  */
  YYSYMBOL_page_body = 42,                 /* page_body  */
  YYSYMBOL_page_property_list = 43,        /* page_property_list  */
  YYSYMBOL_page_property = 44,             /* page_property  */
  YYSYMBOL_seo_block = 45,                 /* seo_block  */
  YYSYMBOL_meta_tags_block = 46,           /* meta_tags_block  */
  YYSYMBOL_meta_tag_list = 47,             /* meta_tag_list  */
  YYSYMBOL_meta_tag = 48,                  /* meta_tag  */
  YYSYMBOL_generate_content_block = 49,    /* generate_content_block  */
  YYSYMBOL_generate_statement_list = 50,   /* generate_statement_list  */
  YYSYMBOL_generate_statement = 51,        /* generate_statement  */
  YYSYMBOL_conditional_statement = 52,     /* conditional_statement  */
  YYSYMBOL_statement_block = 53,           /* statement_block  */
  YYSYMBOL_function_call = 54,             /* function_call  */
  YYSYMBOL_argument_list = 55,             /* argument_list  */
  YYSYMBOL_navigation_block = 56,          /* navigation_block  */
  YYSYMBOL_link_list = 57,                 /* link_list  */
  YYSYMBOL_link = 58,                      /* link  */
  YYSYMBOL_footer_block = 59,              /* footer_block  */
  YYSYMBOL_expression = 60,                /* expression  */
  YYSYMBOL_string_expression = 61,         /* string_expression  */
  YYSYMBOL_identifier = 62                 /* identifier  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   126

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  106

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    79,    79,    85,    92,    95,   110,   113,   116,   119,
     125,   137,   149,   152,   158,   161,   176,   180,   184,   188,
     192,   196,   200,   203,   209,   216,   223,   226,   241,   245,
     252,   259,   262,   277,   280,   283,   286,   292,   297,   306,
     313,   317,   323,   326,   341,   348,   351,   366,   373,   380,
     383,   386,   389,   395,   398,   404
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "STRING_LITERAL", "VARIABLE_REF", "URL_PATTERN", "NUMBER", "IF", "ELSE",
  "URL", "TITLE", "DESCRIPTION", "TEMPLATE", "ACCESS", "SEO", "META_TAGS",
  "NAVIGATION", "LINKS", "FOOTER", "TEXT", "GENERATE_CONTENT", "REDIRECT",
  "KEYWORDS", "FUNCTION", "ASSIGN", "LBRACE", "RBRACE", "LPAREN", "RPAREN",
  "COMMA", "COLON", "DOT", "NEWLINE", "ERROR_TOKEN", "LOWER_THAN_ELSE",
  "$accept", "program", "statement_list", "statement",
  "variable_declaration", "page_definition", "page_body",
  "page_property_list", "page_property", "seo_block", "meta_tags_block",
  "meta_tag_list", "meta_tag", "generate_content_block",
  "generate_statement_list", "generate_statement", "conditional_statement",
  "statement_block", "function_call", "argument_list", "navigation_block",
  "link_list", "link", "footer_block", "expression", "string_expression",
  "identifier", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-69)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      11,   -69,     1,     7,    37,    11,   -69,   -69,   -69,   -69,
     -69,    22,    24,    30,   -69,   -69,    14,    95,    26,    35,
     -69,   -69,   -69,   -69,   -69,   -69,    27,    42,    43,    44,
      46,    50,    54,    61,    52,    49,    95,   -69,   -69,   -69,
      85,    14,     5,    19,    14,    14,    86,    87,    73,    71,
      91,   -69,   -69,     9,   -69,    72,    69,   -69,    15,   -69,
     -69,   -69,   -69,   -69,   -69,    74,    75,    14,   -69,   -69,
      51,   -69,   -69,   -69,    13,   -69,    76,   -69,    94,   -69,
     -69,    14,     3,   -69,    70,   -69,   -69,   -69,   -69,   -69,
      88,    89,    12,   -69,    71,    14,    14,   -69,   -69,    71,
     102,   -69,   -69,    81,    71,   -69
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    55,     0,     0,     0,     2,     4,     6,     7,     8,
       9,     0,     0,     0,     1,     5,     0,    13,     0,     0,
      53,    50,    54,    51,    10,    49,    52,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    12,    14,    22,    23,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    11,    15,     0,    45,     0,     0,    41,     0,    42,
      16,    17,    18,    19,    20,     0,     0,     0,    33,    36,
       0,    31,    35,    34,     0,    21,     0,    46,     0,    48,
      40,     0,     0,    24,     0,    30,    32,    44,    47,    43,
       0,     0,     0,    26,     0,     0,     0,    25,    27,    39,
      37,    28,    29,     0,     0,    38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -69,   -69,   -69,   110,    16,   -69,   -69,   -69,    -4,   -69,
     -69,   -69,    28,   -69,    77,   -68,   -69,    17,   -48,   -69,
     -69,   -69,    65,   -69,   -38,    79,     0
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    68,     8,    35,    36,    69,    38,
      66,    92,    93,    39,    99,    71,    72,   100,    23,    58,
       9,    53,    54,    10,    24,    25,    26
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      11,    73,    86,    56,    59,    11,    61,    62,     1,    20,
      21,    22,     1,    37,     1,    90,     7,     1,    20,    21,
      22,     7,    73,    20,    90,    22,    91,    12,     2,    84,
       3,    86,    52,    13,    57,    91,    76,    14,    16,    97,
      55,    42,    18,    89,    80,    81,    73,    16,    17,    74,
      19,    73,    40,    55,     1,    42,    73,   101,   102,    67,
      41,    27,    28,    29,    30,    31,    32,    43,    44,    45,
      74,    46,    33,    34,     1,    47,    51,    50,    85,    67,
      48,    27,    28,    29,    30,    31,    32,    49,     1,    65,
      63,    64,    33,    34,    74,    75,    79,    78,    88,    74,
      82,    94,    83,    87,    74,    27,    28,    29,    30,    31,
      32,   103,   104,    95,    96,    15,    33,    34,    77,     0,
      98,   105,    60,     0,     0,     0,    70
};

static const yytype_int8 yycheck[] =
{
       0,    49,    70,    41,    42,     5,    44,    45,     3,     4,
       5,     6,     3,    17,     3,    12,     0,     3,     4,     5,
       6,     5,    70,     4,    12,     6,    23,    26,    17,    67,
      19,    99,    36,    26,    29,    23,    27,     0,    25,    27,
      40,    28,    18,    81,    29,    30,    94,    25,    26,    49,
      20,    99,    26,    53,     3,    28,   104,    95,    96,     8,
      25,    10,    11,    12,    13,    14,    15,    25,    25,    25,
      70,    25,    21,    22,     3,    25,    27,    25,    27,     8,
      26,    10,    11,    12,    13,    14,    15,    26,     3,    16,
       4,     4,    21,    22,    94,     4,    27,    25,     4,    99,
      26,    31,    27,    27,   104,    10,    11,    12,    13,    14,
      15,     9,    31,    25,    25,     5,    21,    22,    53,    -1,
      92,   104,    43,    -1,    -1,    -1,    49
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    17,    19,    37,    38,    39,    40,    41,    56,
      59,    62,    26,    26,     0,    39,    25,    26,    18,    20,
       4,     5,     6,    54,    60,    61,    62,    10,    11,    12,
      13,    14,    15,    21,    22,    42,    43,    44,    45,    49,
      26,    25,    28,    25,    25,    25,    25,    25,    26,    26,
      25,    27,    44,    57,    58,    62,    60,    29,    55,    60,
      61,    60,    60,     4,     4,    16,    46,     8,    40,    44,
      50,    51,    52,    54,    62,     4,    27,    58,    25,    27,
      29,    30,    26,    27,    60,    27,    51,    27,     4,    60,
      12,    23,    47,    48,    31,    25,    25,    27,    48,    50,
      53,    60,    60,     9,    31,    53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    37,    37,    38,    38,    39,    39,    39,    39,
      40,    41,    42,    42,    43,    43,    44,    44,    44,    44,
      44,    44,    44,    44,    45,    46,    47,    47,    48,    48,
      49,    50,    50,    51,    51,    51,    51,    52,    52,    53,
      54,    54,    55,    55,    56,    57,    57,    58,    59,    60,
      60,    60,    60,    61,    61,    62
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     1,
       3,     4,     1,     0,     1,     2,     3,     3,     3,     3,
       3,     3,     1,     1,     4,     4,     1,     2,     3,     3,
       4,     1,     2,     1,     1,     1,     1,     4,     7,     1,
       4,     3,     1,     3,     7,     1,     2,     3,     6,     1,
       1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: statement_list  */
#line 79 "usl.y"
                   {
        (yyval.ast_node) = create_ast_node(AST_PROGRAM, NULL, yylineno);
        (yyval.ast_node)->child = (yyvsp[0].ast_node);
        ast_root = (yyval.ast_node);
        printf("Parsing completed successfully.\n");
    }
#line 1238 "usl.tab.c"
    break;

  case 3: /* program: %empty  */
#line 85 "usl.y"
                  {
        (yyval.ast_node) = create_ast_node(AST_PROGRAM, NULL, yylineno);
        ast_root = (yyval.ast_node);
    }
#line 1247 "usl.tab.c"
    break;

  case 4: /* statement_list: statement  */
#line 92 "usl.y"
              {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1255 "usl.tab.c"
    break;

  case 5: /* statement_list: statement_list statement  */
#line 95 "usl.y"
                               {
        if ((yyvsp[-1].ast_node) == NULL) {
            (yyval.ast_node) = (yyvsp[0].ast_node);
        } else {
            ASTNode* current = (yyvsp[-1].ast_node);
            while (current->sibling != NULL) {
                current = current->sibling;
            }
            current->sibling = (yyvsp[0].ast_node);
            (yyval.ast_node) = (yyvsp[-1].ast_node);
        }
    }
#line 1272 "usl.tab.c"
    break;

  case 6: /* statement: variable_declaration  */
#line 110 "usl.y"
                         {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1280 "usl.tab.c"
    break;

  case 7: /* statement: page_definition  */
#line 113 "usl.y"
                      {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1288 "usl.tab.c"
    break;

  case 8: /* statement: navigation_block  */
#line 116 "usl.y"
                       {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1296 "usl.tab.c"
    break;

  case 9: /* statement: footer_block  */
#line 119 "usl.y"
                   {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1304 "usl.tab.c"
    break;

  case 10: /* variable_declaration: identifier ASSIGN expression  */
#line 125 "usl.y"
                                 {
        (yyval.ast_node) = create_ast_node(AST_VARIABLE_DECL, (yyvsp[-2].string_val), yylineno);
        (yyval.ast_node)->child = (yyvsp[0].ast_node);
        
        /* Add to symbol table */
        if (global_symbol_table) {
            add_symbol(global_symbol_table, (yyvsp[-2].string_val), SYMBOL_VARIABLE, yylineno);
        }
    }
#line 1318 "usl.tab.c"
    break;

  case 11: /* page_definition: identifier LBRACE page_body RBRACE  */
#line 137 "usl.y"
                                       {
        (yyval.ast_node) = create_ast_node(AST_PAGE_DEF, (yyvsp[-3].string_val), yylineno);
        (yyval.ast_node)->child = (yyvsp[-1].ast_node);
        
        /* Add page to symbol table */
        if (global_symbol_table) {
            add_symbol(global_symbol_table, (yyvsp[-3].string_val), SYMBOL_PAGE, yylineno);
        }
    }
#line 1332 "usl.tab.c"
    break;

  case 12: /* page_body: page_property_list  */
#line 149 "usl.y"
                       {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1340 "usl.tab.c"
    break;

  case 13: /* page_body: %empty  */
#line 152 "usl.y"
                  {
        (yyval.ast_node) = NULL;
    }
#line 1348 "usl.tab.c"
    break;

  case 14: /* page_property_list: page_property  */
#line 158 "usl.y"
                  {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1356 "usl.tab.c"
    break;

  case 15: /* page_property_list: page_property_list page_property  */
#line 161 "usl.y"
                                       {
        if ((yyvsp[-1].ast_node) == NULL) {
            (yyval.ast_node) = (yyvsp[0].ast_node);
        } else {
            ASTNode* current = (yyvsp[-1].ast_node);
            while (current->sibling != NULL) {
                current = current->sibling;
            }
            current->sibling = (yyvsp[0].ast_node);
            (yyval.ast_node) = (yyvsp[-1].ast_node);
        }
    }
#line 1373 "usl.tab.c"
    break;

  case 16: /* page_property: URL ASSIGN string_expression  */
#line 176 "usl.y"
                                 {
        (yyval.ast_node) = create_ast_node(AST_URL_PROP, "url", yylineno);
        (yyval.ast_node)->child = (yyvsp[0].ast_node);
    }
#line 1382 "usl.tab.c"
    break;

  case 17: /* page_property: TITLE ASSIGN expression  */
#line 180 "usl.y"
                              {
        (yyval.ast_node) = create_ast_node(AST_TITLE_PROP, "title", yylineno);
        (yyval.ast_node)->child = (yyvsp[0].ast_node);
    }
#line 1391 "usl.tab.c"
    break;

  case 18: /* page_property: DESCRIPTION ASSIGN expression  */
#line 184 "usl.y"
                                    {
        (yyval.ast_node) = create_ast_node(AST_DESC_PROP, "description", yylineno);
        (yyval.ast_node)->child = (yyvsp[0].ast_node);
    }
#line 1400 "usl.tab.c"
    break;

  case 19: /* page_property: TEMPLATE ASSIGN STRING_LITERAL  */
#line 188 "usl.y"
                                     {
        (yyval.ast_node) = create_ast_node(AST_TEMPLATE_PROP, "template", yylineno);
        (yyval.ast_node)->child = create_ast_node(AST_STRING_LITERAL, (yyvsp[0].string_val), yylineno);
    }
#line 1409 "usl.tab.c"
    break;

  case 20: /* page_property: ACCESS ASSIGN STRING_LITERAL  */
#line 192 "usl.y"
                                   {
        (yyval.ast_node) = create_ast_node(AST_ACCESS_PROP, "access", yylineno);
        (yyval.ast_node)->child = create_ast_node(AST_STRING_LITERAL, (yyvsp[0].string_val), yylineno);
    }
#line 1418 "usl.tab.c"
    break;

  case 21: /* page_property: REDIRECT ASSIGN STRING_LITERAL  */
#line 196 "usl.y"
                                     {
        (yyval.ast_node) = create_ast_node(AST_REDIRECT_PROP, "redirect", yylineno);
        (yyval.ast_node)->child = create_ast_node(AST_STRING_LITERAL, (yyvsp[0].string_val), yylineno);
    }
#line 1427 "usl.tab.c"
    break;

  case 22: /* page_property: seo_block  */
#line 200 "usl.y"
                {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1435 "usl.tab.c"
    break;

  case 23: /* page_property: generate_content_block  */
#line 203 "usl.y"
                             {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1443 "usl.tab.c"
    break;

  case 24: /* seo_block: SEO LBRACE meta_tags_block RBRACE  */
#line 209 "usl.y"
                                      {
        (yyval.ast_node) = create_ast_node(AST_SEO_BLOCK, "seo", yylineno);
        (yyval.ast_node)->child = (yyvsp[-1].ast_node);
    }
#line 1452 "usl.tab.c"
    break;

  case 25: /* meta_tags_block: META_TAGS LBRACE meta_tag_list RBRACE  */
#line 216 "usl.y"
                                          {
        (yyval.ast_node) = create_ast_node(AST_META_TAGS_BLOCK, "meta_tags", yylineno);
        (yyval.ast_node)->child = (yyvsp[-1].ast_node);
    }
#line 1461 "usl.tab.c"
    break;

  case 26: /* meta_tag_list: meta_tag  */
#line 223 "usl.y"
             {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1469 "usl.tab.c"
    break;

  case 27: /* meta_tag_list: meta_tag_list meta_tag  */
#line 226 "usl.y"
                             {
        if ((yyvsp[-1].ast_node) == NULL) {
            (yyval.ast_node) = (yyvsp[0].ast_node);
        } else {
            ASTNode* current = (yyvsp[-1].ast_node);
            while (current->sibling != NULL) {
                current = current->sibling;
            }
            current->sibling = (yyvsp[0].ast_node);
            (yyval.ast_node) = (yyvsp[-1].ast_node);
        }
    }
#line 1486 "usl.tab.c"
    break;

  case 28: /* meta_tag: DESCRIPTION ASSIGN expression  */
#line 241 "usl.y"
                                  {
        (yyval.ast_node) = create_ast_node(AST_META_DESC, "description", yylineno);
        (yyval.ast_node)->child = (yyvsp[0].ast_node);
    }
#line 1495 "usl.tab.c"
    break;

  case 29: /* meta_tag: KEYWORDS ASSIGN expression  */
#line 245 "usl.y"
                                 {
        (yyval.ast_node) = create_ast_node(AST_META_KEYWORDS, "keywords", yylineno);
        (yyval.ast_node)->child = (yyvsp[0].ast_node);
    }
#line 1504 "usl.tab.c"
    break;

  case 30: /* generate_content_block: GENERATE_CONTENT LBRACE generate_statement_list RBRACE  */
#line 252 "usl.y"
                                                           {
        (yyval.ast_node) = create_ast_node(AST_GENERATE_CONTENT, "generate_content", yylineno);
        (yyval.ast_node)->child = (yyvsp[-1].ast_node);
    }
#line 1513 "usl.tab.c"
    break;

  case 31: /* generate_statement_list: generate_statement  */
#line 259 "usl.y"
                       {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1521 "usl.tab.c"
    break;

  case 32: /* generate_statement_list: generate_statement_list generate_statement  */
#line 262 "usl.y"
                                                 {
        if ((yyvsp[-1].ast_node) == NULL) {
            (yyval.ast_node) = (yyvsp[0].ast_node);
        } else {
            ASTNode* current = (yyvsp[-1].ast_node);
            while (current->sibling != NULL) {
                current = current->sibling;
            }
            current->sibling = (yyvsp[0].ast_node);
            (yyval.ast_node) = (yyvsp[-1].ast_node);
        }
    }
#line 1538 "usl.tab.c"
    break;

  case 33: /* generate_statement: variable_declaration  */
#line 277 "usl.y"
                         {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1546 "usl.tab.c"
    break;

  case 34: /* generate_statement: function_call  */
#line 280 "usl.y"
                    {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1554 "usl.tab.c"
    break;

  case 35: /* generate_statement: conditional_statement  */
#line 283 "usl.y"
                            {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1562 "usl.tab.c"
    break;

  case 36: /* generate_statement: page_property  */
#line 286 "usl.y"
                    {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1570 "usl.tab.c"
    break;

  case 37: /* conditional_statement: IF expression COLON statement_block  */
#line 292 "usl.y"
                                                              {
        (yyval.ast_node) = create_ast_node(AST_IF_STMT, "if", yylineno);
        (yyval.ast_node)->child = (yyvsp[-2].ast_node);
        (yyvsp[-2].ast_node)->sibling = (yyvsp[0].ast_node);
    }
#line 1580 "usl.tab.c"
    break;

  case 38: /* conditional_statement: IF expression COLON statement_block ELSE COLON statement_block  */
#line 297 "usl.y"
                                                                     {
        (yyval.ast_node) = create_ast_node(AST_IF_ELSE_STMT, "if_else", yylineno);
        (yyval.ast_node)->child = (yyvsp[-5].ast_node);
        (yyvsp[-5].ast_node)->sibling = (yyvsp[-3].ast_node);
        (yyvsp[-3].ast_node)->sibling = (yyvsp[0].ast_node);
    }
#line 1591 "usl.tab.c"
    break;

  case 39: /* statement_block: generate_statement_list  */
#line 306 "usl.y"
                            {
        (yyval.ast_node) = create_ast_node(AST_STATEMENT_BLOCK, "block", yylineno);
        (yyval.ast_node)->child = (yyvsp[0].ast_node);
    }
#line 1600 "usl.tab.c"
    break;

  case 40: /* function_call: identifier LPAREN argument_list RPAREN  */
#line 313 "usl.y"
                                           {
        (yyval.ast_node) = create_ast_node(AST_FUNCTION_CALL, (yyvsp[-3].string_val), yylineno);
        (yyval.ast_node)->child = (yyvsp[-1].ast_node);
    }
#line 1609 "usl.tab.c"
    break;

  case 41: /* function_call: identifier LPAREN RPAREN  */
#line 317 "usl.y"
                               {
        (yyval.ast_node) = create_ast_node(AST_FUNCTION_CALL, (yyvsp[-2].string_val), yylineno);
    }
#line 1617 "usl.tab.c"
    break;

  case 42: /* argument_list: expression  */
#line 323 "usl.y"
               {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1625 "usl.tab.c"
    break;

  case 43: /* argument_list: argument_list COMMA expression  */
#line 326 "usl.y"
                                     {
        if ((yyvsp[-2].ast_node) == NULL) {
            (yyval.ast_node) = (yyvsp[0].ast_node);
        } else {
            ASTNode* current = (yyvsp[-2].ast_node);
            while (current->sibling != NULL) {
                current = current->sibling;
            }
            current->sibling = (yyvsp[0].ast_node);
            (yyval.ast_node) = (yyvsp[-2].ast_node);
        }
    }
#line 1642 "usl.tab.c"
    break;

  case 44: /* navigation_block: NAVIGATION LBRACE LINKS LBRACE link_list RBRACE RBRACE  */
#line 341 "usl.y"
                                                           {
        (yyval.ast_node) = create_ast_node(AST_NAVIGATION, "navigation", yylineno);
        (yyval.ast_node)->child = (yyvsp[-2].ast_node);
    }
#line 1651 "usl.tab.c"
    break;

  case 45: /* link_list: link  */
#line 348 "usl.y"
         {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1659 "usl.tab.c"
    break;

  case 46: /* link_list: link_list link  */
#line 351 "usl.y"
                     {
        if ((yyvsp[-1].ast_node) == NULL) {
            (yyval.ast_node) = (yyvsp[0].ast_node);
        } else {
            ASTNode* current = (yyvsp[-1].ast_node);
            while (current->sibling != NULL) {
                current = current->sibling;
            }
            current->sibling = (yyvsp[0].ast_node);
            (yyval.ast_node) = (yyvsp[-1].ast_node);
        }
    }
#line 1676 "usl.tab.c"
    break;

  case 47: /* link: identifier ASSIGN STRING_LITERAL  */
#line 366 "usl.y"
                                     {
        (yyval.ast_node) = create_ast_node(AST_LINK, (yyvsp[-2].string_val), yylineno);
        (yyval.ast_node)->child = create_ast_node(AST_STRING_LITERAL, (yyvsp[0].string_val), yylineno);
    }
#line 1685 "usl.tab.c"
    break;

  case 48: /* footer_block: FOOTER LBRACE TEXT ASSIGN expression RBRACE  */
#line 373 "usl.y"
                                                {
        (yyval.ast_node) = create_ast_node(AST_FOOTER, "footer", 0);
        (yyval.ast_node)->child = (yyvsp[-1].ast_node);
    }
#line 1694 "usl.tab.c"
    break;

  case 49: /* expression: string_expression  */
#line 380 "usl.y"
                      {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1702 "usl.tab.c"
    break;

  case 50: /* expression: VARIABLE_REF  */
#line 383 "usl.y"
                   {
        (yyval.ast_node) = create_ast_node(AST_VARIABLE_REF, (yyvsp[0].string_val), 0);
    }
#line 1710 "usl.tab.c"
    break;

  case 51: /* expression: function_call  */
#line 386 "usl.y"
                    {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1718 "usl.tab.c"
    break;

  case 52: /* expression: identifier  */
#line 389 "usl.y"
                 {
        (yyval.ast_node) = create_ast_node(AST_IDENTIFIER, (yyvsp[0].string_val), 0);
    }
#line 1726 "usl.tab.c"
    break;

  case 53: /* string_expression: STRING_LITERAL  */
#line 395 "usl.y"
                   {
        (yyval.ast_node) = create_ast_node(AST_STRING_LITERAL, (yyvsp[0].string_val), 0);
    }
#line 1734 "usl.tab.c"
    break;

  case 54: /* string_expression: URL_PATTERN  */
#line 398 "usl.y"
                  {
        (yyval.ast_node) = create_ast_node(AST_URL_PATTERN, (yyvsp[0].string_val), 0);
    }
#line 1742 "usl.tab.c"
    break;

  case 55: /* identifier: IDENTIFIER  */
#line 404 "usl.y"
               {
        (yyval.string_val) = strdup((yyvsp[0].string_val));
    }
#line 1750 "usl.tab.c"
    break;


#line 1754 "usl.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 410 "usl.y"


/* User Code Section */

void yyerror(const char* s) {
    // Avoid duplicate error messages for the same line
    if (last_error_line == yylineno) {
        return;
    }
    
    last_error_line = yylineno;
    
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
    
    // Provide additional context about the error
    if (yytext && strlen(yytext) > 0) {
        fprintf(stderr, "Error near token: '%s'\n", yytext);
        
        // Provide specific guidance based on common error patterns
        if (strcmp(s, "syntax error") == 0) {
            // Try to guess what might be missing based on the current token
            if (strcmp(yytext, "{") == 0) {
                fprintf(stderr, "Possible issue: Missing closing '}' or incorrect block structure\n");
            } else if (strcmp(yytext, "}") == 0) {
                fprintf(stderr, "Possible issue: Mismatched braces or unexpected closing brace\n");
            } else if (strcmp(yytext, "=") == 0) {
                fprintf(stderr, "Possible issue: Missing value after assignment operator\n");
            } else if (strcmp(yytext, ";") == 0) {
                fprintf(stderr, "Possible issue: Unexpected semicolon (USL uses newlines for statement separation)\n");
            } else {
                fprintf(stderr, "Possible issues: Missing required syntax element or incorrect token usage\n");
            }
        }
    } else {
        fprintf(stderr, "Error at end of input - possible incomplete statement\n");
    }
    
    parse_error_count++;
}

void print_parse_tree_helper(ASTNode* node, int depth, int is_last[], int parent_depth) {
    if (node == NULL) return;
    
    /* Print tree structure with ASCII characters */
    for (int i = 0; i < depth; i++) {
        if (i == depth - 1) {
            /* Last level - print branch */
            if (is_last[i]) {
                printf("+-- ");
            } else {
                printf("|-- ");
            }
        } else {
            /* Previous levels - print vertical line or space */
            if (is_last[i]) {
                printf("    ");
            } else {
                printf("|   ");
            }
        }
    }
    
    /* Print node information */
    printf("%s", ast_node_type_names[node->type]);
    if (node->value) {
        printf(" [%s]", node->value);
    }
    printf("\n");
    
    /* Update is_last array for children */
    int new_is_last[100];
    for (int i = 0; i <= depth; i++) {
        new_is_last[i] = is_last[i];
    }
    
    /* Print children */
    if (node->child) {
        ASTNode* child = node->child;
        while (child != NULL) {
            new_is_last[depth + 1] = (child->sibling == NULL);
            print_parse_tree_helper(child, depth + 1, new_is_last, depth);
            child = child->sibling;
        }
    }
}

void print_parse_tree(ASTNode* node, int depth) {
    if (node == NULL) return;
    
    int is_last[100] = {0};
    is_last[0] = 1;
    
    /* Print root node */
    printf("%s", ast_node_type_names[node->type]);
    if (node->value) {
        printf(" [%s]", node->value);
    }
    printf("\n");
    
    /* Print children */
    if (node->child) {
        ASTNode* child = node->child;
        while (child != NULL) {
            is_last[1] = (child->sibling == NULL);
            print_parse_tree_helper(child, 1, is_last, 0);
            child = child->sibling;
        }
    }
}

int parse_usl_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return -1;
    }
    
    yyin = file;
    
    /* Reset lexer state and error counters */
    reset_lexer();
    
    /* Initialize symbol table */
    global_symbol_table = create_symbol_table();
    
    printf("Starting parse of %s...\n", filename);
    
    int result = yyparse();
    
    fclose(file);
    
    /* Print token table first */
    print_token_table();
    
    /* Print lexical errors */
    print_lexical_error_table();
    
    if (result == 0 && parse_error_count == 0) {
        printf("\nParsing completed successfully!\n");
        printf("\n");
        printf("==========================================\n");
        printf("    Abstract Syntax Tree\n");
        printf("==========================================\n");
        print_parse_tree(ast_root, 0);
        
        printf("\n");
        printf("==========================================\n");
        printf("    Symbol Table\n");
        printf("==========================================\n");
        print_symbol_table(global_symbol_table);
        
        /* Perform semantic analysis */
        printf("\n");
        printf("==========================================\n");
        printf("    Semantic Analysis\n");
        printf("==========================================\n");
        int semantic_result = semantic_analysis(ast_root);
        
        return semantic_result;
    } else {
        printf("\nParsing failed with %d errors.\n", parse_error_count);
        return -1;
    }
}

/* Main function for standalone parser testing */
#ifdef STANDALONE_PARSER
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <usl_file>\n", argv[0]);
        return 1;
    }
    
    int result = parse_usl_file(argv[1]);
    
    /* Cleanup */
    if (global_symbol_table) {
        free_symbol_table(global_symbol_table);
    }
    if (ast_root) {
        free_ast_tree(ast_root);
    }
    
    return (result == 0) ? 0 : 1;
}
#endif
