%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROD 1000
int productions = 0;
int indexes[MAX_PROD];

extern int yylex(void);
void yyerror(const char *s);
extern FILE *yyin;

#define YYDEBUG 1
%}

// FIX 1: Rename BEGIN to BEGIN_STMT to avoid macro conflict
%token VAR BEGIN_STMT END ARRAY OF BOOLEAN CHAR INTEGER REAL IF THEN ELSE WHILE DO READ WRITE
%token IDENTIFIER
%token NR
%token CHARCONST
%token STRINGCONST

%token ASSIGN_OP       
%token LE_OP           
%token NE_OP           
%token GE_OP           


%nonassoc '<' LE_OP '=' NE_OP GE_OP '>'
%left '+'
%left '*'
%right ASSIGN_OP

%%

// This rule keeps the semicolon and causes the 'decllist' warning, but the file compiles.
program : VAR decllist ';' cmpdstmt '.' 
        { productions++; indexes[productions] = 0; }
;

decllist : declaration
         { productions++; indexes[productions] = 1; }
       | declaration ';' decllist
         { productions++; indexes[productions] = 2; }
;

declaration : IDENTIFIER ':' type
            { productions++; indexes[productions] = 3; }
;

type : type1
     { productions++; indexes[productions] = 4; }
   | arraydecl
     { productions++; indexes[productions] = 5; }
;

type1 : BOOLEAN
      { productions++; indexes[productions] = 6; }
    | CHAR
      { productions++; indexes[productions] = 7; }
    | INTEGER
      { productions++; indexes[productions] = 8; }
    | REAL
      { productions++; indexes[productions] = 9; }
;

arraydecl : ARRAY '[' NR ']' OF type1
          { productions++; indexes[productions] = 10; }
;

// FIX 2: Uses BEGIN_STMT
cmpdstmt : BEGIN_STMT stmtlist END
         { productions++; indexes[productions] = 11; }
;

stmtlist : stmt
         { productions++; indexes[productions] = 12; }
       | stmt ';' stmtlist
         { productions++; indexes[productions] = 13; }
;

stmt : simplstmt
     { productions++; indexes[productions] = 14; }
   | structstmt
     { productions++; indexes[productions] = 15; }
;

simplstmt : assignstmt
          { productions++; indexes[productions] = 16; }
        | iostmt
          { productions++; indexes[productions] = 17; }
;

assignstmt : IDENTIFIER ASSIGN_OP expression
           { productions++; indexes[productions] = 18; }
;

expression : term exprprime
           { productions++; indexes[productions] = 19; }
;

exprprime : '+' term exprprime
          { productions++; indexes[productions] = 20; }
          | /* empty */
          { productions++; indexes[productions] = 21; }
;

term : factor termprime
     { productions++; indexes[productions] = 22; }
;

termprime : '*' factor termprime
          { productions++; indexes[productions] = 23; }
          | /* empty */
          { productions++; indexes[productions] = 24; }
;

factor : '(' expression ')'
       { productions++; indexes[productions] = 25; }
     | IDENTIFIER
       { productions++; indexes[productions] = 26; }
     | NR
       { productions++; indexes[productions] = 27; }
     | CHARCONST
       { productions++; indexes[productions] = 28; }
     | STRINGCONST
       { productions++; indexes[productions] = 29; }
;

iostmt : READ
       { productions++; indexes[productions] = 30; }
     | WRITE '(' IDENTIFIER ')'
       { productions++; indexes[productions] = 31; }
;

structstmt : cmpdstmt
           { productions++; indexes[productions] = 32; }
         | ifstmt
           { productions++; indexes[productions] = 33; }
         | whilestmt
           { productions++; indexes[productions] = 34; }
;

ifstmt : IF condition THEN stmt
       { productions++; indexes[productions] = 35; }
     | IF condition THEN stmt ELSE stmt
       { productions++; indexes[productions] = 36; }
;

whilestmt : WHILE condition DO stmt
          { productions++; indexes[productions] = 37; }
;

condition : expression RELATION expression
          { productions++; indexes[productions] = 38; }
;

RELATION : '<'
         { productions++; indexes[productions] = 39; }
       | LE_OP
         { productions++; indexes[productions] = 40; }
       | '='
         { productions++; indexes[productions] = 41; }
       | NE_OP
         { productions++; indexes[productions] = 42; }
       | GE_OP
         { productions++; indexes[productions] = 43; }
       | '>'
         { productions++; indexes[productions] = 44; }
;

%%

void yyerror(const char *s)
{
    printf("Error after %d productions, at production: %d\n", productions, indexes[productions]);
}

int main(int argc, char **argv)
{
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            fprintf(stderr, "Could not open file %s\n", argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
    }

    if ((argc > 2) && (!strcmp(argv[2], "-d"))) {
        yydebug = 1;
    }

    if (!yyparse()) {
        fprintf(stderr, "\tProgram syntactic correct, %d productions used\n", productions);
        for (int i = 1; i <= productions; i++) {
            fprintf(stderr, "\tProduction %d was used\n", indexes[i]);
        }
    } else {
        return 1;
    }
    return 0;
}