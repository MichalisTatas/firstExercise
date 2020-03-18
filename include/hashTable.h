#include "patient.h"
#pragma once

int hashFunction(char* str)    //djb2 hash function ;;
{
    return (*str)/10;
}

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
    HTNodePtr* table;
} HashTable;
typedef HashTable* HashTablePtr;