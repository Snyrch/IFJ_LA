//hlavicka pro lexikalni analyzator
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

//identifikator
#define ID       0

//klicova slova
#define ELSE 10
#define FLOAT64    11
#define FOR   12
#define FUNC   13
#define IF 14
#define INT 15
#define PACKAGE 16
#define RETURN 17
#define STRING 18

// num
#define NUM 19

//operatory inkrementace a dekrementace
#define INC     20
#define DEC     21

//jednotlive znaky + dvojice
#define LEFT_BR 22 // '('
#define RIGHT_BR 23 // ')'
#define LEFT_VINCULUM  24 // '{'
#define RIGHT_VINCULUM 25 // '}'
#define LEFT_BRR 26 // '['
#define RIGHT_BRR 27 // ']'
#define SEMICOLON 28 // ';'
#define COMA 29 // ','

#define MULTIPLY 30 // '*'
#define DIVIDE 31 // '/'
#define PLUS 32 // '+'
#define MINUS 33 // '-'
#define LESS 34 // '<'
#define LESS_AND_EQUAL 35 // "<="
#define GREAT 36 // '>'
#define GREAT_AND_EQUAL 37 // ">="
#define EQUAL 38 // '='
#define DOUBLE_EQUAL 39 // "=="
#define NOT_EQUAL 40 // "!="

#define TEXT 41 // "nejaky text"
//prirazeni 
#define ASSIGN 80 // ":="


//specialni znaky
#define END_OF_FILE    100 
#define END_OF_LINE    90 // '\n'

//chybove hlasky
#define LEX_ERROR    -1

//hlavicka funkce simulujici lexikalni analyzator
int getNextToken(string *attr);