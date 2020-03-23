#include "../include/patient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

patientPtr createPatientStruct(char* line)
{
    patientPtr current = malloc(sizeof(patient));

    line = strtok(line, " ");
    current->recordID = atoi(line);

    line = strtok(NULL, " ");
    current->patientFirstName = malloc(strlen(line) + 1);
    strcpy(current->patientFirstName, line);
    
    line = strtok(NULL, " ");
    current->patientLastName = malloc(strlen(line) + 1);
    strcpy(current->patientLastName, line);
    
    line = strtok(NULL, " ");
    current->diseaseID = malloc(strlen(line) + 1);
    strcpy(current->diseaseID, line);
    
    line = strtok(NULL, " ");
    current->country = malloc(strlen(line) + 1);
    strcpy(current->country, line);
    
    line = strtok(NULL, " ");
    current->entryDate = malloc(strlen(line) + 1);
    strcpy(current->entryDate, line);
    if (line != NULL) {
        line = strtok(NULL, " ");
        current->exitDate = malloc(strlen(line) + 1);
        strcpy(current->exitDate, line);
    }
    else current->exitDate = NULL;
    current->next = NULL;

    return current;
}
