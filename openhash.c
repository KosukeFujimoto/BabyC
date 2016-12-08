/*
  Author: Kosuke Fujimoto
  Date: 12-3-2016
  Objective: Open Hasing for symbol table 
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openhash.h"

////////////////////////////////////////////////////////////////////
//////                function definitoin                   ////////
///////////////////////////////////////////////////////////////////

/* function insertNode: return void 
   arguments:
   char *ident: identifier is declared when createNode() is invoked 
   
   Summary: 
   - generate key of hashtable by identifier
   - create new node with the ident
   - if there is no node in a nth raw in the hashtable, head-> the node
   -  ex)   none -> new node
   - else 
   -  new node point to old node
   -  ex)   new node -> old node 
   
   error:
   if there is same identifier, the new identifier cannot be decared.
   
*/
void insertNode(char *ident)
{
  int index = key(ident);
  //printf("index: %d\n",index);

  //  struct node * newnode = createNode(index,ident);
  node * newnode = createNode(index,ident);

  // If there is no node in a raw
  if(!hashTable[index].head){
    newnode->offset=0;
    hashTable[index].head = newnode;
    hashTable[index].count = 1;
    //printf("offset is: %d\n",newnode->offset);
    return;
  }
 
  if(!IsThereIdent(ident)){
    newnode->offset = hashTable[index].head->offset + 4;
    newnode->next = (hashTable[index].head);
    hashTable[index].head = newnode;
    hashTable[index].count++;
    //printf("offset is: %d\n",newnode->offset);
  }else{
    printf("There is already %s. Cannot declare the identifier twice\n", ident);
    exit(0);
  }
}


/*function setValue : return void
  arguments:
  - char * ident: target string 
  - int value : value the selected node would take
  
  Summary:
  setValue to the selected node
  Algorithm is same as IsThereNode
 */

void setValue(char *ident, int value)
{
  int index = key(ident);
  //  struct node *snode = hashTable[index].head;
  node *snode = hashTable[index].head;
  if(!snode){
    //printf("there is no identifier");
  }else{
    while(snode != NULL)
      {
	if(strcmp(ident,snode->ident)==0)
	  {
	    //printf("Target %s exists\n",ident);
	    //printf("Set value %d to %s\n",value, ident);
	    snode->value = value;
	    break;
	  }

	if(snode->next==NULL)
	  break;
	
	snode = snode->next;
      }
  }
}

/*function setValue : return void
  arguments:
  - char * ident: target string 
  - int value : value the selected node would take
  
  Summary:
  setValue to the selected node
  Algorithm is same as IsThereNode
 */

void setReg(char *ident, int rn)
{
  int index = key(ident);
  //  struct node *snode = hashTable[index].head;
  node *snode = hashTable[index].head;
  if(!snode){
    //printf("there is no identifier");
  }else{
    while(snode != NULL)
      {
	if(strcmp(ident,snode->ident)==0)
	  {
	    //printf("Target %s exists\n",ident);
	    //printf("Set value %d to %s\n",value, ident);
	    snode->rn = rn;
	    break;
	  }

	if(snode->next==NULL)
	  break;
	
	snode = snode->next;
      }
  }
}


/* function createNode : return node
   arguments: 
   - int key : key for hash table
   - char * ident : string for identifier 
   - int value : integer value corresponding to identifier
   
   Summary:
   create a node with the arguments above, and return it without next pointer 
   -> next is done in other function. 
 */

//struct node * createNode(int key, char *ident)
node * createNode(int key, char *ident)
{
  //struct node *Node;
  node *Node;
  //Node = (struct node *)malloc(sizeof(struct node));
  Node = (node *)malloc(sizeof(node));
  Node -> key = key; 
  strcpy(Node->ident,ident);
  Node -> next = NULL;
  return Node;
}


/* function IsThereIdent: return char * 
   argument: 
   char * target: target for searching from node list 
   
   summary: 
   - get index of target with key function
   - search hashlist within the nth raw 
   - if there is same identifier, return
   - else 

 */

int IsThereIdent(char *target)
{
  int index = key(target);
  //struct node *snode = hashTable[index].head;
  node *snode = hashTable[index].head;
  if(!snode){
    //printf("there is no such a identifier");
    return 0;
  }else{
    while(snode != NULL)
      {
	if(strcmp(target,snode->ident)==0)
	  {
	    //printf("Target %s exists\n",target);
	    return 1; 
	  }

	if(snode->next==NULL)
	  break;
	snode = snode->next;
      }
  }
  //printf("There is no target in the %d raw\n", index);
  return 0;
}

int getNodeValue(char *ident)
{
  int index = key(ident);
  //struct node *snode = hashTable[index].head;
  node *snode = hashTable[index].head;
  if(!snode){
    printf("there is no such a identifier\n");
    exit(0);
  }else{
    while(snode != NULL)
      {
	if(strcmp(ident,snode->ident)==0)
	  {
	    //printf("Target %s exists\n",ident);
	    return snode->value; 
	  }

	if(snode->next==NULL)
	  break;
	snode = snode->next;
      }
  }
  printf("%s is not declared \n", ident);
  exit(0);
} 

int getNodeReg(char *ident)
{
  int index = key(ident);
  //struct node *snode = hashTable[index].head;
  node *snode = hashTable[index].head;
  if(!snode){
    printf("there is no such a identifier");
    exit(0);
  }else{
    while(snode != NULL)
      {
	if(strcmp(ident,snode->ident)==0)
	  {
	    //printf("Target %s exists\n",ident);
	    return snode->rn; 
	  }

	if(snode->next==NULL)
	  break;
	snode = snode->next;
      }
  }
  printf("%s is not declared \n", ident);
  exit(0);
} 

int getOffset(char *ident)
{
  int index = key(ident);
  //struct node *snode = hashTable[index].head;
  node *snode = hashTable[index].head;
  if(!snode){
    printf("there is no such a identifier");
    exit(0);
  }else{
    while(snode != NULL)
      {
	if(strcmp(ident,snode->ident)==0)
	  {
	    //printf("Target %s exists\n",ident);
	    return snode->offset; 
	  }

	if(snode->next==NULL)
	  break;
	snode = snode->next;
      }
  }
  printf("%s is not declared \n", ident);
  exit(0);
} 

/* function key : return integer
   - Add all ASCII value of each character of an identifier
   - and return sum of ident % TSIZE 
   For exmaple
   - "a" returns 97 % 19
   - "Hello" returns 500 % 6
 */

int key(char * ident)
{
  int key=0;
  int i =0;
  for(i;(int)ident[i]!=0;i++)
    {
      int ascii = (int)ident[i];
      //      printf("%d th: ident is %s ASCII is %d\n", i, &ident[i], ascii);
      key+=ascii;
    }
  return key%TSIZE;
}
