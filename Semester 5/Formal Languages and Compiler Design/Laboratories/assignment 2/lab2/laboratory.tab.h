/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     VAR = 258,
     BEGIN_T = 259,
     END_T = 260,
     IF = 261,
     THEN = 262,
     ELSE = 263,
     WHILE = 264,
     DO = 265,
     READ = 266,
     WRITE = 267,
     ARRAY = 268,
     OF = 269,
     BOOLEAN = 270,
     CHAR_T = 271,
     INTEGER = 272,
     REAL = 273,
     AND = 274,
     OR = 275,
     NOT = 276,
     IDENTIFIER = 277,
     INTCONST = 278,
     ASSIGN = 279,
     LE = 280,
     GE = 281,
     NEQ = 282,
     LT = 283,
     GT = 284,
     EQ = 285
   };
#endif
/* Tokens.  */
#define VAR 258
#define BEGIN_T 259
#define END_T 260
#define IF 261
#define THEN 262
#define ELSE 263
#define WHILE 264
#define DO 265
#define READ 266
#define WRITE 267
#define ARRAY 268
#define OF 269
#define BOOLEAN 270
#define CHAR_T 271
#define INTEGER 272
#define REAL 273
#define AND 274
#define OR 275
#define NOT 276
#define IDENTIFIER 277
#define INTCONST 278
#define ASSIGN 279
#define LE 280
#define GE 281
#define NEQ 282
#define LT 283
#define GT 284
#define EQ 285




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

