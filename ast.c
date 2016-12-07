/* File: ast.c 
   Author: Kosuke Fujimoto
   Ojective: Creating ASTNode for bison.
   
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "openhash.h"

FILE *file;
static int RegNum = 0;

ASTNode* CreateNumNode(int num)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = NUMBER;
  node->name = "Number";
  node->num = num;
  node->left = NULL;
  node->right = NULL;
  return node;
}

ASTNode* CreateIdentNode(char *name)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = IDENTFIER;
  node->name = name;
  node->num = getNodeValue(name);
  node->left = NULL;
  node->right = NULL;
  //printf("%s has %d\n",name, node->num);
  return node;
}


ASTNode* AddNode(ASTNode *left, ASTNode *right)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = AOP;
  node->op = ADD;
  node->name = "Add";
  node->num = left->num + right->num;
  node->left = left;
  node->right = right;
  return node;
}

ASTNode* SubNode(ASTNode *left, ASTNode *right)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = AOP;
  node->op = SUB;
  node->name = "Sub";
  node->num = left->num - right->num;
  node->left = left;
  node->right = right;
  return node;
}

ASTNode* MultNode(ASTNode *left, ASTNode *right)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = AOP;
  node->op = MULT;
  node->name = "Mult";
  node->num = left->num * right->num;
  node->left = left;
  node->right = right;
  return node;
}
  
ASTNode* DivNode(ASTNode *left, ASTNode *right)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = AOP;
  node->op = DIV;
  node->name = "Div";
  node->num = (int)(left->num / right->num);
  node->left = left;
  node->right = right;
  return node;
}

ASTNode* AssignmentNode(ASTNode *ident, ASTNode *expr)
{
  if(IsThereIdent(ident->name)){
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = ASSIGN;
  //  node->name = ident->name;
  node->name = "Assignment";
  node->num = expr->num;
  node->left = ident;
  node->right = expr;
  setValue(ident->name,expr->num);
  //printf("expr value has %d\n",node->num);
  return node;
  }else{
    printf("Error: %s is unknown variable\n", ident->name);
    exit(0);
  }
}

ASTNode* StmtListNode(ASTNode *left, ASTNode *right)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->name = "StatementList";
  node->type = STMTL;
  node->left = left;
  node->right = right;
  return node;
}

ASTNode* CompNode(int op, ASTNode *expr1, ASTNode *expr2)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  
  switch(op)
  {
    //GRE
  case 1:
    node->type = COMP;
    node->op = GRET;
    node->name = "GRE";
    node->num = (expr1->num) > (expr2->num) ;
    node->left = expr1;
    node->right = expr2;

    break;
    //LESS
  case 2:
    node->type = COMP;
    node->op = LESS;
    node->name = "LESS";
    node->num = (expr1->num) < (expr2->num) ;
    node->left = expr1;
    node->right = expr2;
    break;
    
    //GEQ
  case 3:
    node->type = COMP;
    node->op = GEQ;
    node->name = "GEQ";
    node->num = (expr1->num) >= (expr2->num) ;
    node->left = expr1;
    node->right = expr2;
    break;
    
    //LEQ
  case 4:
    node->type = COMP;
    node->op = LEQ;
    node->name = "LEQ";
    node->num = (expr1->num) <= (expr2->num) ;
    node->left = expr1;
    node->right = expr2;
    break;
    
  case 5:
    node->type = COMP;
    node->op = EQUAL;
    node->name = "EQUAL";
    node->num = (expr1->num) == (expr2->num) ;
    node->left = expr1;
    node->right = expr2;
    
    break;
    //LEQ
  case 6:
    node->type = COMP;
    node->op = NOTEQ;
    node->name = "NOTEQ";
    node->num = (expr1->num) != (expr2->num) ;
    node->left = expr1;
    node->right = expr2;
    break;
    
  default:
    printf("Error: unexpected action occur in comparison");
    exit(0);
  }
  //  NodeDisplay(node);
  return node;
}

ASTNode* AndNode(ASTNode *expr1, ASTNode *expr2)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = LOP;
  node->op = ANDOP;
  node->name = "AndNode";
  node->num = (expr1->num) && (expr2->num) ;
  node->left = expr1;
  node->right = expr2;
  NodeDisplay(node);
  return node;
}

ASTNode* OrNode(ASTNode *expr1, ASTNode *expr2)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = LOP;
  node->op = OROP;
  node->name = "OrNode";
  node->num = (expr1->num) || (expr2->num) ;
  node->left = expr1;
  node->right = expr2;
  NodeDisplay(node);
  return node;
}

ASTNode* IfNode(ASTNode *condition, ASTNode *stmtlist )
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = IFS;
  node->name = "IfNode";
  node->left = condition;
  if(condition->num)
    {
      node->right = stmtlist;
    }
  return node;
}

ASTNode* IfElseNode(ASTNode *condition, ASTNode *stmtlist1, ASTNode *stmtlist2)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = IFS;
  node->name = "IfElseNode";
  node->left = condition;
  if(condition->num)
    {
      node->right = stmtlist1;
      //printf("node is %d\n",node->left->num);
    }
  else
    {
      node->right = stmtlist2;
      //printf("node is %d\n",node->left->num);
    }
  return node;
}

ASTNode* WhileNode(ASTNode *condition, ASTNode *stmtlist)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = WHILES;
  node->name = "WhileNode";
  node->left = condition;
  node->right = stmtlist;
  return node;
}

void NodeDisplay(ASTNode *t)
{
  //if(t->type==STMTL){
  printf("Node : %s\n",t->name);
  printf("Value :%d\n",t->num);
  printf("reg# :%d\n",t->rn);


  
  if(t->left!=NULL){
    printf("left node :%s\n",t->left->name);
  printf("left reg# :%d\n",t->left->rn);
    //printf("left:%d\n",t->left->num);
    //      printf("reg# :%s\n",t->left->reg);
  }
  
  if(t->right!=NULL){
    printf("right node:%s\n",t->right->name);
    printf("rightreg# :%d\n",t->right->rn);
    //printf("right:%d\n",t->right->num);
    //printf("reg# :%s\n",t->right->reg);
  }
  printf("\n");
}

/*
  Data Structure is Binary Search Tree 
  Depending on Nodetype and NodeOP, the ILOC would be differernt
  Search from left because of architeture 
  Left Right Parent
*/

