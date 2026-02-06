%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYDEBUG 1

int yylex(void);
void yyerror(const char *s);
extern FILE *yyin;

/* production tracing */
static int prodCount = 0;
static int prodIdx[10000];

static void used(int idx) {
    if (prodCount < (int)(sizeof(prodIdx)/sizeof(prodIdx[0])) - 1) {
        prodIdx[++prodCount] = idx; /* 1-based position */
    }
}
%}

/* ===== Tokens (must match your Flex/lex file in Lab6) ===== */
%token VAR BEGIN_T END_T
%token IF THEN ELSE WHILE DO
%token READ WRITE
%token ARRAY OF
%token BOOLEAN CHAR_T INTEGER REAL
%token AND OR NOT

%token IDENTIFIER INTCONST

/* multi-char operators */
%token ASSIGN        /* := */
%token LE GE NEQ     /* <=  >=  <> */
%token LT GT EQ      /* <   >   =  */

/* ===== Precedence (avoid conflicts in expressions/conditions) ===== */
%left OR
%left AND
%right NOT

%left '+' '-'
%left '*' '/'
%nonassoc LT LE EQ NEQ GE GT

%start program

%%

program
  : VAR declList cmpdStmt '.'
        { used(0); }
  ;

declList
  : declaration declListTail
         { used(1); }
  ;

declListTail
  : ';' declaration declListTail
        { used(2); }
  | /* empty */
  ;

declaration
  : IDENTIFIER ':' type
      { used(3); }
  ;

type
  : type1
      { used(4); }
  | arrayDecl
      { used(5); }
  ;

type1
  : BOOLEAN
      { used(6); }
  | CHAR_T
      { used(7); }
  | INTEGER
      { used(8); }
  | REAL
      { used(9); }
  ;

arrayDecl
  : ARRAY '[' INTCONST ']' OF type1
      { used(10); }
  ;

cmpdStmt
  : BEGIN_T stmtList END_T
      { used(11); }
  ;

stmtList
  : stmt
      { used(12); }
  | stmt ';' stmtList
      { used(13); }
  ;

stmt
  : simpleStmt
      { used(14); }
  | matchedStmt
      { used(15); }
  | unmatchedStmt
      { used(16); }
  ;

simpleStmt
  : assignStmt
      { used(16); }
  | ioStmt
      { used(17); }
  ;

assignStmt
  : IDENTIFIER ASSIGN expression
      { used(18); }
  ;

ioStmt
  : READ '(' IDENTIFIER ')'
      { used(19); }
  | WRITE '(' IDENTIFIER ')'
      { used(20); }
  ;

matchedStmt
  : cmpdStmt
      { used(21); }
  | WHILE condition DO matchedStmt
      { used(22); }
  | IF condition THEN matchedStmt ELSE matchedStmt
      { used(23); }
  ;

unmatchedStmt
  : IF condition THEN stmt
      { used(24); }
  | IF condition THEN matchedStmt ELSE unmatchedStmt
      { used(25); }
  | WHILE condition DO unmatchedStmt
      { used(26); }
  ;

/* Expression grammar (classic precedence) */
expression
  : expression '+' term
      { used(28); }
  | expression '-' term
      { used(29); }
  | term
      { used(30); }
  ;

term
  : term '*' factor
      { used(31); }
  | term '/' factor
      { used(32); }
  | factor
      { used(33); }
  ;

factor
  : '(' expression ')'
      { used(34); }
  | IDENTIFIER
      { used(35); }
  | INTCONST
      { used(36); }
  ;

/* Condition grammar */
condition
  : condition AND condition
      { used(37); }
  | condition OR condition
      { used(38); }
  | NOT condition
      { used(39); }
  | '(' expression relation expression ')'
      { used(40); }
  ;

relation
  : LT   { used(41); }
  | LE   { used(42); }
  | EQ   { used(43); }
  | NEQ  { used(44); }
  | GE   { used(45); }
  | GT   { used(46); }
  ;

%%

void yyerror(const char *s)
{
    /* "position (production) of the error" -> we print the last successfully used production index. */
    int last = (prodCount >= 1 ? prodIdx[prodCount] : -1);
    fprintf(stderr, "Error at production: %d\n", last);
}

int main(int argc, char **argv)
{
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("fopen");
            return 1;
        }
    }

    /* Optional: enable debug with -d */
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            yydebug = 1;
        }
    }

    int res = yyparse();
    if (res == 0) {
        printf("Program syntactic correct\n");
        for (int i = 1; i <= prodCount; i++) {
            printf("%d ", prodIdx[i]);
        }
        printf("\n");
        return 0;
    }
    return 1;
}
