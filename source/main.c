#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashTable.h"
#include "../include/patient.h"
#include "../include/avlTree.h"
#include "../include/diseaseMonitor.h"
#include "../include/binaryHeap.h"


bool existIn(patientPtr list, patientPtr patient)
{
    if (list == NULL)
        return false;

    patientPtr temp = list;
    while (temp!=NULL) {
        if (strcmp(temp->recordID, patient->recordID) == 0)
            return true;
        temp=temp->next;
    }
    return false;
}

void p(BHNodePtr node)
{
    if (node != NULL)
    {
        printf ("%s %d\n", node->key, node->volume );//entryDate->day, node->patient->entryDate->month, node->patient->entryDate->year);
        p(node->left);
        p(node->right);
    }
}


int main (int argc, char* argv[])
{
    // int bucketSize; // should it be int?
    // int diseaseHashtableNumOfEntries, countryHashtableNumOfEntries;
    // char* fileName;
    // if (argc != 9) {
    //     printf ("Input numbers aren't correct\n");
    //     return -1;
    // }

    // for (int i=0; i<argc; i++) {
    //     if (!strcmp(argv[i], "-p")) {
    //         if ((fileName = malloc(strlen(argv[i+1])+1)) == NULL) {
    //             printf("Wrong input malloc failed to allocate space\n");
    //             return -1;
    //         }
    //         strcpy(fileName, argv[i+1]);
    //     }
    //     else if (!strcmp(argv[i], "-h1")) {
    //         if ((diseaseHashtableNumOfEntries = atoi(argv[i+1])) == 0) {
    //             printf("Wrong input diseaseHashtableNumOfEntries is 0\n");
    //             return -1;
    //         }
    //     }
    //     else if (!strcmp(argv[i], "-h2")) {
    //         if ((countryHashtableNumOfEntries = atoi(argv[i+1])) == 0) {
    //             printf("Wrong input countryHashtableNumOfEntries is 0\n");
    //             return -1;
    //         }
    //     }
    //     else if (!strcmp(argv[i], "-b")) {
    //         if ((bucketSize = atoi(argv[i+1])) == 0) {
    //             printf("Wrong input bucketSize is 0\n");
    //             return -1;
    //         }
    //     }
    // }

    // FILE* filePtr = NULL;
    // filePtr = fopen("./assets/small.txt", "r");
    // if (filePtr == NULL) {
    //     printf("Failed to open file\n");
    //     return -1;
    // }
    // char* line = NULL;
    // size_t len = 0;
    // patientPtr current= NULL, head = NULL;

    // while (getline(&line, &len, filePtr) != -1) {
    //     line = strtok(line, "\n");
    //     current = createPatientStruct(line);
    //     if (!existIn(head, current)) {
    //         if (current->exitDate != NULL && (compareDates(current->entryDate, current->exitDate) == -1)) {
    //                 head = patientListInsert(head, current);
    //         }
    //         else
    //             printf("record with record id %s is rejected \n", current->recordID);
    //     }
    //     else
    //         printf("record with record id %s is rejected \n", current->recordID);
    // }

    // current = head;
    // HashTablePtr diseaseHashtable = HTCreate(diseaseHashtableNumOfEntries, bucketSize);
    // HashTablePtr countryHashtable = HTCreate(countryHashtableNumOfEntries, bucketSize);
    // treeNodePtr checkTree = NULL;

    // while (current != NULL) {
    //     // printf("%s --> %d %d %d\n", current->recordID, current->exitDate->day, current->exitDate->month, current->exitDate->year);
    //     HTInsert(diseaseHashtable, current->diseaseID, current);
    //     HTInsert(countryHashtable, current->country, current);
    //     current = current->next;
    // }
    // // preorder(checkTree);
    // // HTPrint(countryHashtable);
    // // HTPrint(diseaseHashtable);
    // while(getline(&line, &len, stdin) != -1) {
    //     strtok(line, "\n");
    //     if (diseaseMonitor(line, head, diseaseHashtable, countryHashtable, head) == -1)
    //         break;
    // }
    // AVLDestroy(checkTree);
    // fclose(filePtr);
    // free(line);
    // free(fileName);
    BinaryHeapPtr heap = BHInit();
    BHInsert(heap, "USA", 13);
    BHInsert(heap, "GR", 3);
    BHInsert(heap, "BUL", 1);
    BHInsert(heap, "ITA", 11);
    BHInsert(heap, "FR", 12);
    BHInsert(heap, "DE", 19);
    lvl(heap);
    BHNodePtr temp;
    temp = BHRemove(heap);
    printf("%s %d \n" , temp->key, temp->volume);
    free(temp->key);
    free(temp);
    lvl(heap);
    temp = BHRemove(heap);
    printf("%s %d \n" , temp->key, temp->volume);
    free(temp->key);
    free(temp);
    temp = BHRemove(heap);
    printf("%s %d \n" , temp->key, temp->volume);
    free(temp->key);
    free(temp);
    temp = BHRemove(heap);
    printf("%s %d \n" , temp->key, temp->volume);
    free(temp->key);
    free(temp);
    BHDestroy(heap);

    return 0;
}