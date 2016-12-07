#ifndef AST_H
#define AST_H

typedef enum{AOP, LOP, COMP, ASSIGN, IDENTFIER, NUMBER, IFS, WHILES,STMTL} NodeType;
typedef enum{ADD, SUB, MULT, DIV, GRET, LESS, EQUAL, NOTEQ, GEQ, LEQ, ANDOP, OROP} NodeOp;

typedef struct ASTNode ASTNode;

struct ASTNode{
  NodeType type;
  NodeOp op;
  int num;
  char *name;
  ASTNode* left;
  ASTNode* right; 
  int rn;
};


ASTNode* CreateNumNode(int num);
ASTNode* CreateIdentNode(char * ident);
ASTNode* AddNode(ASTNode *left, ASTNode *right);
ASTNode* SubNode(ASTNode *left, ASTNode *right);
ASTNode* MultNode(ASTNode *left, ASTNode *right);
ASTNode* DivNode(ASTNode *left, ASTNode *right);
ASTNode* AssignmentNode(ASTNode *ident, ASTNode *expr);
ASTNode* StmtListNode(ASTNode *left, ASTNode *right);
ASTNode* CompNode(int op, ASTNode *expr1, ASTNode *expr2);
ASTNode* AndNode(ASTNode *expr1, ASTNode *expr2);
ASTNode* OrNode(ASTNode *expr1, ASTNode *expr2);
ASTNode* IfNode(ASTNode *condition, ASTNode *stmtlist );
ASTNode* IfElseNode(ASTNode *condition, ASTNode *stmtlist1, ASTNode *stmtlist2);
ASTNode* WhileNode(ASTNode *condition, ASTNode *stmtlist);
void NodeDisplay(ASTNode *t);
void ILOC(ASTNode *root,char *fn);
ASTNode* Traverse(ASTNode *root);
void output(ASTNode *program);
int NextReg();
#endif
