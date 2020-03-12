#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct patient{
    int recordID;
    char* patientFirstName;
    char* patientLastName;
    char* diseaseID;
    char* country;
    char* entryDate;
    char* exitDate;
    struct patient* next;
}patient;
typedef patient* patientPtr;

patientPtr createPatientStruct(char* line)
{
    patientPtr current = malloc(sizeof(patient));

    line = strtok(line, " ");
    current->recordID = atoi(line);

    line = strtok(NULL, " ");
    current->patientFirstName = malloc(sizeof(line));
    strcpy(current->patientFirstName, line);
    
    line = strtok(NULL, " ");
    current->patientLastName = malloc(sizeof(line));
    strcpy(current->patientLastName, line);
    
    line = strtok(NULL, " ");
    current->diseaseID = malloc(sizeof(line));
    strcpy(current->diseaseID, line);
    
    line = strtok(NULL, " ");
    current->country = malloc(sizeof(line));
    strcpy(current->country, line);
    
    line = strtok(NULL, " ");
    current->entryDate = malloc(sizeof(line));
    strcpy(current->entryDate, line);
    if (line != NULL) {
        line = strtok(NULL, " ");
        current->exitDate = malloc(sizeof(line));
        strcpy(current->exitDate, line);
    }
    else current->exitDate = NULL;
    current->next = NULL;
    return current;
}

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
    int counter = 0;
    while (current != NULL) {
        printf("%d %s %s %s %s %s %s \n", current->recordID, current->patientFirstName, current->patientLastName, current->diseaseID, current->country, current->entryDate, current->exitDate);
        current = current->next;
        counter ++;
    }
    free(filePtr);
    // free(line);
    free(fileName);
    return 0;
}