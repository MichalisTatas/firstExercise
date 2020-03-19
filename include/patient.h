#pragma once

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

patientPtr createPatientStruct(char*);