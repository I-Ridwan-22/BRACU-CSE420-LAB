/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "21201129.y"

#include "symbol_table.h"
#include <bits/stdc++.h>
using namespace std;

#define YYSTYPE symbol_info*

int yyparse(void);
int yylex(void);

extern FILE *yyin;
extern YYSTYPE yylval;

ofstream outlog;
ofstream outerror;

symbol_table* main_table = nullptr;
int lines = 1;
int error_count = 0;

/*helpers*/
static inline bool isNumericType(const string& t){
    return (t == "int" || t == "float");
}
static inline bool isVoidType(const string& t){
    return (t == "void");
}
static inline bool isUndefinedType(const string& t){
    return (t.empty() || t == "undefined");
}
static inline string promoteNumeric(const string& a, const string& b){
    if(isUndefinedType(a) || isUndefinedType(b)) return "undefined";
    if(isVoidType(a) || isVoidType(b)) return "void";
    if(a == "float" || b == "float") return "float";
    return "int";
}

static inline symbol_info* lookup_by_name(const string& name){
    if(!main_table) return nullptr;
    symbol_info temp(name, "ID");
    return main_table->lookup(&temp);
}

/*removing spaces and strip outer parentheses repeatedly*/
static inline string stripSpaces(string s){
    s.erase(remove_if(s.begin(), s.end(), [](unsigned char c){ return isspace(c); }), s.end());
    return s;
}
static inline string stripParens(string s){
    s = stripSpaces(s);
    while(s.size() >= 2 && s.front()=='(' && s.back()==')'){
        s = s.substr(1, s.size()-2);
        s = stripSpaces(s);
    }
    return s;
}

static inline bool isZeroConstantExpr(symbol_info* e){
    if(!e) return false;
    string s = stripParens(e->get_name());
    if(s.empty()) return false;

    if(s[0]=='+' || s[0]=='-'){
        s = stripParens(s.substr(1));
    }
    if(s=="0") return true;
    if(s.size()>=2 && s[0]=='0' && s[1]=='.'){
        for(size_t i=2;i<s.size();i++){
            if(s[i] != '0') return false;
        }
        return true;
    }
    return false;
}

static inline string get_expression_type(symbol_info* e){
    if(!e) return "undefined";
    return e->get_data_type();
}

static inline bool isFunctionSymbol(symbol_info* s){
    if(!s) return false;
    string st = s->get_symbol_type();
    return (st == "Function Definition" || st == "Function Declaration");
}

/*Error output formatting*/
static inline void emit_error(int line, const string& msg){
    outerror << "At line no: " << line << " " << msg << "\n\n";
    error_count++;
}
static inline void emit_warning(int line, const string& msg){
    // sample warning still appears in same stream; and sample total counts it
    outerror << "At line no: " << line << " " << msg << "\n\n";
    error_count++;
}

static bool pending_func_params = false;
static vector<string> pending_param_types;
static vector<string> pending_param_names;
static string current_function_return_type = "";
static int current_function_scope_id = -1;
static string current_function_name = "";

static void inject_pending_params_into_scope(){
    if(!pending_func_params) return;
    current_function_scope_id = main_table->getCurrentScopeID();
    for(size_t i=0;i<pending_param_types.size();i++){
        string ptype = pending_param_types[i];
        string pname = (i < pending_param_names.size() ? pending_param_names[i] : "");

        if(pname.empty()) continue; // allows unnamed parameter but not inserted

        symbol_info* psym = new symbol_info(pname, "ID", "Variable");
        psym->set_data_type(ptype);

        if(!main_table->insert(psym)){
            //Multiple declaration of variable a in parameter of foo2
            emit_error(lines, "Multiple declaration of variable " + pname + " in parameter of " + current_function_name);
        }
    }

    pending_func_params = false;
    pending_param_types.clear();
    pending_param_names.clear();
}

void yyerror(const char *s){
    emit_error(lines, string(s));
}
void yyerror(char *s){
    yyerror((const char*)s);
}