void ILOC(ASTNode *root, char *fn)
{
  int size = strlen(fn)-2;
  char *nn=malloc(sizeof(size+4));
  strncpy(nn,fn,size);
  strcat(nn,"iloc");
  printf("%s\n",nn);
  file = fopen(nn,"w");
  Traverse(root);
  fclose(file);
}

ASTNode* Traverse(ASTNode *root)
{
  ASTNode *node;
  //printf("root\n");
  //NodeDisplay(root);

  //Check Left Node until null

  if(root->left==NULL)
    {
      return root;
    }
  
  node = Traverse(root->left);

  //  output(root);
  //printf("Child node is:\n");
  //  NodeDisplay(root);
  //  output(root);
  
  if(root->right!=NULL)
    {
      node = Traverse(root->right);
    }
  output(root);
  NodeDisplay(root);
  //printf("node is:\n");
  return root;
}

void output(ASTNode *program)
{
  NodeType rtype,ltype;
  char reg[5];
  
  if(program->right!=NULL){
    rtype = program->right->type;
  }

  if(program->left!=NULL){
    ltype = program->left->type;
  }
  
  switch(program->type)
    {
    case STMTL:
      if((program->left->type==ASSIGN)&&((program->right==NULL)||(program->right->left->type!=ASSIGN)))
	{
	  //	  fprintf(file,"Basic Block\n");
	}
      
      if((program->type==IFS)&&(program->right==NULL))
	{
	  //	  fprintf(file,"Basic Block\n");
	}

      if((program->type==WHILES)&&(program->right==NULL))
	{
	  //	  fprintf(file,"Basic Block\n");
	}      
    break;
      
    case AOP:
      if(((ltype==AOP)||(ltype==NUMBER)||(ltype==IDENTFIER))
	 &&
	 ((rtype==AOP)||(rtype==NUMBER)||(rtype==IDENTFIER)))
	{
	  program->rn = NextReg();
	  //sprintf(reg,"r%d",x);
	  if( program->op == ADD )
	    {	      
	      fprintf(file,"add %d %d -> r%d\n", program->left->rn, program->right->rn, program->rn);
	    }
	  else if( program->op == SUB )
	    {
	      fprintf(file,"sub %d %d -> r%d\n", program->left->rn, program->right->rn, program->rn);
	    }
	  else if( program->op == MULT)
	    {
	      fprintf(file,"mult %d %d -> r%d\n", program->left->rn, program->right->rn, program->rn);
	    }
	  else if( program->op == DIV)
	    {
	      fprintf(file,"div %d %d -> r%d\n", program->left->rn, program->right->rn, program->rn);
	    }
	}
      break;

    case LOP:
      if(program->op==ANDOP)
	{
	  fprintf(file,"and %s %s -> \n", program->left->name,program->right->name);
	}
      else if(program->op==OROP)
	{
	  fprintf(file,"or %s %s -> \n", program->left->name,program->right->name);
	}
      break;
      
    case COMP:
      program->rn = NextReg();
      if(program->op==GRET)
	{
	  fprintf(file,"comp_GT %d %d -> %d\n",program->left->num,program->right->num,program->rn);
	}
      else if(program->op==LESS)
	{
	  fprintf(file,"comp_LT %d %d -> %d\n",program->left->num,program->right->num,program->rn);
	}
      else if(program->op==GEQ)
	{
	  fprintf(file,"comp_GE %d %d -> %d\n",program->left->num,program->right->num,program->rn);
	}
      else if(program->op==LEQ)
	{
	  fprintf(file,"comp_LE %d %d -> %d\n",program->left->num,program->right->num,program->rn);	  
	}
      else if(program->op==EQUAL)
 	{
	  fprintf(file,"comp_EQ %d %d -> %d\n",program->left->num,program->right->num,program->rn);	  	  
	}
      else if(program->op==NOTEQ)
	{
	  fprintf(file,"comp_NE %d %d ->\n",program->left->num,program->right->num);	  	  
	}
      break;

    case ASSIGN:
      if(rtype==NUMBER)
	{
	  program->rn = NextReg();
	  int num = program->right->num;
	  fprintf(file,"storeI %d -> @rarp, offset\n", num);
	}

      if((rtype==AOP)||(rtype==IDENTFIER))
	{
	  program->rn = NextReg();
	  char *ident = program->right->name;
	  fprintf(file,"store %d -> rarp offset\n", program->right->rn );
	}
      
      break;

    case WHILES:
      
      break;
      
    default:
      break;
    }
}

int NextReg()
{
  return RegNum++;
}
