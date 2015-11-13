/* A Bison parser, made by GNU Bison 2.7.91.2-c16b7-dirty.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7.91.2-c16b7-dirty"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "lang.y" /* yacc.c:356  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//int yydebug=1;

typedef struct cmd cmd;
typedef struct cmdList cmdList;
typedef struct symtab symtab;
typedef struct funtab funtab;
typedef struct exprn exprn;
typedef struct arglist arglist;
typedef enum boolean boolean;

struct arglist {
    char *name;
    arglist *next;
};

enum boolean {false, true};

struct symtab {
    char *name;
    int ival;
    boolean bval;
    char cval;
    int type;
    symtab *next;
};


struct funtab {
    char *name;
    arglist *args;
    cmdList *body;
    funtab *next;
};

struct exprn {
    char type;  //+-*/><, = - ==, G - >=, L - <=, N - !=, ! - not, n - number, v - variable, f - function, t - type
    int val;    //if it's a number
    char *var;  //if it's a variable
    exprn *left;
    exprn *right;
    arglist *args;
};


struct cmd {
    char type; //a - assignment, d - do, i - if, s - show, z - stop, l - loop, e - bare expression, r - return
    char *var;
    exprn *exp;
    cmdList *cmnd;
};

struct cmdList {
    cmd *curr;
    cmdList *rest;
};

arglist * makeArgList(char *arg, arglist *n) {
    arglist *ret = malloc(sizeof(arglist));
    ret->name = arg;
    ret->next = n;
    return ret;
}

cmdList * makeCmdList(cmd *c, cmdList *r) {
    cmdList *ret = malloc(sizeof(cmdList));
    ret->curr = c;
    ret->rest = r;
    return ret;
}

cmd * makeCmd(char t, char *v, exprn *e, cmdList *c) {
    cmd *ret = malloc(sizeof(cmd));
    ret->type = t;
    ret->var = v;
    ret->exp = e;
    ret->cmnd = c;
    return ret;
}

exprn * makeExprn(char t, int v, char* name, exprn *l, exprn *r) {
    exprn *ret = malloc(sizeof(exprn));
    ret->type = t;
    ret->val = v;
    ret->var = name;
    ret->left = l;
    ret->right = r;
    return ret;
}

exprn * makeFunctionExprn(char *name, arglist *args) {
    exprn *ret = malloc(sizeof(exprn));
    ret->type = 'f';
    ret->var = name;
    ret->args = args;
    return ret;
}

cmdList * getFunBody(char *name, funtab *t) {
    if(strcmp(name, t->name) == 0)
        return t->body;
    else if(t->next != NULL)
        return getFunBody(name, t->next);
    printf("Error, function %s not defined before use\n", name);
    return NULL;
}

arglist * getFunArgs(char *name, funtab *t) {
    if(strcmp(name, t->name) == 0)
        return t->args;
    else if(t->next != NULL)
        return getFunArgs(name, t->next);
    printf("Error, function %s does not have suitable args\n", name);
    return NULL;
}

void setFun(char *name, arglist *args, cmdList *body,funtab *t) {
    if(strcmp(name, t->name) == 0) {
        t->body = body;
        t->args = args;
    }
    else if(t->next != NULL)
        setFun(name, args, body, t->next);
    else {
        t->next = malloc(sizeof(funtab));
        t->next->name = malloc(strlen(name));
        strcpy(t->next->name, name);
        t->next->args = args;
        t->next->body = body;
        t->next->next = NULL;
    }
}

funtab functions = {"main", NULL, NULL};

#line 208 "y.tab.c" /* yacc.c:356  */

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMBER = 258,
    IDENTIFIER = 259,
    SHOW = 260,
    DO = 261,
    TIMES = 262,
    STOP = 263,
    END = 264,
    IF = 265,
    GTEQ = 266,
    LTEQ = 267,
    EQ = 268,
    NEQ = 269,
    LOOP = 270,
    FUN = 271,
    RET = 272
  };
