#include "patient.h"
#pragma once

typedef struct ItemNode
{
    char* key;
    patientPtr PatientData;
    //ptr sto tree
} ItemNode;
typedef ItemNode* ItemNodePtr;

typedef struct HTNode
{
    struct HTNode* next;
    ItemNodePtr* array;
} HTNode;
typedef HTNode* HTNodePtr;

typedef struct HashTable
{
    int size;
    int ptrNum;
    HTNodePtr* table;
} HashTable;
typedef HashTable* HashTablePtr;

void HTPrint(HashTablePtr);
HashTablePtr HTCreate(int, int);
void HTInsert(HashTablePtr, char*, patientPtr);
int HashFunction(char*);
void HTDestroy(HashTablePtr);
