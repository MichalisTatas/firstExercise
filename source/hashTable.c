#include "../include/hashTable.h"
#include <stdio.h>
#include <stdlib.h>

HashTablePtr HTCreate(int size, int bucketSize)
{
    HashTablePtr ht = malloc(sizeof(HashTable));
    ht->table = malloc(size*sizeof(HTNode));
    // check if it fits perfectly
    int checker;
    if ((checker = bucketSize % 8) == 0)
        ht->ptrNum = bucketSize/8 - 1; //see how many pointers i can store minus the one to the next HTNode
    else 
        ht->ptrNum = (bucketSize - checker)/8 - 1;

    for (int i=0; i<size; i++)
        ht->table[i] = NULL;

    return ht;
}

void recursiveInsert()
{

}

HashTablePtr HTInsert(HashTablePtr hashTable, char* key, patientPtr patient)
{
    HTNodePtr node = malloc((hashTable->ptrNum + 1)*8);     //8 for each pointer
    printf("size : %ld \n", sizeof(node));
    //recursively find last bucket of chain
    //insert it there if there is free space otherwise create new bucket
    // recursiveInsert();

}

int hashFunction(char* str)    //djb2 hash function ;;
{
    return (*str)/10;
}

void HTDestroy(HashTablePtr hashTable)
{
    free(hashTable->table);
    free(hashTable);
}