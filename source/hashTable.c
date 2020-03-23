#include "../include/hashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HashTablePtr HTCreate(int size, int bucketSize)
{
    HashTablePtr ht = malloc(sizeof(HashTable));
    ht->table = malloc(size*sizeof(HTNode));
    ht->size = size;
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

int hashFunction(char* str)    //djb2 hash function ;;
{
    return (*str)/10;
}

int hasBucketFreeSpace(HTNodePtr hashNode, int numOfEntries)
{

    for (int i=0; i<numOfEntries; i++) {
        if (hashNode->array[i] == NULL)
            return i;
    }

    return -1;
}

void HTInsert(HashTablePtr hashTable, char* key, patientPtr patient)
{
    int bucketNum = hashFunction(key);
    int help;
    ItemNodePtr item = malloc(sizeof(ItemNode));
    item->key = malloc(strlen(key) + 1);
    strcpy(item->key, key);
    // item->key = key;
    item->PatientData = patient;

    if (hashTable->table[bucketNum] == NULL) {    // if bucket is empty
        hashTable->table[bucketNum] = malloc(sizeof(HTNode));
        hashTable->table[bucketNum]->array = malloc(hashTable->ptrNum * sizeof(ItemNode));
        hashTable->table[bucketNum]->next = NULL;
        for (int i=0; i<hashTable->ptrNum; i++)
            hashTable->table[bucketNum]->array[i] = NULL;
        *hashTable->table[bucketNum]->array = item;
    }
    else {                                        // if bucket is not empty
        HTNodePtr temp = hashTable->table[bucketNum];
        while (temp->next != NULL)                  //find last bucket of chain
            temp = temp->next;
        if ((help = hasBucketFreeSpace(temp, hashTable->ptrNum)) != -1) { //if last bucket has free space
            temp->array[help] = item;
        }
        else {                                      // if last bucket no space create new and add to end
            temp->next = malloc(sizeof(HTNode));
            temp = temp->next;
            temp->next = NULL;
            temp->array = malloc(hashTable->ptrNum * sizeof(ItemNode));
            for (int i=0; i<hashTable->ptrNum; i++)
                temp->array[i] = NULL;
            *temp->array = item;
        }
    }
}

void HTPrint(HashTablePtr hashTable)
{
    HTNodePtr temp;
    for (int i=0; i<hashTable->size; i++) {
        if (hashTable->table[i] != NULL) {
            temp = hashTable->table[i];
            while (temp != NULL) {
                for (int j=0; j<hashTable->ptrNum; j++) {
                    // printf("TATAS!! ");
                    if (temp->array[j] != NULL)
                        printf("%s --> ", temp->array[j]->key);
                }
                temp = temp->next;
            }
        }
        printf("\n");
    }
}

void recursiveDestroy(HTNodePtr node, int ptrNum)
{
    if (node == NULL)
        return;
    recursiveDestroy(node->next, ptrNum);
    for (int i=0; i<ptrNum; i++) {
        if (node->array[i] != NULL) {
            free(node->array[i]->key);
            free(node->array[i]);
        }
    }
    free(node->array);
    free(node);
}

void HTDestroy(HashTablePtr hashTable)
{
    for (int i=0; i<hashTable->size; i++)
        recursiveDestroy(hashTable->table[i], hashTable->ptrNum);
    free(hashTable->table);
    free(hashTable);
}

