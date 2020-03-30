#include "../include/hashTable.h"
#include "../include/patient.h"
#include "../include/avlTree.h"
#include "../include/diseaseMonitor.h"
#include <wordexp.h>

int searchInTree(char* country, datePtr date1, datePtr date2, treeNodePtr tree)
{
    if (tree == NULL)
        return 0;

    int count =0;
    if (tree != NULL) {
        if (country == NULL || !strcmp(tree->patient->country, country))
            if ((date1 == NULL && date2 == NULL) || ((compareDates(tree->patient->entryDate, date1) >= 0) && (compareDates(tree->patient->exitDate, date2) <= 0)) )
                count ++;

    }

    count += (searchInTree(country, date1, date2, tree->left) + searchInTree(country, date1, date2, tree->right)); 

    return count;
}

void function(char* virus, char* country, datePtr date1, datePtr date2, HashTablePtr diseaseHT)
{
    //this function will find the tree/trees i need to search in
    HTNodePtr temp = NULL;

    if (virus == NULL) {       // traverse the hash table
        for (int i=0; i<diseaseHT->size; i++) {
            temp = diseaseHT->table[i];
            while (temp != NULL) {
                for (int j=0; j<diseaseHT->ptrNum; j++) {
                    if (temp->array[j] != NULL) {
                        printf("%s : ", temp->array[j]->key);
                        printf("%d \n",searchInTree(country, date1, date2, temp->array[j]->tree));
                    }
                }
                temp = temp->next;
            }
        }
    }
    else {                     // use hash function to find bucket
        int bucketNum = hashFunction(virus);
        temp = diseaseHT->table[bucketNum];
        while (temp != NULL) {
            for (int j=0; j<diseaseHT->ptrNum; j++) {
                if (!strcmp(virus, temp->array[j]->key)) {
                    printf("%s ", temp->array[j]->key);
                    printf("%d\n",searchInTree(country, date1, date2, temp->array[j]->tree));
                    return;
                }
            }
            temp = temp->next;
        }
    }
}


int countNullExitDates(treeNodePtr tree)
{
    if (tree == NULL)
        return 0;
    
    int count = 0;
    if (tree != NULL) {
        if (tree->patient->exitDate == NULL)
            count++;
    }
    count += (countNullExitDates(tree->left) + countNullExitDates(tree->right));
    return count;
}

void printCurrPatients(char* disease, HashTablePtr diseaseHT)
{
    HTNodePtr temp = NULL;
    if (disease != NULL) {
        temp = diseaseHT->table[hashFunction(disease)];
        while (temp != NULL) {
            for (int i=0; i<diseaseHT->ptrNum; i++) {
                if (!strcmp(temp->array[i]->key, disease)) {
                    printf("%s ", disease);
                    printf("%d\n",countNullExitDates(temp->array[i]->tree));
                }
            }
            temp = temp->next;
        }
    }
    else {
        for (int j=0; j<diseaseHT->size; j++) {
            temp = diseaseHT->table[j];
            while (temp != NULL) {
                            printf("TATAS");

                for (int i=0; i<diseaseHT->ptrNum; i++) {
                    if (temp->array[i] != NULL) {
                        printf("%s ",temp->array[i]->key);
                        printf("%d\n",countNullExitDates(temp->array[i]->tree));
                    }
               }
               temp = temp->next;
            }
        }
    }
}

int diseaseMonitor(char* command, patientPtr patientList, HashTablePtr diseaseHashtable, HashTablePtr countryHashtable, patientPtr head)
{

    datePtr date1=NULL, date2=NULL;
    wordexp_t p;
    wordexp(command, &p, 0);

    if (!strcmp(p.we_wordv[0], "/globalDiseaseStats")) {
        if (p.we_wordc == 1 )
            function(NULL, NULL, date1, date2, diseaseHashtable);
        else if(p.we_wordc == 3) {
            date1 = createDate(p.we_wordv[1]);
            date2 = createDate(p.we_wordv[2]);
            function(NULL, NULL, date1, date2, diseaseHashtable);
            free(date1);
            free(date2);
        }
        else {
            printf("number of arguments not right !\n");
            return -1;
        }
        wordfree(&p);
    }
    else if (!strcmp(p.we_wordv[0], "/diseaseFrequency")) {
        if (p.we_wordc == 4) {
            date1 = createDate(p.we_wordv[2]);
            date2 = createDate(p.we_wordv[3]);
            function(p.we_wordv[1], NULL, date1, date2, diseaseHashtable);
        }
        else if (p.we_wordc == 5) {
            date1 = createDate(p.we_wordv[2]);
            date2 = createDate(p.we_wordv[3]);
            function(p.we_wordv[1], p.we_wordv[4], date1, date2, diseaseHashtable);
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
        printf("/topk-Diseases ali8eias\n");
        wordfree(&p);
    }
    else if (!strcmp(p.we_wordv[0], "/topk-Countries")) {
        printf("/topk-Countries ali8eias\n");
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