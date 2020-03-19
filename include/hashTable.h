#include "patient.h"
#pragma once

typedef struct ItemNode
{
    char* key;
    patientPtr PatienData;
    //ptr sto tree
} ItemNode;
typedef ItemNode* ItemNodePtr;

typedef struct HTNode
{
    struct HTNode* next;
    ItemNodePtr array[];
} HTNode;
typedef HTNode* HTNodePtr;

typedef struct HashTable
{
    int ptrNum;
    HTNodePtr* table;
} HashTable;
typedef HashTable* HashTablePtr;

HashTablePtr HTCreate(int, int);
HashTablePtr HTInsert(HashTablePtr, char*, patientPtr);
int HashFunction(char*);
void HTDestroy(HashTablePtr);
