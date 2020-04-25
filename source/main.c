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

int main (int argc, char* argv[])
{
    int bucketSize;
    int diseaseHashtableNumOfEntries, countryHashtableNumOfEntries;
    char* fileName;
    if (argc != 9) {
        printf ("Input numbers aren't correct\n");
        return -1;
    }

    for (int i=0; i<argc; i++) {
        if (!strcmp(argv[i], "-p")) {
            if ((fileName = malloc(strlen(argv[i+1])+1)) == NULL) {
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

    FILE* filePtr = NULL;
    filePtr = fopen(fileName, "r");
    if (filePtr == NULL) {
        printf("Failed to open file\n");
        return -1;
    }
    char* line = NULL;
    size_t len = 0;
    patientPtr current= NULL, head = NULL;
    HashTablePtr diseaseHashtable = HTCreate(diseaseHashtableNumOfEntries, bucketSize);
    HashTablePtr countryHashtable = HTCreate(countryHashtableNumOfEntries, bucketSize);

    while (getline(&line, &len, filePtr) != -1) {
        line = strtok(line, "\n");
        current = createPatientStruct(line);
        if (!existIn(head, current)) {
            if (current->exitDate != NULL && (compareDates(current->entryDate, current->exitDate) == -1)) {
                    head = patientListInsert(head, current);
                    HTInsert(diseaseHashtable, current->diseaseID, current);
                    HTInsert(countryHashtable, current->country, current);
            }
            else
                printf("record with record id %s is rejected \n", current->recordID);
        }
        else
            printf("record with record id %s is rejected \n", current->recordID);
    }

    while(getline(&line, &len, stdin) != -1) {
        strtok(line, "\n");
        if (diseaseMonitor(line, head, diseaseHashtable, countryHashtable, head) == -1)
            break;
    }

    fclose(filePtr);
    free(line);
    free(fileName);
    return 0;
}