#endif
/* Tokens.  */
#define NUMBER 258
#define IDENTIFIER 259
#define SHOW 260
#define DO 261
#define TIMES 262
#define STOP 263
#define END 264
#define IF 265
#define GTEQ 266
#define LTEQ 267
#define EQ 268
#define NEQ 269
#define LOOP 270
#define FUN 271
#define RET 272

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 143 "lang.y" /* yacc.c:372  */

	cmdList *cList;
	int  num;
    exprn *exp;
    cmd *c;
    char *name;
    arglist *arg;

#line 288 "y.tab.c" /* yacc.c:372  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 303 "y.tab.c" /* yacc.c:375  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   203

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  8
/* YYNRULES -- Number of rules.  */
#define YYNRULES  36
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  80

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   272

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    24,     2,     2,     2,     2,     2,     2,
      25,    26,    20,    18,    32,    19,     2,    21,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    31,    30,
      23,    29,    22,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    27,     2,    28,     2,     2,     2,     2,
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
      15,    16,    17
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   170,   170,   171,   174,   175,   178,   179,   182,   183,
     186,   187,   188,   189,   190,   191,   192,   193,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   215,   216
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "IDENTIFIER", "SHOW", "DO",
  "TIMES", "STOP", "END", "IF", "GTEQ", "LTEQ", "EQ", "NEQ", "LOOP", "FUN",
  "RET", "'+'", "'-'", "'*'", "'/'", "'>'", "'<'", "'!'", "'('", "')'",
  "'{'", "'}'", "'='", "';'", "':'", "','", "$accept", "prog", "funlist",
  "commlist", "block", "comm", "expr", "args", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,    43,    45,
      42,    47,    62,    60,    33,    40,    41,   123,   125,    61,
      59,    58,    44
};
# endif

#define YYPACT_NINF -20

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-20)))

#define YYTABLE_NINF -6

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      12,   -20,    13,    18,   -20,    -3,   -20,    16,    -6,     1,
      16,    38,   -20,   -20,   -15,     0,     0,    17,    24,    38,
       0,     0,     0,     0,    63,    34,   -20,    72,    16,     0,
      21,    20,    85,   131,   -20,     0,   -20,    98,   176,   -20,
     144,    26,    63,   -20,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -20,    30,   111,   -20,   -20,    38,
     160,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   176,
     176,   180,   180,   -20,   -20,   -20,   -20,   -20,    38,   -20
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,     0,     2,     0,     1,     0,    36,     0,
       0,     0,    35,    32,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     7,     5,     8,     0,     0,     0,
       0,    33,     0,     0,    14,     0,    15,     0,    21,    30,
       0,     0,     7,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    16,     0,     0,    34,    13,     0,
       0,    17,    18,     9,     6,    27,    28,    26,    29,    19,
      20,    22,    23,    24,    25,    31,    10,    11,     0,    12
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -20,   -20,    33,    19,   -19,   -13,   -14,    -5
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,    41,    25,    26,    27,     9
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      36,    32,    33,    13,    31,    12,    37,    38,    39,    40,
      28,    42,    -5,     1,    29,    56,    30,     5,     6,    21,
       8,    60,     7,    55,    22,    23,    10,    11,     2,    42,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      77,    13,    14,    15,    16,    28,    17,    34,    18,    35,
       2,    30,    57,    19,    63,    20,    75,    21,    43,    79,
       0,    64,    22,    23,     0,    24,    13,    14,    15,    16,
       0,    17,     0,    18,     0,     0,     0,     0,    19,     0,
      20,     0,    21,    44,    45,    46,    47,    22,    23,     0,
      48,    49,    50,    51,    52,    53,    44,    45,    46,    47,
       0,     0,    54,    48,    49,    50,    51,    52,    53,    44,
      45,    46,    47,     0,     0,    58,    48,    49,    50,    51,
      52,    53,    44,    45,    46,    47,     0,     0,    61,    48,
      49,    50,    51,    52,    53,     0,     0,     0,    59,     0,
       0,    76,    44,    45,    46,    47,     0,     0,     0,    48,
      49,    50,    51,    52,    53,    44,    45,    46,    47,     0,
       0,     0,    48,    49,    50,    51,    52,    53,     0,     0,
      62,    44,    45,    46,    47,     0,     0,     0,    48,    49,
      50,    51,    52,    53,     0,     0,    78,    44,    45,    46,
      47,    44,    45,    46,    47,     0,    50,    51,    52,    53,
       0,     0,    52,    53
};

