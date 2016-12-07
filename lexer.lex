%{
  #include <stdio.h>
  #include <string.h>
  #include "ast.h"
  #include "parser.tab.h"

void yyerror(const char *s)
{
  printf("Error on line %d: %s.\n", yylineno, s);
  exit(1);
}
%}

%option yylineno
%option noyywrap

%%
"," return ',';
";" return ';';
"+" return '+';
"-" return '-';
"*" return '*';
"/" return '/';
"<" return '<';
">" return '>';
"=" return '=';
"(" return '(';
")" return ')';
"{" return '{';
"}" return '}';

"||" return OR;
"&&" return AND; 
"==" return EQ;
"!=" return NE;
"<=" return LE;
">=" return GE;

"int" return INT;
"main" return MAIN;
"if"  return IF;
"else" return ELSE;
"while" return WHILE;

[a-z|A-Z]([a-z]|[A-Z]|[0-9])* yylval.string = strdup(yytext); return IDENT; //Identifier
0|[1-9][0-9]*	yylval.num = atoi(yytext); return NUM; //Number

[ \t\n]+		//Whitespace is ignored
.           printf( "ERROR on Line %d: Unrecognized token \n", yylineno ); exit(1); //No match. Fatal error.
