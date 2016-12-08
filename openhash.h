#ifndef OPENHASH_H_INCLUDED
#define OPENHASH_H_INCLUDED
#define TSIZE 1

typedef struct node node;
/* node
  - pointer to next block in same key
  - key
  - identifier
  - value in integer 
 */
struct node{
  //struct node *next;
  node *next;
  int key;
  char ident[20];
  int value;
  int offset;
  int rn;
};


/* hash block
   - pointer to fisrt ident
   - block number 
 */
struct hash{
  //struct node *head;
  node *head;
  int count;
};


struct hash *hashTable;
void insertNode(char *ident);
void setValue(char *ident, int num);
void setReg(char *ident, int rn);
node * createNode(int key, char *ident);
int IsThereIdent(char *ident);
int getNodeValue(char *ident);
int getNodeReg(char *ident);
int getOffset(char *ident);
int key(char * ident);

#endif