/* Line 371 of yacc.c  */
#line 204 "y.tab.c"

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

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     FOR = 260,
     WHILE = 261,
     DO = 262,
     BREAK = 263,
     CONTINUE = 264,
     RETURN = 265,
     INT = 266,
     FLOAT = 267,
     CHAR = 268,
     DOUBLE = 269,
     VOID = 270,
     SWITCH = 271,
     CASE = 272,
     DEFAULT = 273,
     GOTO = 274,
     PRINTF = 275,
     ADDOP = 276,
     MULOP = 277,
     INCOP = 278,
     RELOP = 279,
     ASSIGNOP = 280,
     LOGICOP = 281,
     NOT = 282,
     LPAREN = 283,
     RPAREN = 284,
     LCURL = 285,
     RCURL = 286,
     LTHIRD = 287,
     RTHIRD = 288,
     COMMA = 289,
     SEMICOLON = 290,
     COLON = 291,
     ID = 292,
     CONST_INT = 293,
     CONST_FLOAT = 294,
     LOWER_THAN_ELSE = 295
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define DO 262
#define BREAK 263
#define CONTINUE 264
#define RETURN 265
#define INT 266
#define FLOAT 267
#define CHAR 268
#define DOUBLE 269
#define VOID 270
#define SWITCH 271
#define CASE 272
#define DEFAULT 273
#define GOTO 274
#define PRINTF 275
#define ADDOP 276
#define MULOP 277
#define INCOP 278
#define RELOP 279
#define ASSIGNOP 280
#define LOGICOP 281
#define NOT 282
#define LPAREN 283
#define RPAREN 284
#define LCURL 285
#define RCURL 286
#define LTHIRD 287
#define RTHIRD 288
#define COMMA 289
#define SEMICOLON 290
#define COLON 291
#define ID 292
#define CONST_INT 293
#define CONST_FLOAT 294
#define LOWER_THAN_ELSE 295



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 350 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   211

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNRULES -- Number of states.  */
#define YYNSTATES  160

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    23,
      29,    30,    38,    39,    46,    51,    55,    58,    60,    61,
      66,    67,    71,    75,    77,    79,    81,    83,    85,    89,
      96,    98,   103,   105,   108,   110,   112,   114,   122,   128,
     136,   142,   150,   156,   161,   165,   168,   171,   175,   179,
     185,   188,   192,   195,   197,   200,   203,   205,   210,   212,
     216,   218,   222,   224,   228,   230,   234,   236,   240,   243,
     246,   248,   250,   255,   259,   261,   263,   266,   269,   271,
     272,   276
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      42,     0,    -1,    43,    -1,    43,    44,    -1,    44,    -1,
      53,    -1,    45,    -1,    46,    -1,    54,    37,    28,    49,
      29,    35,    -1,    54,    37,    28,    29,    35,    -1,    -1,
      54,    37,    28,    49,    29,    47,    50,    -1,    -1,    54,
      37,    28,    29,    48,    50,    -1,    49,    34,    54,    37,
      -1,    49,    34,    54,    -1,    54,    37,    -1,    54,    -1,
      -1,    30,    51,    56,    31,    -1,    -1,    30,    52,    31,
      -1,    54,    55,    35,    -1,    11,    -1,    12,    -1,    15,
      -1,    13,    -1,    14,    -1,    55,    34,    37,    -1,    55,
      34,    37,    32,    38,    33,    -1,    37,    -1,    37,    32,
      38,    33,    -1,    57,    -1,    56,    57,    -1,    53,    -1,
      58,    -1,    50,    -1,     5,    28,    58,    58,    60,    29,
      57,    -1,     3,    28,    60,    29,    57,    -1,     3,    28,
      60,    29,    57,     4,    57,    -1,     6,    28,    60,    29,
      57,    -1,     7,    57,     6,    28,    60,    29,    35,    -1,
      16,    28,    60,    29,    57,    -1,    17,    38,    36,    57,
      -1,    18,    36,    57,    -1,     8,    35,    -1,     9,    35,
      -1,    19,    37,    35,    -1,    37,    36,    57,    -1,    20,
      28,    37,    29,    35,    -1,    10,    35,    -1,    10,    60,
      35,    -1,     1,    35,    -1,    35,    -1,    60,    35,    -1,
       1,    35,    -1,    37,    -1,    37,    32,    60,    33,    -1,
      61,    -1,    59,    25,    61,    -1,    62,    -1,    62,    26,
      62,    -1,    63,    -1,    63,    24,    63,    -1,    64,    -1,
      63,    21,    64,    -1,    65,    -1,    64,    22,    65,    -1,
      21,    65,    -1,    27,    65,    -1,    66,    -1,    59,    -1,
      37,    28,    67,    29,    -1,    28,    60,    29,    -1,    38,
      -1,    39,    -1,    59,    23,    -1,    23,    59,    -1,    68,
      -1,    -1,    68,    34,    61,    -1,    61,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   144,   144,   151,   157,   164,   170,   176,   183,   207,
     234,   233,   267,   266,   293,   306,   319,   327,   337,   336,
     360,   359,   383,   434,   435,   436,   437,   438,   441,   447,
     453,   459,   466,   472,   479,   485,   491,   497,   503,   512,
     521,   530,   539,   545,   551,   557,   563,   569,   575,   581,
     591,   597,   603,   609,   615,   622,   629,   655,   681,   688,
     717,   724,   741,   748,   765,   772,   797,   804,   849,   856,
     869,   877,   884,   918,   925,   932,   939,   946,   954,   962,
     969,   979
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "FOR", "WHILE", "DO",
  "BREAK", "CONTINUE", "RETURN", "INT", "FLOAT", "CHAR", "DOUBLE", "VOID",
  "SWITCH", "CASE", "DEFAULT", "GOTO", "PRINTF", "ADDOP", "MULOP", "INCOP",
  "RELOP", "ASSIGNOP", "LOGICOP", "NOT", "LPAREN", "RPAREN", "LCURL",
  "RCURL", "LTHIRD", "RTHIRD", "COMMA", "SEMICOLON", "COLON", "ID",
  "CONST_INT", "CONST_FLOAT", "LOWER_THAN_ELSE", "$accept", "start",
  "program", "unit", "func_declaration", "func_definition", "$@1", "$@2",
  "parameter_list", "compound_statement", "$@3", "$@4", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement",
  "expression_statement", "variable", "expression", "logic_expression",
  "rel_expression", "simple_expression", "term", "unary_expression",
  "factor", "argument_list", "arguments", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    44,    45,    45,
      47,    46,    48,    46,    49,    49,    49,    49,    51,    50,
      52,    50,    53,    54,    54,    54,    54,    54,    55,    55,
      55,    55,    56,    56,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    58,    58,    58,    59,    59,    60,    60,
      61,    61,    62,    62,    63,    63,    64,    64,    65,    65,
      65,    66,    66,    66,    66,    66,    66,    66,    67,    67,
      68,    68
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     6,     4,     3,     2,     1,     0,     4,
       0,     3,     3,     1,     1,     1,     1,     1,     3,     6,
       1,     4,     1,     2,     1,     1,     1,     7,     5,     7,
       5,     7,     5,     4,     3,     2,     2,     3,     3,     5,
       2,     3,     2,     1,     2,     2,     1,     4,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     2,     2,
       1,     1,     4,     3,     1,     1,     2,     2,     1,     0,
       3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    23,    24,    26,    27,    25,     0,     2,     4,     6,
       7,     5,     0,     1,     3,    30,     0,     0,     0,     0,
      22,    12,     0,    17,     0,    28,     9,     0,    10,     0,
      16,    31,     0,    18,    13,     8,     0,    15,     0,     0,
       0,    11,    14,    29,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    53,    56,    74,    75,    36,    34,     0,     0,    32,
      35,    71,     0,    58,    60,    62,    64,    66,    70,    21,
      52,     0,     0,     0,     0,    45,    46,    50,    56,     0,
       0,     0,     0,     0,     0,    71,    68,    56,    77,    69,
       0,    79,     0,     0,    30,    19,    33,    76,     0,    54,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
       0,     0,    44,    47,     0,    73,    81,     0,    78,     0,
      48,    59,    61,    65,    63,    67,     0,    55,     0,     0,
       0,     0,    43,     0,    72,     0,    57,    38,     0,    40,
       0,    42,    49,    80,     0,     0,     0,    39,    37,    41
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    10,    36,    27,    22,    65,
      39,    40,    66,    67,    16,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,   127,   128
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -96
static const yytype_int16 yypact[] =
{
      88,   -96,   -96,   -96,   -96,   -96,    43,    88,   -96,   -96,
     -96,   -96,   -10,   -96,   -96,     1,   -26,    66,    14,    16,
     -96,    24,   -12,    19,    29,    28,   -96,    37,    34,    88,
     -96,   -96,    33,    41,   -96,   -96,    37,    39,    50,   146,
      56,   -96,   -96,   -96,    54,    62,    64,    69,   146,    70,
      74,    47,    76,    73,    93,    94,   104,   159,    96,   159,
     159,   -96,   -13,   -96,   -96,   -96,   -96,    99,   107,   -96,
     -96,     9,   105,   -96,   113,    27,   119,   -96,   -96,   -96,
     -96,   159,     3,   159,   137,   -96,   -96,   -96,    17,   115,
     159,   112,   146,   133,   134,   147,   -96,   140,   -96,   -96,
     148,   159,   159,   146,   143,   -96,   -96,   -96,   159,   -96,
     159,   159,   159,   159,   149,   144,     3,   160,   162,   -96,
     163,   146,   -96,   -96,   164,   -96,   -96,   165,   154,   158,
     -96,   -96,   -96,   119,   174,   -96,   146,   -96,   159,   146,
     159,   146,   -96,   166,   -96,   159,   -96,   195,   171,   -96,
     173,   -96,   -96,   -96,   146,   146,   168,   -96,   -96,   -96
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -96,   -96,   -96,   197,   -96,   -96,   -96,   -96,   -96,   -22,
     -96,   -96,    21,    18,   -96,   -96,   -48,   -80,   -47,   -44,
     -95,    95,    97,   100,   -56,   -96,   -96,   -96
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -21
static const yytype_int16 yytable[] =
{
      84,    96,   116,    99,   115,    34,   126,    89,    19,    20,
      95,    98,    95,   131,    41,   101,   100,    28,    12,   102,
     106,    11,    29,   103,    57,    12,    58,    15,    11,    17,
      59,    60,   107,    18,   108,    23,   138,   114,    61,   117,
      88,    63,    64,    13,   122,   101,   120,    37,   111,   102,
     153,   112,    24,    25,    95,   130,    30,   135,   129,    26,
      32,    95,    31,    95,    95,    95,    95,    33,    57,    35,
      58,    38,   -20,   142,    59,    60,    42,     1,     2,     3,
       4,     5,    87,    43,    88,    63,    64,    79,   147,    80,
      81,   149,    82,   151,   148,    21,   150,    83,    95,     1,
       2,     3,     4,     5,    90,    85,   157,   158,    44,    86,
      45,    91,    46,    47,    48,    49,    50,    51,     1,     2,
       3,     4,     5,    52,    53,    54,    55,    56,    57,    92,
      58,    93,    94,    97,    59,    60,   104,    33,   105,   110,
     109,   113,    61,   118,    62,    63,    64,    44,   121,    45,
     119,    46,    47,    48,    49,    50,    51,     1,     2,     3,
       4,     5,    52,    53,    54,    55,    56,    57,   123,    58,
     107,   124,   102,    59,    60,    18,    33,   125,   136,   137,
      57,    61,    58,    62,    63,    64,    59,    60,   145,   139,
     140,   146,   141,   143,   144,   111,    88,    63,    64,   154,
     155,   152,   156,   159,    14,   132,     0,     0,     0,   134,
       0,   133
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-96)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      48,    57,    82,    59,     1,    27,   101,    51,    34,    35,
      57,    58,    59,   108,    36,    28,    60,    29,     0,    32,
      68,     0,    34,    36,    21,     7,    23,    37,     7,    28,
      27,    28,    23,    32,    25,    17,   116,    81,    35,    83,
      37,    38,    39,     0,    92,    28,    90,    29,    21,    32,
     145,    24,    38,    37,   101,   103,    37,   113,   102,    35,
      32,   108,    33,   110,   111,   112,   113,    30,    21,    35,
      23,    38,    31,   121,    27,    28,    37,    11,    12,    13,
      14,    15,    35,    33,    37,    38,    39,    31,   136,    35,
      28,   139,    28,   141,   138,    29,   140,    28,   145,    11,
      12,    13,    14,    15,    28,    35,   154,   155,     1,    35,
       3,    38,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    36,
      23,    37,    28,    37,    27,    28,    37,    30,    31,    26,
      35,    22,    35,     6,    37,    38,    39,     1,    36,     3,
      35,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    35,    23,
      23,    37,    32,    27,    28,    32,    30,    29,    29,    35,
      21,    35,    23,    37,    38,    39,    27,    28,    34,    29,
      28,    33,    29,    29,    29,    21,    37,    38,    39,     4,
      29,    35,    29,    35,     7,   110,    -1,    -1,    -1,   112,
      -1,   111
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    11,    12,    13,    14,    15,    42,    43,    44,    45,
      46,    53,    54,     0,    44,    37,    55,    28,    32,    34,
      35,    29,    49,    54,    38,    37,    35,    48,    29,    34,
      37,    33,    32,    30,    50,    35,    47,    54,    38,    51,
      52,    50,    37,    33,     1,     3,     5,     6,     7,     8,
       9,    10,    16,    17,    18,    19,    20,    21,    23,    27,
      28,    35,    37,    38,    39,    50,    53,    54,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    31,
      35,    28,    28,    28,    57,    35,    35,    35,    37,    60,
      28,    38,    36,    37,    28,    59,    65,    37,    59,    65,
      60,    28,    32,    36,    37,    31,    57,    23,    25,    35,
      26,    21,    24,    22,    60,     1,    58,    60,     6,    35,
      60,    36,    57,    35,    37,    29,    61,    67,    68,    60,
      57,    61,    62,    64,    63,    65,    29,    35,    58,    29,
      28,    29,    57,    29,    29,    34,    33,    57,    60,    57,
      60,    57,    35,    61,     4,    29,    29,    57,    57,    35
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
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
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
      yychar = YYLEX;
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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 145 "21201129.y"
    {
    outlog << "At line no: " << lines << " start : program " << endl << endl;
    outlog << "Symbol Table" << endl << endl;
    main_table->print_all_scopes(outlog);
}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 152 "21201129.y"
    {
    outlog << "At line no: " << lines << " program : program unit " << endl << endl;
    outlog << (yyvsp[(1) - (2)])->get_name() + "\n" + (yyvsp[(2) - (2)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (2)])->get_name() + "\n" + (yyvsp[(2) - (2)])->get_name(), "program");
}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 158 "21201129.y"
    {
    outlog << "At line no: " << lines << " program : unit " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "program");
}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 165 "21201129.y"
    {
    outlog << "At line no: " << lines << " unit : var_declaration " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "unit");
}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 171 "21201129.y"
    {
    outlog << "At line no: " << lines << " unit : func_declaration " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "unit");
}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 177 "21201129.y"
    {
    outlog << "At line no: " << lines << " unit : func_definition " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "unit");
}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 184 "21201129.y"
    {
    outlog << "At line no: " << lines << " func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON " << endl << endl;
    outlog << (yyvsp[(1) - (6)])->get_name() << " " << (yyvsp[(2) - (6)])->get_name() << "(" << (yyvsp[(4) - (6)])->get_name() << ");" << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (6)])->get_name() + " " + (yyvsp[(2) - (6)])->get_name() + "(" + (yyvsp[(4) - (6)])->get_name() + ");", "func_decl");

    string fname = (yyvsp[(2) - (6)])->get_name();
    current_function_name = fname;
    symbol_info* existing = lookup_by_name(fname);

    if(existing){
        if(!isFunctionSymbol(existing)){
            emit_error(lines, "Multiple declaration of function " + fname);
        } else {
            if(existing->get_data_type() != (yyvsp[(1) - (6)])->get_name() || existing->get_param_types() != (yyvsp[(4) - (6)])->get_param_types()){
                emit_error(lines, "Multiple declaration of function " + fname);
            }
        }
    } else {
        symbol_info* fsym = new symbol_info(fname, "ID", "Function Declaration", (yyvsp[(4) - (6)])->get_param_types(), (yyvsp[(4) - (6)])->get_param_names());
        fsym->set_data_type((yyvsp[(1) - (6)])->get_name());
        main_table->insert(fsym);
    }
}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 208 "21201129.y"
    {
    outlog << "At line no: " << lines << " func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON " << endl << endl;
    outlog << (yyvsp[(1) - (5)])->get_name() << " " << (yyvsp[(2) - (5)])->get_name() << "();" << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (5)])->get_name() + " " + (yyvsp[(2) - (5)])->get_name() + "();", "func_decl");

    string fname = (yyvsp[(2) - (5)])->get_name();
    current_function_name = fname;
    symbol_info* existing = lookup_by_name(fname);

    if(existing){
        if(!isFunctionSymbol(existing)){
            emit_error(lines, "Multiple declaration of function " + fname);
        } else {
            if(existing->get_data_type() != (yyvsp[(1) - (5)])->get_name() || existing->get_param_types().size() != 0){
                emit_error(lines, "Multiple declaration of function " + fname);
            }
        }
    } else {
        symbol_info* fsym = new symbol_info(fname, "ID", "Function Declaration");
        fsym->set_data_type((yyvsp[(1) - (5)])->get_name());
        main_table->insert(fsym);
    }
}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 234 "21201129.y"
    {
    current_function_return_type = (yyvsp[(1) - (5)])->get_name();
    string fname = (yyvsp[(2) - (5)])->get_name();
    current_function_name = fname;
    symbol_info* existing = lookup_by_name(fname);

    if(existing){
        if(existing->get_symbol_type() == "Function Definition" || existing->get_symbol_type() == "Function Declaration"){
            emit_error(lines, "Multiple declaration of function " + fname);
        } else {
            emit_error(lines, "Multiple declaration of function " + fname);
        }
    } else {
        symbol_info* fsym = new symbol_info(fname, "ID", "Function Definition", (yyvsp[(4) - (5)])->get_param_types(), (yyvsp[(4) - (5)])->get_param_names());
        fsym->set_data_type((yyvsp[(1) - (5)])->get_name());
        if(!main_table->insert(fsym)){
            emit_error(lines, "Multiple declaration of function " + fname);
        }
    }

    pending_func_params = true;
    pending_param_types = (yyvsp[(4) - (5)])->get_param_types();
    pending_param_names = (yyvsp[(4) - (5)])->get_param_names();
}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 259 "21201129.y"
    {
    outlog << "At line no: " << lines << " func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement " << endl << endl;

    outlog << (yyvsp[(1) - (7)])->get_name() << " " << (yyvsp[(2) - (7)])->get_name() << "(" << (yyvsp[(4) - (7)])->get_name() << ")\n" << (yyvsp[(7) - (7)])->get_name() << endl << endl;

    (yyval) = new symbol_info((yyvsp[(1) - (7)])->get_name() + " " + (yyvsp[(2) - (7)])->get_name() + "(" + (yyvsp[(4) - (7)])->get_name() + ")\n" + (yyvsp[(7) - (7)])->get_name(),"func_def");
}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 267 "21201129.y"
    {
    current_function_return_type = (yyvsp[(1) - (4)])->get_name();
    string fname = (yyvsp[(2) - (4)])->get_name();
    current_function_name = fname;
    symbol_info* existing = lookup_by_name(fname);

    if(existing){
        emit_error(lines, "Multiple declaration of function " + fname);
    } else {
        symbol_info* fsym = new symbol_info(fname, "ID", "Function Definition");
        fsym->set_data_type((yyvsp[(1) - (4)])->get_name());
        if(!main_table->insert(fsym)){
            emit_error(lines, "Multiple declaration of function " + fname);
        }
    }
    pending_func_params = true;
    pending_param_types.clear();
    pending_param_names.clear();
}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 287 "21201129.y"
    {
    outlog << "At line no: " << lines << " func_definition : type_specifier ID LPAREN RPAREN compound_statement " << endl << endl;
    outlog << (yyvsp[(1) - (6)])->get_name() << " " << (yyvsp[(2) - (6)])->get_name() << "()\n" << (yyvsp[(6) - (6)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (6)])->get_name() + " " + (yyvsp[(2) - (6)])->get_name() + "()\n" + (yyvsp[(6) - (6)])->get_name(), "func_def");
}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 294 "21201129.y"
    {
    outlog << "At line no: " << lines << " parameter_list : parameter_list COMMA type_specifier ID " << endl << endl;
    outlog << (yyvsp[(1) - (4)])->get_name() << "," << (yyvsp[(3) - (4)])->get_name() << " " << (yyvsp[(4) - (4)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (4)])->get_name() + "," + (yyvsp[(3) - (4)])->get_name() + " " + (yyvsp[(4) - (4)])->get_name(), "param_list");

    vector<string> types = (yyvsp[(1) - (4)])->get_param_types();
    vector<string> names = (yyvsp[(1) - (4)])->get_param_names();
    types.push_back((yyvsp[(3) - (4)])->get_name());
    names.push_back((yyvsp[(4) - (4)])->get_name());
    (yyval)->set_param_types(types);
    (yyval)->set_param_names(names);
}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 307 "21201129.y"
    {
    outlog << "At line no: " << lines << " parameter_list : parameter_list COMMA type_specifier " << endl << endl;
    outlog << (yyvsp[(1) - (3)])->get_name() << "," << (yyvsp[(3) - (3)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name() + "," + (yyvsp[(3) - (3)])->get_name(), "param_list");

    vector<string> types = (yyvsp[(1) - (3)])->get_param_types();
    vector<string> names = (yyvsp[(1) - (3)])->get_param_names();
    types.push_back((yyvsp[(3) - (3)])->get_name());
    names.push_back("");
    (yyval)->set_param_types(types);
    (yyval)->set_param_names(names);
}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 320 "21201129.y"
    {
    outlog << "At line no: " << lines << " parameter_list : type_specifier ID " << endl << endl;
    outlog << (yyvsp[(1) - (2)])->get_name() << " " << (yyvsp[(2) - (2)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (2)])->get_name() + " " + (yyvsp[(2) - (2)])->get_name(), "param_list");
    (yyval)->set_param_types(vector<string>{ (yyvsp[(1) - (2)])->get_name() });
    (yyval)->set_param_names(vector<string>{ (yyvsp[(2) - (2)])->get_name() });
}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 328 "21201129.y"
    {
    outlog << "At line no: " << lines << " parameter_list : type_specifier " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "param_list");
    (yyval)->set_param_types(vector<string>{ (yyvsp[(1) - (1)])->get_name() });
    (yyval)->set_param_names(vector<string>{ "" });
}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 337 "21201129.y"
    {
    main_table->enter_scope();
    outlog << "New ScopeTable with ID " << main_table->getCurrentScopeID() << " created" << endl << endl;
    inject_pending_params_into_scope();
}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 343 "21201129.y"
    {
    outlog << "At line no: " << lines << " compound_statement : LCURL statements RCURL " << endl << endl;
    outlog << "{\n" + (yyvsp[(3) - (4)])->get_name() + "\n}" << endl << endl;
    (yyval) = new symbol_info("{\n" + (yyvsp[(3) - (4)])->get_name() + "\n}", "comp_stmnt");

    main_table->print_all_scopes(outlog);
    int id = main_table->getCurrentScopeID();
    main_table->exit_scope();
    outlog << "Scopetable with ID " << id << " removed" << endl << endl;

    if(id == current_function_scope_id){
        current_function_scope_id = -1;
        current_function_return_type = "";
        current_function_name = "";
    }
}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 360 "21201129.y"
    {
    main_table->enter_scope();
    outlog << "New ScopeTable with ID " << main_table->getCurrentScopeID() << " created" << endl << endl;
    inject_pending_params_into_scope();
}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 366 "21201129.y"
    {
    outlog << "At line no: " << lines << " compound_statement : LCURL RCURL " << endl << endl;
    outlog << "{\n}" << endl << endl;
    (yyval) = new symbol_info("{\n}", "compound_stmnt");

    main_table->print_all_scopes(outlog);
    int id = main_table->getCurrentScopeID();
    main_table->exit_scope();
    outlog << "Scopetable with ID " << id << " removed" << endl << endl;

    if(id == current_function_scope_id){
        current_function_scope_id = -1;
        current_function_return_type = "";
        current_function_name = "";
    }
}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 384 "21201129.y"
    {
    outlog << "At line no: " << lines << " var_declaration : type_specifier declaration_list SEMICOLON " << endl << endl;
    outlog << (yyvsp[(1) - (3)])->get_name() << " " << (yyvsp[(2) - (3)])->get_name() << ";" << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name() + " " + (yyvsp[(2) - (3)])->get_name() + ";", "var_dec");

    string data_type = (yyvsp[(1) - (3)])->get_name();
    if(data_type == "void"){
        emit_error(lines, "variable type can not be void");
        data_type = "undefined";
    }

    vector<string> vars;
    {
        string s = (yyvsp[(2) - (3)])->get_name();
        string token;
        stringstream ss(s);
        while(getline(ss, token, ',')) vars.push_back(stripSpaces(token));
    }

    for(const string& var : vars){
        if(var.empty()) continue;

        size_t openb = var.find('[');
        size_t closeb = var.find(']');

        if(openb != string::npos && closeb != string::npos && closeb > openb + 1){
            string array_name = var.substr(0, openb);
            string size_str = var.substr(openb + 1, closeb - openb - 1);

            int array_size = 0;
            try { array_size = stoi(size_str); } catch(...) { array_size = 0; }

            symbol_info* sym = new symbol_info(array_name, "ID", "Array");
            sym->set_array_size(array_size);
            sym->set_data_type(data_type);

            if(!main_table->insert(sym)){
                emit_error(lines, "Multiple declaration of variable " + array_name);
            }
        } else {
            symbol_info* sym = new symbol_info(var, "ID", "Variable");
            sym->set_data_type(data_type);

            if(!main_table->insert(sym)){
                emit_error(lines, "Multiple declaration of variable " + var);
            }
        }
    }
}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 434 "21201129.y"
    { outlog << "At line no:" << lines << " type_specifier : INT " << endl << endl;   outlog << "int" << endl << endl;   (yyval) = new symbol_info("int","type"); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 435 "21201129.y"
    { outlog << "At line no:" << lines << " type_specifier : FLOAT " << endl << endl; outlog << "float" << endl << endl; (yyval) = new symbol_info("float","type"); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 436 "21201129.y"
    { outlog << "At line no:" << lines << " type_specifier : VOID " << endl << endl;  outlog << "void" << endl << endl;  (yyval) = new symbol_info("void","type"); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 437 "21201129.y"
    { outlog << "At line no:" << lines << " type_specifier : CHAR " << endl << endl;  outlog << "char" << endl << endl;  (yyval) = new symbol_info("char","type"); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 438 "21201129.y"
    { outlog << "At line no:" << lines << " type_specifier : DOUBLE " << endl << endl;outlog << "double" << endl << endl;(yyval) = new symbol_info("double","type"); 
}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 442 "21201129.y"
    {
    outlog << "At line no: " << lines << " declaration_list : declaration_list COMMA ID " << endl << endl;
    outlog << (yyvsp[(1) - (3)])->get_name() << "," << (yyvsp[(3) - (3)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name() + "," + (yyvsp[(3) - (3)])->get_name(), "declaration_list");
}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 448 "21201129.y"
    {
    outlog << "At line no: " << lines << " declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD " << endl << endl;
    outlog << (yyvsp[(1) - (6)])->get_name() << "," << (yyvsp[(3) - (6)])->get_name() << "[" << (yyvsp[(5) - (6)])->get_name() << "]" << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (6)])->get_name() + "," + (yyvsp[(3) - (6)])->get_name() + "[" + (yyvsp[(5) - (6)])->get_name() + "]", "declaration_list");
}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 454 "21201129.y"
    {
    outlog << "At line no: " << lines << " declaration_list : ID " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "declaration_list");
}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 460 "21201129.y"
    {
    outlog << "At line no: " << lines << " declaration_list : ID LTHIRD CONST_INT RTHIRD " << endl << endl;
    outlog << (yyvsp[(1) - (4)])->get_name() << "[" << (yyvsp[(3) - (4)])->get_name() << "]" << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (4)])->get_name() + "[" + (yyvsp[(3) - (4)])->get_name() + "]", "declaration_list");
}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 467 "21201129.y"
    {
    outlog << "At line no: " << lines << " statements : statement " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "stmnts");
}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 473 "21201129.y"
    {
    outlog << "At line no: " << lines << " statements : statements statement " << endl << endl;
    outlog << (yyvsp[(1) - (2)])->get_name() << "\n" << (yyvsp[(2) - (2)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (2)])->get_name() + "\n" + (yyvsp[(2) - (2)])->get_name(), "stmnts");
}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 480 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : var_declaration " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "stmnt");
}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 486 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : expression_statement " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "stmnt");
}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 492 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : compound_statement " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "stmnt");
}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 498 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement " << endl << endl;
    outlog << "for(" << (yyvsp[(3) - (7)])->get_name() << (yyvsp[(4) - (7)])->get_name() << (yyvsp[(5) - (7)])->get_name() << ")\n" << (yyvsp[(7) - (7)])->get_name() << endl << endl;
    (yyval) = new symbol_info("for(" + (yyvsp[(3) - (7)])->get_name() + (yyvsp[(4) - (7)])->get_name() + (yyvsp[(5) - (7)])->get_name() + ")\n" + (yyvsp[(7) - (7)])->get_name(), "stmnt");
}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 504 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : IF LPAREN expression RPAREN statement " << endl << endl;
    outlog << "if(" << (yyvsp[(3) - (5)])->get_name() << ")\n" << (yyvsp[(5) - (5)])->get_name() << endl << endl;
    (yyval) = new symbol_info("if(" + (yyvsp[(3) - (5)])->get_name() + ")\n" + (yyvsp[(5) - (5)])->get_name(), "stmnt");
    if(isVoidType(get_expression_type((yyvsp[(3) - (5)])))){
        emit_error(lines, "operation on void type");
    }
}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 513 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : IF LPAREN expression RPAREN statement ELSE statement " << endl << endl;
    outlog << "if(" << (yyvsp[(3) - (7)])->get_name() << ")\n" << (yyvsp[(5) - (7)])->get_name() << "\nelse\n" << (yyvsp[(7) - (7)])->get_name() << endl << endl;
    (yyval) = new symbol_info("if(" + (yyvsp[(3) - (7)])->get_name() + ")\n" + (yyvsp[(5) - (7)])->get_name() + "\nelse\n" + (yyvsp[(7) - (7)])->get_name(), "stmnt");
    if(isVoidType(get_expression_type((yyvsp[(3) - (7)])))){
        emit_error(lines, "operation on void type");
    }
}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 522 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : WHILE LPAREN expression RPAREN statement " << endl << endl;
    outlog << "while(" << (yyvsp[(3) - (5)])->get_name() << ")\n" << (yyvsp[(5) - (5)])->get_name() << endl << endl;
    (yyval) = new symbol_info("while(" + (yyvsp[(3) - (5)])->get_name() + ")\n" + (yyvsp[(5) - (5)])->get_name(), "stmnt");
    if(isVoidType(get_expression_type((yyvsp[(3) - (5)])))){
        emit_error(lines, "operation on void type");
    }
}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 531 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : DO statement WHILE LPAREN expression RPAREN SEMICOLON " << endl << endl;
    outlog << "do\n" << (yyvsp[(2) - (7)])->get_name() << "\nwhile(" << (yyvsp[(5) - (7)])->get_name() << ");" << endl << endl;
    (yyval) = new symbol_info("do\n" + (yyvsp[(2) - (7)])->get_name() + "\nwhile(" + (yyvsp[(5) - (7)])->get_name() + ");", "stmnt");
    if(isVoidType(get_expression_type((yyvsp[(5) - (7)])))){
        emit_error(lines, "operation on void type");
    }
}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 540 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : SWITCH LPAREN expression RPAREN statement " << endl << endl;
    outlog << "switch(" << (yyvsp[(3) - (5)])->get_name() << ")\n" << (yyvsp[(5) - (5)])->get_name() << endl << endl;
    (yyval) = new symbol_info("switch(" + (yyvsp[(3) - (5)])->get_name() + ")\n" + (yyvsp[(5) - (5)])->get_name(), "stmnt");
}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 546 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : CASE CONST_INT COLON statement " << endl << endl;
    outlog << "case " << (yyvsp[(2) - (4)])->get_name() << ":\n" << (yyvsp[(4) - (4)])->get_name() << endl << endl;
    (yyval) = new symbol_info("case " + (yyvsp[(2) - (4)])->get_name() + ":\n" + (yyvsp[(4) - (4)])->get_name(), "stmnt");
}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 552 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : DEFAULT COLON statement " << endl << endl;
    outlog << "default:\n" << (yyvsp[(3) - (3)])->get_name() << endl << endl;
    (yyval) = new symbol_info("default:\n" + (yyvsp[(3) - (3)])->get_name(), "stmnt");
}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 558 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : BREAK SEMICOLON " << endl << endl;
    outlog << "break;" << endl << endl;
    (yyval) = new symbol_info("break;", "stmnt");
}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 564 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : CONTINUE SEMICOLON " << endl << endl;
    outlog << "continue;" << endl << endl;
    (yyval) = new symbol_info("continue;", "stmnt");
}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 570 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : GOTO ID SEMICOLON " << endl << endl;
    outlog << "goto " << (yyvsp[(2) - (3)])->get_name() << ";" << endl << endl;
    (yyval) = new symbol_info("goto " + (yyvsp[(2) - (3)])->get_name() + ";", "stmnt");
}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 576 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : ID COLON statement " << endl << endl;
    outlog << (yyvsp[(1) - (3)])->get_name() << ":\n" << (yyvsp[(3) - (3)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name() + ":\n" + (yyvsp[(3) - (3)])->get_name(), "stmnt");
}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 582 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : PRINTF LPAREN ID RPAREN SEMICOLON " << endl << endl;
    outlog << "printf(" << (yyvsp[(3) - (5)])->get_name() << ");" << endl << endl;
    (yyval) = new symbol_info("printf(" + (yyvsp[(3) - (5)])->get_name() + ");", "stmnt");
    symbol_info* s = lookup_by_name((yyvsp[(3) - (5)])->get_name());
    if(!s){
        emit_error(lines, "Undeclared variable " + (yyvsp[(3) - (5)])->get_name());
    }
}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 592 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : RETURN SEMICOLON " << endl << endl;
    outlog << "return;" << endl << endl;
    (yyval) = new symbol_info("return;", "stmnt");
}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 598 "21201129.y"
    {
    outlog << "At line no: " << lines << " statement : RETURN expression SEMICOLON " << endl << endl;
    outlog << "return " << (yyvsp[(2) - (3)])->get_name() << ";" << endl << endl;
    (yyval) = new symbol_info("return " + (yyvsp[(2) - (3)])->get_name() + ";", "stmnt");
}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 604 "21201129.y"
    {
    yyerrok;
    (yyval) = new symbol_info(";", "stmnt");
}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 610 "21201129.y"
    {
    outlog << "At line no: " << lines << " expression_statement : SEMICOLON " << endl << endl;
    outlog << ";" << endl << endl;
    (yyval) = new symbol_info(";", "expr_stmt");
}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 616 "21201129.y"
    {
    outlog << "At line no: " << lines << " expression_statement : expression SEMICOLON " << endl << endl;
    outlog << (yyvsp[(1) - (2)])->get_name() << ";" << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (2)])->get_name() + ";", "expr_stmt");
    (yyval)->set_data_type(get_expression_type((yyvsp[(1) - (2)])));
}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 623 "21201129.y"
    {
    yyerrok;
    (yyval) = new symbol_info(";", "expr_stmt");
    (yyval)->set_data_type("undefined");
}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 630 "21201129.y"
    {
    outlog << "At line no: " << lines << " variable : ID " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    symbol_info* sym = lookup_by_name((yyvsp[(1) - (1)])->get_name());

    if(!sym){
        emit_error(lines, "Undeclared variable " + (yyvsp[(1) - (1)])->get_name());
        (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "var");
        (yyval)->set_data_type("undefined");
    }
    else if(sym->get_symbol_type() == "Array"){
        emit_error(lines, "variable is of array type : " + (yyvsp[(1) - (1)])->get_name());
        (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "var");
        (yyval)->set_data_type(sym->get_data_type());
    }
    else if(isFunctionSymbol(sym)){
        emit_error(lines, "Undeclared variable " + (yyvsp[(1) - (1)])->get_name());
        (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "var");
        (yyval)->set_data_type("undefined");
    }
    else{
        (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "var");
        (yyval)->set_data_type(sym->get_data_type());
    }
}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 656 "21201129.y"
    {
    outlog << "At line no: " << lines << " variable : ID LTHIRD expression RTHIRD " << endl << endl;
    outlog << (yyvsp[(1) - (4)])->get_name() << "[" << (yyvsp[(3) - (4)])->get_name() << "]" << endl << endl;
    symbol_info* sym = lookup_by_name((yyvsp[(1) - (4)])->get_name());

    if(!sym){
        emit_error(lines, "Undeclared variable " + (yyvsp[(1) - (4)])->get_name());
        (yyval) = new symbol_info((yyvsp[(1) - (4)])->get_name() + "[" + (yyvsp[(3) - (4)])->get_name() + "]", "var");
        (yyval)->set_data_type("undefined");
    }
    else if(sym->get_symbol_type() != "Array"){
        emit_error(lines, "variable is not of array type : " + (yyvsp[(1) - (4)])->get_name());
        (yyval) = new symbol_info((yyvsp[(1) - (4)])->get_name() + "[" + (yyvsp[(3) - (4)])->get_name() + "]", "var");
        (yyval)->set_data_type(sym->get_data_type());
    }
    else{
        string idx_t = get_expression_type((yyvsp[(3) - (4)]));
        if(!isUndefinedType(idx_t) && idx_t != "int"){
            emit_error(lines, "array index is not of integer type : " + (yyvsp[(1) - (4)])->get_name());
        }
        (yyval) = new symbol_info((yyvsp[(1) - (4)])->get_name() + "[" + (yyvsp[(3) - (4)])->get_name() + "]", "var");
        (yyval)->set_data_type(sym->get_data_type());
    }
}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 682 "21201129.y"
    {
    outlog << "At line no: " << lines << " expression : logic_expression " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "expr");
    (yyval)->set_data_type(get_expression_type((yyvsp[(1) - (1)])));
}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 689 "21201129.y"
    {
    outlog << "At line no: " << lines << " expression : variable ASSIGNOP logic_expression " << endl << endl;
    outlog << (yyvsp[(1) - (3)])->get_name() << "=" << (yyvsp[(3) - (3)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name() + "=" + (yyvsp[(3) - (3)])->get_name(), "expr");

    string lhs = get_expression_type((yyvsp[(1) - (3)]));
    string rhs = get_expression_type((yyvsp[(3) - (3)]));

    if(isUndefinedType(lhs) || isUndefinedType(rhs)){
        (yyval)->set_data_type("undefined");
    }
    else if(isVoidType(rhs)){
        emit_error(lines, "operation on void type");
        (yyval)->set_data_type("undefined");
    }
    else if(lhs == "int" && rhs == "float"){
        emit_warning(lines, "Warning: Assignment of float value into variable of integer type");
        (yyval)->set_data_type("int");
    }
    else if(lhs != rhs && !(lhs=="float" && rhs=="int")){
        emit_error(lines, "Type mismatch in assignment");
        (yyval)->set_data_type(lhs);
    }
    else{
        (yyval)->set_data_type(lhs);
    }
}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 718 "21201129.y"
    {
    outlog << "At line no: " << lines << " logic_expression : rel_expression " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "logic_expr");
    (yyval)->set_data_type(get_expression_type((yyvsp[(1) - (1)])));
}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 725 "21201129.y"
    {
    outlog << "At line no: " << lines << " logic_expression : rel_expression LOGICOP rel_expression " << endl << endl;
    outlog << (yyvsp[(1) - (3)])->get_name() << (yyvsp[(2) - (3)])->get_name() << (yyvsp[(3) - (3)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name() + (yyvsp[(2) - (3)])->get_name() + (yyvsp[(3) - (3)])->get_name(), "logic_expr");

    string t1 = get_expression_type((yyvsp[(1) - (3)]));
    string t2 = get_expression_type((yyvsp[(3) - (3)]));

    if(isVoidType(t1) || isVoidType(t2)){
        emit_error(lines, "operation on void type");
        (yyval)->set_data_type("undefined");
    } else {
        (yyval)->set_data_type("int");
    }
}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 742 "21201129.y"
    {
    outlog << "At line no: " << lines << " rel_expression : simple_expression " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "rel_expr");
    (yyval)->set_data_type(get_expression_type((yyvsp[(1) - (1)])));
}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 749 "21201129.y"
    {
    outlog << "At line no: " << lines << " rel_expression : simple_expression RELOP simple_expression " << endl << endl;
    outlog << (yyvsp[(1) - (3)])->get_name() << (yyvsp[(2) - (3)])->get_name() << (yyvsp[(3) - (3)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name() + (yyvsp[(2) - (3)])->get_name() + (yyvsp[(3) - (3)])->get_name(), "rel_expr");

    string t1 = get_expression_type((yyvsp[(1) - (3)]));
    string t2 = get_expression_type((yyvsp[(3) - (3)]));

    if(isVoidType(t1) || isVoidType(t2)){
        emit_error(lines, "operation on void type");
        (yyval)->set_data_type("undefined");
    } else {
        (yyval)->set_data_type("int");
    }
}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 766 "21201129.y"
    {
    outlog << "At line no: " << lines << " simple_expression : term " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "simp_expr");
    (yyval)->set_data_type(get_expression_type((yyvsp[(1) - (1)])));
}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 773 "21201129.y"
    {
    outlog << "At line no: " << lines << " simple_expression : simple_expression ADDOP term " << endl << endl;
    outlog << (yyvsp[(1) - (3)])->get_name() << (yyvsp[(2) - (3)])->get_name() << (yyvsp[(3) - (3)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name() + (yyvsp[(2) - (3)])->get_name() + (yyvsp[(3) - (3)])->get_name(), "simp_expr");

    string t1 = get_expression_type((yyvsp[(1) - (3)]));
    string t2 = get_expression_type((yyvsp[(3) - (3)]));

    if(isUndefinedType(t1) || isUndefinedType(t2)){
        (yyval)->set_data_type("undefined");
    }
    else if(isVoidType(t1) || isVoidType(t2)){
        emit_error(lines, "operation on void type");
        (yyval)->set_data_type("undefined");
    }
    else if(!isNumericType(t1) || !isNumericType(t2)){
        emit_error(lines, "Non-numeric operand used in arithmetic operation");
        (yyval)->set_data_type("undefined");
    }
    else{
        (yyval)->set_data_type(promoteNumeric(t1, t2));
    }
}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 798 "21201129.y"
    {
    outlog << "At line no: " << lines << " term : unary_expression " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "term");
    (yyval)->set_data_type(get_expression_type((yyvsp[(1) - (1)])));
}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 805 "21201129.y"
    {
    outlog << "At line no: " << lines << " term : term MULOP unary_expression " << endl << endl;
    outlog << (yyvsp[(1) - (3)])->get_name() << (yyvsp[(2) - (3)])->get_name() << (yyvsp[(3) - (3)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name() + (yyvsp[(2) - (3)])->get_name() + (yyvsp[(3) - (3)])->get_name(), "term");

    string t1 = get_expression_type((yyvsp[(1) - (3)]));
    string t2 = get_expression_type((yyvsp[(3) - (3)]));
    string op = (yyvsp[(2) - (3)])->get_name();

    if(isUndefinedType(t1) || isUndefinedType(t2)){
        (yyval)->set_data_type("undefined");
    }
    else if(isVoidType(t1) || isVoidType(t2)){
        emit_error(lines, "operation on void type");
        (yyval)->set_data_type("undefined");
    }
    else if(!isNumericType(t1) || !isNumericType(t2)){
        emit_error(lines, "Non-numeric operand used in arithmetic operation");
        (yyval)->set_data_type("undefined");
    }
    else{
        if(op == "%"){
            if(t1 != "int" || t2 != "int"){
                emit_error(lines, "Modulus operator on non integer type");
                (yyval)->set_data_type("undefined");
            } else {
                if(isZeroConstantExpr((yyvsp[(3) - (3)]))){
                    emit_error(lines, "Modulus by 0");
                }
                (yyval)->set_data_type("int");
            }
        }
        else if(op == "/"){
            if(isZeroConstantExpr((yyvsp[(3) - (3)]))){
                emit_error(lines, "Division by 0");
            }
            (yyval)->set_data_type(promoteNumeric(t1, t2));
        }
        else{
            (yyval)->set_data_type(promoteNumeric(t1, t2));
        }
    }
}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 850 "21201129.y"
    {
    outlog << "At line no: " << lines << " unary_expression : ADDOP unary_expression " << endl << endl;
    outlog << (yyvsp[(1) - (2)])->get_name() << (yyvsp[(2) - (2)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (2)])->get_name() + (yyvsp[(2) - (2)])->get_name(), "un_expr");
    (yyval)->set_data_type(get_expression_type((yyvsp[(2) - (2)])));
}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 857 "21201129.y"
    {
    outlog << "At line no: " << lines << " unary_expression : NOT unary_expression " << endl << endl;
    outlog << "!" << (yyvsp[(2) - (2)])->get_name() << endl << endl;
    (yyval) = new symbol_info("!" + (yyvsp[(2) - (2)])->get_name(), "un_expr");

    if(isVoidType(get_expression_type((yyvsp[(2) - (2)])))){
        emit_error(lines, "operation on void type");
        (yyval)->set_data_type("undefined");
    } else {
        (yyval)->set_data_type("int");
    }
}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 870 "21201129.y"
    {
    outlog << "At line no: " << lines << " unary_expression : factor " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "un_expr");
    (yyval)->set_data_type(get_expression_type((yyvsp[(1) - (1)])));
}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 878 "21201129.y"
    {
    outlog << "At line no: " << lines << " factor : variable " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "factor");
    (yyval)->set_data_type(get_expression_type((yyvsp[(1) - (1)])));
}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 885 "21201129.y"
    {
    outlog << "At line no: " << lines << " factor : ID LPAREN argument_list RPAREN " << endl << endl;
    outlog << (yyvsp[(1) - (4)])->get_name() << "(" << (yyvsp[(3) - (4)])->get_name() << ")" << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (4)])->get_name() + "(" + (yyvsp[(3) - (4)])->get_name() + ")", "factor");

    symbol_info* sym = lookup_by_name((yyvsp[(1) - (4)])->get_name());
    if(!sym){
        emit_error(lines, "Undeclared function: " + (yyvsp[(1) - (4)])->get_name());
        (yyval)->set_data_type("undefined");
    }
    else if(!isFunctionSymbol(sym)){
        emit_error(lines, "Undeclared function: " + (yyvsp[(1) - (4)])->get_name());
        (yyval)->set_data_type("undefined");
    }
    else {
        vector<string> param_types = sym->get_param_types();
        vector<string> arg_types   = (yyvsp[(3) - (4)])->get_param_types();

        if(param_types.size() != arg_types.size()){
            emit_error(lines, "Inconsistencies in number of arguments in function call: " + (yyvsp[(1) - (4)])->get_name());
        } else {
            for(size_t i=0;i<param_types.size();i++){
                string p = param_types[i];
                string a = arg_types[i];
                if(isUndefinedType(a)) continue;
                if(p == a) continue;
                if(p == "float" && a == "int") continue;
                emit_error(lines, "argument " + to_string((int)i+1) + " type mismatch in function call: " + (yyvsp[(1) - (4)])->get_name());
            }
        }
        (yyval)->set_data_type(sym->get_data_type());
    }
}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 919 "21201129.y"
    {
    outlog << "At line no: " << lines << " factor : LPAREN expression RPAREN " << endl << endl;
    outlog << "(" << (yyvsp[(2) - (3)])->get_name() << ")" << endl << endl;
    (yyval) = new symbol_info("(" + (yyvsp[(2) - (3)])->get_name() + ")", "factor");
    (yyval)->set_data_type(get_expression_type((yyvsp[(2) - (3)])));
}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 926 "21201129.y"
    {
    outlog << "At line no: " << lines << " factor : CONST_INT " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "factor");
    (yyval)->set_data_type("int");
}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 933 "21201129.y"
    {
    outlog << "At line no: " << lines << " factor : CONST_FLOAT " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "factor");
    (yyval)->set_data_type("float");
}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 940 "21201129.y"
    {
    outlog << "At line no: " << lines << " factor : variable INCOP " << endl << endl;
    outlog << (yyvsp[(1) - (2)])->get_name() << "++" << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (2)])->get_name() + "++", "factor");
    (yyval)->set_data_type(get_expression_type((yyvsp[(1) - (2)])));
}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 947 "21201129.y"
    {
    outlog << "At line no: " << lines << " factor : INCOP variable " << endl << endl;
    outlog << "++" << (yyvsp[(2) - (2)])->get_name() << endl << endl;
    (yyval) = new symbol_info("++" + (yyvsp[(2) - (2)])->get_name(), "factor");
    (yyval)->set_data_type(get_expression_type((yyvsp[(2) - (2)])));
}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 955 "21201129.y"
    {
    outlog << "At line no: " << lines << " argument_list : arguments " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "arg_list");
    (yyval)->set_param_types((yyvsp[(1) - (1)])->get_param_types());
}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 962 "21201129.y"
    {
    outlog << "At line no: " << lines << " argument_list : " << endl << endl;
    (yyval) = new symbol_info("", "arg_list");
    (yyval)->set_param_types(vector<string>());
}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 970 "21201129.y"
    {
    outlog << "At line no: " << lines << " arguments : arguments COMMA logic_expression " << endl << endl;
    outlog << (yyvsp[(1) - (3)])->get_name() << ", " << (yyvsp[(3) - (3)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name() + ", " + (yyvsp[(3) - (3)])->get_name(), "args");

    vector<string> types = (yyvsp[(1) - (3)])->get_param_types();
    types.push_back(get_expression_type((yyvsp[(3) - (3)])));
    (yyval)->set_param_types(types);
}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 980 "21201129.y"
    {
    outlog << "At line no: " << lines << " arguments : logic_expression " << endl << endl;
    outlog << (yyvsp[(1) - (1)])->get_name() << endl << endl;
    (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(), "args");
    (yyval)->set_param_types(vector<string>{ get_expression_type((yyvsp[(1) - (1)])) });
}
    break;


/* Line 1792 of yacc.c  */
#line 2836 "y.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 987 "21201129.y"


int main(int argc, char *argv[])
{
    if(argc != 2){
        cout << "Please input file name" << endl;
        return 0;
    }

    yyin = fopen(argv[1], "r");

    outlog.open("21201129_log.txt", ios::trunc);
    outerror.open("21201129_error.txt", ios::trunc);

    if(yyin == NULL){
        cout << "Couldn't open file" << endl;
        return 0;
    }

    main_table = new symbol_table(10);
    outlog << "New ScopeTable with ID " << main_table->getCurrentScopeID() << " created" << endl << endl;

    yyparse();

    outlog << endl << "Total lines: " << lines << endl;
    outlog << "Total errors: " << error_count << endl;
    outerror << "Total errors: " << error_count << endl;

    outlog.close();
    outerror.close();
    fclose(yyin);
    return 0;
}