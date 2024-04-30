#ifndef BTREE_H
#define BTREE_H

typedef struct BtreeNode* pNode;
typedef void(*pFunction)(pNode);
typedef wchar_t Data;
typedef struct BtreeNode {pNode left,right; Data data;} BtreeNode;

pNode NewNode(Data data);
void Delete(pNode node);
void PreProcess(pNode root, pFunction Function);
void PostProcess(pNode root, pFunction Function);
void Insert(pNode* p_root, Data data);
pNode Find(pNode root, pNode* p_parent, int* p_LR, Data data);
pNode FindRightMin(pNode root, pNode* p_parent);
void DeleteNode(pNode* ROOT, Data D);
void RotateRight(pNode* pLev0);
void RotateLeft(pNode* pLev0);
void InsertRoot(pNode* proot, Data D);

void PrintTree(pNode root);
int GetHeight(pNode root);
int GetNodeCount(pNode root);
void DestroyBtree(pNode root);

#endif