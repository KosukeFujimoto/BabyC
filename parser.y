%{
#include <stdio.h>
#include <stdlib.h>
#include "openhash.h"
#include "ast.h"
#include "parser.tab.h"  

  extern int yylex();
  extern int yyerror(const char *);
  extern ASTNode *root;
  
%}

%initial-action
{
  //  printf("Initial Action\n");
  hashTable = (struct hash *)calloc(TSIZE,sizeof(struct hash));
}

/*
  Token is characters passed by scanner
 */
%token LE "<="
%token GE ">="
%token EQ "=="
%token NE "!="
%token OR "||"
%token AND "&&"
%token MAIN "main"
%token INT "int"
%token IF "if"
%token ELSE "else"
%token WHILE "while"

%union{
  ASTNode *node;
  int num;
  char *string;
 }

%token <string> IDENT
%token <num> NUM
%type <node> DeclarationList
%type <node> Declaration
%type <node> StatementList
%type <node> Statement
%type <node> Assignment
%type <node> If
%type <node> While
%type <node> Condition
%type <node> Compare 
%type <num> Op 
%type <node> LHS
%type <node> Expr
%type <node> Term
%type <node> Factor

%%

Goal:"main" '(' ')' '{' DeclarationList StatementList '}' { root = $6; };

DeclarationList: { }
| Declaration DeclarationList { }
;

Declaration: "int" IDENT ';' { insertNode($2); };

StatementList: { $$ = NULL; }
| Statement StatementList { $$ = StmtListNode($1, $2); };


Statement: Assignment { $$ = $1; }
| If { $$ = $1; };
| While { $$ = $1; }
;


//Create if node
If: "if" '(' Condition ')' '{' StatementList '}' { $$ = IfNode($3,$6);  }
| "if" '(' Condition ')' '{' StatementList '}' "else" '{' StatementList '}' {  $$ = IfElseNode($3, $6, $10);}
;

//Create while node
While: "while" '(' Condition ')' '{' StatementList '}' { $$ = WhileNode($3,$6); };

Condition: Compare { $$ = $1; }
| Compare "||" Condition { $$ = OrNode($1, $3); }
;

Compare: Expr Op Expr { $$ = CompNode($2, $1, $3); }
| Compare "&&" Compare {  $$ = AndNode($1, $3); }
;

Op: '>'{ $$=1; }
| '<'  { $$=2; }
| ">=" { $$=3; }
| "<=" { $$=4; }
| "==" { $$=5; }
| "!=" { $$=6; }
;

Assignment: LHS '=' Expr ';' { $$ = AssignmentNode( $1 , $3 ); };

LHS: IDENT { $$ = CreateIdentNode($1); };

Expr: Term { $$ = $1; }
| Expr '+' Term { $$ = AddNode( $1, $3 ); } 
| Expr '-' Term { $$ = SubNode( $1, $3 ); }
;

Term: Factor { $$ = $1; }
| Term '*' Factor { $$ = MultNode( $1 , $3); }
| Term '/' Factor { $$ = DivNode( $1, $3); }
;

Factor: NUM { $$ = CreateNumNode($1); }
| IDENT { $$ = CreateIdentNode($1); }
| '(' Expr ')' { $$ = $2; }
;