static const yytype_int8 yycheck[] =
{
      19,    15,    16,     3,     4,    10,    20,    21,    22,    23,
      25,    24,     0,     1,    29,    29,    31,     4,     0,    19,
       4,    35,    25,    28,    24,    25,    32,    26,    16,    42,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      59,     3,     4,     5,     6,    25,     8,    30,    10,    25,
      16,    31,    31,    15,    28,    17,    26,    19,    25,    78,
      -1,    42,    24,    25,    -1,    27,     3,     4,     5,     6,
      -1,     8,    -1,    10,    -1,    -1,    -1,    -1,    15,    -1,
      17,    -1,    19,    11,    12,    13,    14,    24,    25,    -1,
      18,    19,    20,    21,    22,    23,    11,    12,    13,    14,
      -1,    -1,    30,    18,    19,    20,    21,    22,    23,    11,
      12,    13,    14,    -1,    -1,    30,    18,    19,    20,    21,
      22,    23,    11,    12,    13,    14,    -1,    -1,    30,    18,
      19,    20,    21,    22,    23,    -1,    -1,    -1,     7,    -1,
      -1,    30,    11,    12,    13,    14,    -1,    -1,    -1,    18,
      19,    20,    21,    22,    23,    11,    12,    13,    14,    -1,
      -1,    -1,    18,    19,    20,    21,    22,    23,    -1,    -1,
      26,    11,    12,    13,    14,    -1,    -1,    -1,    18,    19,
      20,    21,    22,    23,    -1,    -1,    26,    11,    12,    13,
      14,    11,    12,    13,    14,    -1,    20,    21,    22,    23,
      -1,    -1,    22,    23
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    16,    34,    35,     4,     0,    25,     4,    40,
      32,    26,    40,     3,     4,     5,     6,     8,    10,    15,
      17,    19,    24,    25,    27,    37,    38,    39,    25,    29,
      31,     4,    39,    39,    30,    25,    37,    39,    39,    39,
      39,    36,    38,    35,    11,    12,    13,    14,    18,    19,
      20,    21,    22,    23,    30,    40,    39,    31,    30,     7,
      39,    30,    26,    28,    36,    39,    39,    39,    39,    39,
      39,    39,    39,    39,    39,    26,    30,    37,    26,    37
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    34,    35,    35,    36,    36,    37,    37,
      38,    38,    38,    38,    38,    38,    38,    38,    39,    39,
      39,    39,    39,    39,    39,    39,    39,    39,    39,    39,
      39,    39,    39,    39,    39,    40,    40
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     7,     0,     2,     0,     1,     3,
       4,     4,     5,     3,     2,     2,     2,     3,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     4,     1,     1,     3,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE (yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 3:
#line 171 "lang.y" /* yacc.c:1663  */
    { yyerrok; printf("Error!\n"); }
#line 1416 "y.tab.c" /* yacc.c:1663  */
    break;

  case 4:
#line 174 "lang.y" /* yacc.c:1663  */
    { setFun((yyvsp[-5].name), (yyvsp[-3].arg), (yyvsp[-1].cList), &functions); }
#line 1422 "y.tab.c" /* yacc.c:1663  */
    break;

  case 6:
#line 178 "lang.y" /* yacc.c:1663  */
    { (yyval.cList) = makeCmdList((yyvsp[-1].c), (yyvsp[0].cList)); }
#line 1428 "y.tab.c" /* yacc.c:1663  */
    break;

  case 7:
#line 179 "lang.y" /* yacc.c:1663  */
    { (yyval.cList) = NULL; }
#line 1434 "y.tab.c" /* yacc.c:1663  */
    break;

  case 8:
#line 182 "lang.y" /* yacc.c:1663  */
    { (yyval.cList) = makeCmdList((yyvsp[0].c), NULL); }
#line 1440 "y.tab.c" /* yacc.c:1663  */
    break;

  case 9:
#line 183 "lang.y" /* yacc.c:1663  */
    { (yyval.cList) = (yyvsp[-1].cList); }
#line 1446 "y.tab.c" /* yacc.c:1663  */
    break;

  case 10:
#line 186 "lang.y" /* yacc.c:1663  */
    { (yyval.c) = makeCmd('a', (yyvsp[-3].name), (yyvsp[-1].exp), NULL); }
#line 1452 "y.tab.c" /* yacc.c:1663  */
    break;

  case 11:
#line 187 "lang.y" /* yacc.c:1663  */
    { (yyval.c) = makeCmd('d', NULL, (yyvsp[-2].exp), (yyvsp[0].cList)); }
#line 1458 "y.tab.c" /* yacc.c:1663  */
    break;

  case 12:
#line 188 "lang.y" /* yacc.c:1663  */
    { (yyval.c) = makeCmd('i', NULL, (yyvsp[-2].exp), (yyvsp[0].cList)); }
#line 1464 "y.tab.c" /* yacc.c:1663  */
    break;

  case 13:
#line 189 "lang.y" /* yacc.c:1663  */
    { (yyval.c) = makeCmd('s', NULL, (yyvsp[-1].exp), NULL); }
#line 1470 "y.tab.c" /* yacc.c:1663  */
    break;

  case 14:
#line 190 "lang.y" /* yacc.c:1663  */
    { (yyval.c) = makeCmd('z', NULL, NULL, NULL); }
#line 1476 "y.tab.c" /* yacc.c:1663  */
    break;

  case 15:
#line 191 "lang.y" /* yacc.c:1663  */
    { (yyval.c) = makeCmd('l', NULL, NULL, (yyvsp[0].cList)); }
#line 1482 "y.tab.c" /* yacc.c:1663  */
    break;

  case 16:
#line 192 "lang.y" /* yacc.c:1663  */
    { (yyval.c) = makeCmd('e', NULL, (yyvsp[-1].exp), NULL); }
#line 1488 "y.tab.c" /* yacc.c:1663  */
    break;

  case 17:
#line 193 "lang.y" /* yacc.c:1663  */
    { (yyval.c) = makeCmd('r', NULL, (yyvsp[-1].exp), NULL); }
#line 1494 "y.tab.c" /* yacc.c:1663  */
    break;

  case 18:
#line 196 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = (yyvsp[-1].exp); }
#line 1500 "y.tab.c" /* yacc.c:1663  */
    break;

  case 19:
#line 197 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = makeExprn('+', 0, NULL, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1506 "y.tab.c" /* yacc.c:1663  */
    break;

  case 20:
#line 198 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = makeExprn('-', 0, NULL, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1512 "y.tab.c" /* yacc.c:1663  */
    break;

  case 21:
#line 199 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = makeExprn('-', 0, NULL, makeExprn('n', 0, NULL, NULL, NULL), (yyvsp[0].exp)); }
#line 1518 "y.tab.c" /* yacc.c:1663  */
    break;

  case 22:
#line 200 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = makeExprn('*', 0, NULL, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1524 "y.tab.c" /* yacc.c:1663  */
    break;

  case 23:
#line 201 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = makeExprn('/', 0, NULL, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1530 "y.tab.c" /* yacc.c:1663  */
    break;

  case 24:
#line 202 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = makeExprn('>', 0, NULL, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1536 "y.tab.c" /* yacc.c:1663  */
    break;

  case 25:
#line 203 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = makeExprn('<', 0, NULL, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1542 "y.tab.c" /* yacc.c:1663  */
    break;

  case 26:
#line 204 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = makeExprn('=', 0, NULL, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1548 "y.tab.c" /* yacc.c:1663  */
    break;

  case 27:
#line 205 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = makeExprn('G', 0, NULL, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1554 "y.tab.c" /* yacc.c:1663  */
    break;

  case 28:
#line 206 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = makeExprn('L', 0, NULL, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1560 "y.tab.c" /* yacc.c:1663  */
    break;

  case 29:
#line 207 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = makeExprn('N', 0, NULL, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1566 "y.tab.c" /* yacc.c:1663  */
    break;

  case 30:
#line 208 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = makeExprn('!', 0, NULL, (yyvsp[0].exp), NULL); }
#line 1572 "y.tab.c" /* yacc.c:1663  */
    break;

  case 31:
#line 209 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = makeFunctionExprn((yyvsp[-3].name), (yyvsp[-1].arg)); }
#line 1578 "y.tab.c" /* yacc.c:1663  */
    break;

  case 32:
#line 210 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = makeExprn('n', (yyvsp[0].num), NULL, NULL, NULL); }
#line 1584 "y.tab.c" /* yacc.c:1663  */
    break;

  case 33:
#line 211 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = makeExprn('v', 0, (yyvsp[0].name), NULL, NULL); }
#line 1590 "y.tab.c" /* yacc.c:1663  */
    break;

  case 34:
#line 212 "lang.y" /* yacc.c:1663  */
    { (yyval.exp) = makeExprn('t', 0, (yyvsp[-2].name), NULL, NULL); }
#line 1596 "y.tab.c" /* yacc.c:1663  */
    break;

  case 35:
#line 215 "lang.y" /* yacc.c:1663  */
    { (yyval.arg) = makeArgList((yyvsp[-2].name), (yyvsp[0].arg)); }
#line 1602 "y.tab.c" /* yacc.c:1663  */
    break;

  case 36:
#line 216 "lang.y" /* yacc.c:1663  */
    { (yyval.arg) = makeArgList((yyvsp[0].name), NULL); }
#line 1608 "y.tab.c" /* yacc.c:1663  */
    break;


#line 1612 "y.tab.c" /* yacc.c:1663  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 220 "lang.y" /* yacc.c:1923  */


#include "lex.yy.c"

yyerror(s)
char *s;
{printf("%s\n", s);
}

void setVal(int val, symtab *t, int type) {
    if(type==0) {
            t->ival = val;
    } else if(type==1) {
        if(val%1) {
            t->bval = true;
        } else {
            t->bval = false;
        }
    } else {
        t->cval = (char)val;
    }
}

symtab *findVar(char *name, symtab *t) {
    if(t == NULL) return NULL;
    if(strcmp(name, t->name) == 0) {
        return t;
    }
    else if(t->next != NULL)
        return findVar(name, t->next);
    else return NULL;
}

int getType(char* name, symtab *t) {
    if(strcmp(name, t->name) == 0) {
        return t->type;
    } else if(t->next != NULL)
        return getType(name, t->next);
    else {
        return rand()%3;
    }
}

int getVar(char *name, symtab *t) {
    if(strcmp(name, t->name) == 0) {
        int oldtype = t->type;
        t->type = rand()%3;
        if(oldtype == 0) return t->ival;
        else if(oldtype == 1) return t->bval;
        else return t->cval;
    } else if(t->next != NULL)
        return getVar(name, t->next);
    else {
        t->next = malloc(sizeof(symtab));
        t = t->next;
        t->name = malloc(strlen(name));
        strcpy(t->name, name);
        t->type = rand()%3;
        setVal(0, t, t->type);
        t->type = rand()%3;
        t->next = NULL;
        printf("Auto-initializing %s\n", name);
        return 0;
    }
}

void setVar(char *name, int val, symtab *t) {
    if(strcmp(name, t->name) == 0) {
        setVal(val, t, t->type);
        t->type = rand()%3;
    }
    else if(t->next != NULL)
        setVar(name, val, t->next);
    else {
        t->next = malloc(sizeof(symtab));
        t = t->next;
        t->name = malloc(strlen(name));
        t->type = rand()%3;
        strcpy(t->name, name);
        setVal(val, t, t->type);
        t->type = rand()%3;
        t->next = NULL;
    }
}

void copyVars(arglist *oldargs, symtab *old, arglist *newargs, symtab *new) {
    while(oldargs != NULL && newargs != NULL) {
        setVar(newargs->name, getVar(oldargs->name, old), new);
        symtab *nvar = findVar(newargs->name, new), *ovar = findVar(oldargs->name, old);
        if(nvar != NULL && ovar != NULL) {
            nvar->ival = ovar->ival;
            nvar->bval = ovar->bval;
            nvar->cval = ovar->cval;
        }
        oldargs = oldargs->next;
        newargs = newargs->next;
    }
    if(oldargs!= NULL || newargs !=NULL)
        printf("Error! Not enough arguments!\n");
}

int applyFun(char *name, arglist *args, symtab *table) {
    symtab newtab = {"zero", 0, 0, 0, 0, NULL};
    copyVars(args, table, getFunArgs(name, &functions), &newtab);
    int ret = executeList(getFunBody(name, &functions), &newtab);
    return ret;
}


int evalExpr(exprn *e, symtab *table) {
    if(e==NULL) return 0;
    switch (e->type) {
        case '+' : return evalExpr(e->left, table)+evalExpr(e->right, table);
        case '-' : return evalExpr(e->left, table)-evalExpr(e->right, table);
        case '*' : return evalExpr(e->left, table)*evalExpr(e->right, table);
        case '/' : return evalExpr(e->left, table)/evalExpr(e->right, table);
        case '>' : return evalExpr(e->left, table)>evalExpr(e->right, table);
        case '<' : return evalExpr(e->left, table)<evalExpr(e->right, table);
        case '=' : return evalExpr(e->left, table)==evalExpr(e->right, table);
        case 'G' : return evalExpr(e->left, table)>=evalExpr(e->right, table);
        case 'L' : return evalExpr(e->left, table)<=evalExpr(e->right, table);
        case 'N' : return evalExpr(e->left, table)!=evalExpr(e->right, table);
        case '!' : return !(evalExpr(e->left, table));
        case 'f' : return applyFun(e->var, e->args, table);
        case 'n' : return e->val;
        case 'v' : return getVar(e->var, table);
        case 't' : return getType(e->var, table);
        default : return 0;
    }
}

int breakFlag = 0;
int retFlag = 0;
int retval = 0;
int executeList(cmdList *tree, symtab *table) {    //return value says if we had 'stop'

    if(tree==NULL) return 0;
    while(tree->curr != NULL) {
        cmd *curr = tree->curr;
        switch(curr->type){
            case 'a':
                setVar(curr->var, evalExpr(tree->curr->exp, table), table); break;
            case 'd': { //for the variable
                int count = evalExpr(curr->exp, table);
                while(count-->0 && breakFlag==0 && retFlag==0) { executeList(curr->cmnd, table);}
                } breakFlag = 0; if(retFlag!=0) {return retval; }break;
            case 'l': while(breakFlag==0) {executeList(curr->cmnd, table);} breakFlag = 0; if(retFlag!=0) {
retFlag=0; return retval; } break;
            case 's':
                printf("%d\n", evalExpr(curr->exp, table)); break;
            case 'z': breakFlag = 1; return 0; break;
            case 'i': if(evalExpr(curr->exp, table)) { int ret = executeList(curr->cmnd, table); if(retFlag!=0) { breakFlag =0; retFlag = 0; return ret; } if(breakFlag!=0) { return 0; } }break;
            case 'e': evalExpr(curr->exp, table); break;
            case 'r': {retval = evalExpr(curr->exp, table); breakFlag = 1; retFlag = 1; return retval;} break;
            default :
                printf("Unsupported Op: %c\n", curr->type);
        }


        if(tree == NULL || tree->rest == NULL) break;
        tree = tree->rest;
    }
    return retval;
}

main()
{ srand(time(NULL));
  yyparse();
  symtab table = {"zero", 0, 0, 0, 0, NULL};
  executeList(functions.body, &table);
}
