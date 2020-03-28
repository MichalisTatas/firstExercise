#include "patient.h"

typedef struct treeNode
{
    char* key;
    int height;
    patientPtr patient;
    struct treeNode* left;
    struct treeNode* right;
} treeNode;
typedef treeNode* treeNodePtr;

void AVLDestroy(treeNodePtr);
void preorder(treeNodePtr);
treeNodePtr AVLInsert(treeNodePtr, patientPtr, char*);