#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashTable.h"
#include "../include/patient.h"

//recursively destroy the list and then destroy the hashtable and finally check for leaks before its too late

int main (int argc, char* argv[])
{
    int bucketSize; // should it be int?
    int diseaseHashtableNumOfEntries, countryHashtableNumOfEntries;
    char* fileName;
    if (argc != 9) {
        printf ("Input numbers aren't correct\n");
        return -1;
    }

    for (int i=0; i<argc; i++) {
        if (!strcmp(argv[i], "-p")) {
            if ((fileName = malloc(sizeof(argv[i+1]))) == NULL) {
                printf("Wrong input malloc failed to allocate space\n");
                return -1;
            }
            strcpy(fileName, argv[i+1]);
        }
        else if (!strcmp(argv[i], "-h1")) {
            if ((diseaseHashtableNumOfEntries = atoi(argv[i+1])) == 0) {
                printf("Wrong input diseaseHashtableNumOfEntries is 0\n");
                return -1;
            }
        }
        else if (!strcmp(argv[i], "-h2")) {
            if ((countryHashtableNumOfEntries = atoi(argv[i+1])) == 0) {
                printf("Wrong input countryHashtableNumOfEntries is 0\n");
                return -1;
            }
        }
        else if (!strcmp(argv[i], "-b")) {
            if ((bucketSize = atoi(argv[i+1])) == 0) {
                printf("Wrong input bucketSize is 0\n");
                return -1;
            }
        }
    }

    printf("%s  %d %d %d \n", fileName, diseaseHashtableNumOfEntries, countryHashtableNumOfEntries, bucketSize);

    FILE* filePtr = NULL;
    filePtr = fopen("./assets/small.txt", "r");
    if (filePtr == NULL) {
        printf("Failed to open file\n");
        return -1;
    }
    char* line = NULL;
    size_t len = 0;
    patientPtr current, head= NULL;
    while (getline(&line, &len, filePtr) != -1) {
        // printf("%s \n",line);
        current = createPatientStruct(line);
        current->next = head;
        head = current;
    }

    current = head;
    // while (current != NULL) {
    //     // printf("%d %s %s %s %s %s %s \n", current->recordID, current->patientFirstName, current->patientLastName, current->diseaseID, current->country, current->entryDate, current->exitDate);

    //     current = current->next;
    // }
    HashTablePtr ht = HTCreate(diseaseHashtableNumOfEntries, bucketSize);
    HTInsert(ht, "m", head);
    HTDestroy(ht);
    free(filePtr);
    // free(line);
    free(fileName);
    return 0;
}