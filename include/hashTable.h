#pragma once

typedef struct ItemNode
{
    char* key;
    int data;
    struct ItemNode* next;
} ItemNode;
typedef ItemNode* ItemNodePtr;

typedef struct HTNode
{
    char* key;
    ItemNode item;
    struct HTNode* next;
} HTNode;
typedef HTNode* HTNodePtr;

typedef struct HashTable
{
    HTNodePtr* table;
} HashTable;
typedef HashTable* HashTablePtr;