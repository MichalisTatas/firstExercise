#include "../include/diseaseMonitor.h"

int diseaseMonitor(char* command, patientPtr patientList, HashTablePtr diseaseHashtable, HashTablePtr countryHashtable, patientPtr head)
{

    datePtr date1=NULL, date2=NULL;
    wordexp_t p;
    wordexp(command, &p, 0);

    if (!strcmp(p.we_wordv[0], "/globalDiseaseStats")) {
        if (p.we_wordc == 1 ) {
            char* dt = malloc(sizeof("00-00-00") + 1);
            strcpy(dt, "00-00-00");
            date1 = createDate(dt);
            strcpy(dt, "0-0-9999");
            date2 = createDate(dt);
            statsFrequency(NULL, NULL, date1, date2, diseaseHashtable);
            free(dt);
        }
        else if(p.we_wordc == 3) {
            date1 = createDate(p.we_wordv[1]);
            date2 = createDate(p.we_wordv[2]);
            statsFrequency(NULL, NULL, date1, date2, diseaseHashtable);
        }
        else {
            printf("number of arguments not right !\n");
            return -1;
        }
        free(date1);
        free(date2);
        wordfree(&p);
    }
    else if (!strcmp(p.we_wordv[0], "/diseaseFrequency")) {
        if (p.we_wordc == 4) {
            date1 = createDate(p.we_wordv[2]);
            date2 = createDate(p.we_wordv[3]);
            statsFrequency(p.we_wordv[1], NULL, date1, date2, diseaseHashtable);
        }
        else if (p.we_wordc == 5) {
            date1 = createDate(p.we_wordv[2]);
            date2 = createDate(p.we_wordv[3]);
            statsFrequency(p.we_wordv[1], p.we_wordv[4], date1, date2, diseaseHashtable);
        }
        else {
            printf("number of arguments is not right");
            return -1;
        }

        free(date1);
        free(date2);
        wordfree(&p);
    }
    else if (!strcmp(p.we_wordv[0], "/topk-Diseases")) {
        if (p.we_wordc == 3) {
            char* dt = malloc(sizeof("00-00-00") + 1);
            strcpy(dt, "00-00-00");
            date1 = createDate(dt);
            strcpy(dt, "0-0-9999");
            date2 = createDate(dt);
            topkDiseases(countryHashtable, diseaseHashtable, date1, date2, atoi(p.we_wordv[1]), p.we_wordv[2]);
            free(dt);
        }
        else if (p.we_wordc == 5) {
            date1 = createDate(p.we_wordv[3]);
            date2 = createDate(p.we_wordv[4]);
            topkDiseases(countryHashtable, diseaseHashtable, date1, date2, atoi(p.we_wordv[1]), p.we_wordv[2]);
        }
        else {
            printf("number of arguments is not right !\n");
            return -1;
        }
        free(date1);
        free(date2);
        wordfree(&p);
    }
    else if (!strcmp(p.we_wordv[0], "/topk-Countries")) {
        if (p.we_wordc == 3) {

        }
        else if (p.we_wordc == 5) {

        }
        else {
            printf("number of arguments is not right !\n");
            return -1;
        }
        wordfree(&p);
    }
    else if (!strcmp(p.we_wordv[0], "/insertPatientRecord")) {
        if (p.we_wordc == 8 || p.we_wordc == 7) {     // it automatically adds "-" to exit if exit date doesn't exist
            printf("Record added\n");
            command = strtok(command, " ");
            command = strtok(NULL, "\n");
            patientPtr pat = createPatientStruct(command);
            HTInsert(diseaseHashtable, pat->diseaseID, pat);
            HTInsert(countryHashtable, pat->country, pat);
            head = patientListInsert(head, pat);
        }
        else {
            printf("number of arguments in not right !\n");
            return -1;
        }
        wordfree(&p);
    }
    else if (!strcmp(p.we_wordv[0], "/recordPatientExit")) {
        if (p.we_wordc == 3) {
            replaceExitDate(head, p.we_wordv[1], p.we_wordv[2]);
            printf("Record updated\n");
        }
        else {
            printf("number of arguments is not right !\n");
            return -1;
        }
        wordfree(&p);
    }
    else if (!strcmp(p.we_wordv[0], "/numCurrentPatients")) {
        if (p.we_wordc == 1) {
            printCurrPatients(NULL, diseaseHashtable);
        }
        else if (p.we_wordc == 2) {
            printCurrPatients(p.we_wordv[1], diseaseHashtable);
        }
        else {
            printf("number of arguments is not right !\n");
            return -1;
        }
        wordfree(&p);
    }
    else if (!strcmp(p.we_wordv[0], "/exit")) {
        // patientPtr temp = head;
        // while(temp->next != NULL){
        //     printf("%s --> %d %d %d\n", temp->recordID, temp->exitDate->day, temp->exitDate->month, temp->exitDate->year);
        //     temp=temp->next;
        // }
        printf("exiting\n");
        HTDestroy(diseaseHashtable);
        HTDestroy(countryHashtable);
        destroyPatientList(patientList);
        wordfree(&p);
        return -1;
    }
    else 
        printf("wrong command ! \n");

    return 0; 
}