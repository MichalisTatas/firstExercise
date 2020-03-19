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
