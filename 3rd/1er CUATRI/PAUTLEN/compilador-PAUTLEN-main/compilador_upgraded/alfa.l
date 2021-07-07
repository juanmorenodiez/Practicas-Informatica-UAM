%{
#include <stdio.h>
#include "alfa.h"
#include "y.tab.h"

int lines = 1;
int cols = 1;
int morf = 0;
extern FILE * out;

%}

%option noyywrap

DIGITO			[0-9]
ENTERO			{DIGITO}*
LETRA			[a-zA-Z]
IDENTIFICADOR 	{LETRA}({LETRA}|{DIGITO})*
IDERROR      [a-zA-Z][a-zA-Z0-9]*
error               	.

%%


"main"               	{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_MAIN;}
"int"                 	{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_INT;}
"boolean"            	{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_BOOLEAN;}
"array"              	{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_ARRAY;}
"function"            	{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_FUNCTION;}
"if"                  	{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_IF;}
"else"              	{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_ELSE;}
"compare"              	{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_COMPARE;}
"with"              	{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_WITH;}
"while"              	{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_WHILE;}
"for"              	    {cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_FOR;}
"scanf"              	{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_SCANF;}
"printf"              	{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_PRINTF;}
"return"             	{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_RETURN;}
";"         			{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_PUNTOYCOMA;}
","                		{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_COMA;}
"(" 					{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_PARENTESISIZQUIERDO;}
")"   					{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_PARENTESISDERECHO;}
"["						{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_CORCHETEIZQUIERDO;}
"]"     				{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_CORCHETEDERECHO;}
"{"          			{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_LLAVEIZQUIERDA;}
"}"            			{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_LLAVEDERECHA;}
"="              		{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_ASIGNACION;}
"+="              		{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_MASIGUAL;}
"-="              		{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_MENOSIGUAL;}
"*="              		{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_PORIGUAL;}
"/="              		{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_ENTREIGUAL ;}
"++"              		{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_INCREMENTO;}
"--"              		{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_DECREMENTO;}
"!!"              		{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_FACTORIAL;}
"+"                     {cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_MAS;}
"-"                   	{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_MENOS;}
"/"                		{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_DIVISION;}
"*"                     {cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_ASTERISCO;}
"^"              		{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_POTENCIA;}
"%"              		{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_MODULO;}
"€"              		{cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_LONGITUD;}
"&&"                    {cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_AND;}
"||"                               {cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_OR;}
"!"                                {cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_NOT;}
"=="                               {cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_IGUAL;}
"!="                               {cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_DISTINTO;}
"<="                               {cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_MENORIGUAL;}
">="                               {cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_MAYORIGUAL;}
"<"                                {cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_MENOR;}
">"                                {cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_MAYOR;}
{ENTERO}                           {yylval.atributos.valor_numerico = atoi(yytext); strcpy(yylval.atributos.nombre, yytext); cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_CONSTANTE_ENTERA;}
"true"                               {cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_TRUE;}
"false"                                {cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_FALSE;}
[a-zA-Z][a-zA-Z0-9]{0,99}          {strcpy(yylval.atributos.nombre, yytext); cols += yyleng; fprintf(out, ";D:\t%s\n", yytext); return  TOK_IDENTIFICADOR;}
"//".*         			{lines++; cols = 0;}
[ \t]+           		{cols += yyleng;}
\n             {lines++; cols = 0;}

{IDERROR}    {fprintf(stderr, "****Error en [lin %d, col %d]: identificador demasiado largo (%s)\n", lines, cols+1, yytext); cols += yyleng; morf = 2; return  TOK_ERROR;}
{error}                 {fprintf(stderr, "****Error en [lin %d, col %d]: simbolo no permitido (%s)\n", lines, cols+1, yytext); cols += yyleng; morf = 1; return  TOK_ERROR;}
%%