#include "patient.h"

typedef struct treeNode
{
    char* key;
    int height;
    patientPtr patient;
    struct treeNode* right;
    struct treeNode* left;
} treeNode;
typedef treeNode* treeNodePtr;

void AVLDestroy(treeNodePtr);
void preorder(treeNodePtr);
treeNodePtr AVLInsert(treeNodePtr, patientPtr, char*);