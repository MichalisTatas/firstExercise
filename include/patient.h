#pragma once

typedef struct date
{
    int day;
    int month;
    int year;
} date;
typedef date* datePtr;

typedef struct patient{
    char* recordID;
    char* patientFirstName;
    char* patientLastName;
    char* diseaseID;
    char* country;
    datePtr entryDate;
    datePtr exitDate;
    struct patient* next;
}patient;
typedef patient* patientPtr;

datePtr createDate(char*);
void replaceExitDate(patientPtr, char*, char*);
patientPtr patientListInsert(patientPtr, patientPtr);
int compareDates(datePtr, datePtr);
patientPtr createPatientStruct(char*);
void destroyPatientList(patientPtr);