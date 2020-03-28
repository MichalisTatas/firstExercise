#include "../include/patient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareDates(datePtr date1, datePtr date2)
{
    if (date1->year > date2->year)
        return 1;
    else if (date1->year < date2->year)
        return -1;
    else {
        if (date1->month > date2->month)
            return 1;
        else if (date1->month < date2->month)
            return -1;
        else {
            if (date1->day > date2->day)
                return 1;
            else if (date1->day < date2->day)
                return -1;
        }
    }
    return 0;
}

patientPtr createPatientStruct(char* line)
{
    patientPtr current = malloc(sizeof(patient));
    char token[] = " -";

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

    current->entryDate = malloc(sizeof(date));
    line = strtok(NULL, "-");
    current->entryDate->day = atoi(line);
    line = strtok(NULL, "-");
    current->entryDate->month = atoi(line);
    line = strtok(NULL, " ");
    current->entryDate->year = atoi(line);

    line = strtok(NULL, token);

    if (strlen(line) > 1 ) {           //CHANGE THIS THING
        current->exitDate = malloc(sizeof(date));
        current->exitDate->day = atoi(line);
        line = strtok(NULL, "-");
        current->exitDate->month = atoi(line);
        line = strtok(NULL, " ");
        current->exitDate->year = atoi(line);
    }
    else
        current->exitDate = NULL;

    current->next = NULL;

    return current;
}

void sortPatientList(patientPtr head)
{
    
}

void destroyPatientList(patientPtr patient)
{
    if (patient == NULL)
        return;
    destroyPatientList(patient->next);
    free(patient->country);
    free(patient->diseaseID);
    free(patient->entryDate);
    free(patient->exitDate);
    free(patient->patientFirstName);
    free(patient->patientLastName);
    free(patient);

}