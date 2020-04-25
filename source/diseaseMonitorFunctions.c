#include "../include/diseaseMonitorFunctions.h"
#include "../include/binaryHeap.h"

int searchInTree(char* country, char* disease, datePtr date1, datePtr date2, treeNodePtr tree)
{
    if (tree == NULL)
        return 0;

    if (compareDates(tree->patient->entryDate, date1) == -1) {
        searchInTree(country, disease, date1, date2, tree->right);
    }
    else if (compareDates(tree->patient->entryDate, date2) == 1) {
        searchInTree(country, disease, date1, date2, tree->left);
    }

    int count =0;
    patientPtr list;
    if (disease == NULL || !strcmp(tree->patient->diseaseID, disease)) {
        if (country == NULL || !strcmp(tree->patient->country, country)) {
            if ((compareDates(tree->patient->entryDate, date1) >= 0) && (compareDates(tree->patient->exitDate, date2) <= 0)) {
                list = tree->patient;  //searches the list of patients because some may not be in the tree bcz they have the same date
                while (list != NULL && compareDates(list->entryDate, tree->patient->entryDate)==0){
                    count ++;
                    list = list->next;
                }
                
            }
        }
    }

    
    count += (searchInTree(country, disease, date1, date2, tree->left) + searchInTree(country, disease, date1, date2, tree->right)); 

    return count;
}

void statsFrequency(char* virus, char* country, datePtr date1, datePtr date2, HashTablePtr diseaseHT)
{
    HTNodePtr temp = NULL;

    if (virus == NULL) {       // traverse the hash table
        for (int i=0; i<diseaseHT->size; i++) {
            temp = diseaseHT->table[i];
            while (temp != NULL) {
                for (int j=0; j<diseaseHT->ptrNum; j++) {
                    if (temp->array[j] != NULL) {
                        printf("%s %d\n", temp->array[j]->key, searchInTree(country, NULL, date1, date2, temp->array[j]->tree));
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
                    printf("%s %d\n", temp->array[j]->key, searchInTree(country, NULL, date1, date2, temp->array[j]->tree));
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
                    printf("%s %d \n", disease, countNullExitDates(temp->array[i]->tree));
                }
            }
            temp = temp->next;
        }
    }
    else {
        for (int j=0; j<diseaseHT->size; j++) {
            temp = diseaseHT->table[j];
            while (temp != NULL) {
                for (int i=0; i<diseaseHT->ptrNum; i++) {
                    if (temp->array[i] != NULL) {
                        printf("%s %d \n",temp->array[i]->key, countNullExitDates(temp->array[i]->tree));
                    }
               }
               temp = temp->next;
            }
        }
    }
}

void topkDiseases(HashTablePtr ht1, HashTablePtr ht2, datePtr date1, datePtr date2, int k, char* key)
{
    HTNodePtr temp = ht1->table[hashFunction(key)];
    treeNodePtr tree = NULL;
    BinaryHeapPtr heap = BHInit();

    while(temp != NULL){
        for (int i=0; i<ht1->ptrNum; i++) {
            if (!strcmp(temp->array[i]->key, key))
                tree = temp->array[i]->tree;           //found the tree of the hash node with given key
        }
        temp = temp->next;
    }

    for (int j=0; j<ht2->size; j++) {
        temp = ht2->table[j];
        while (temp != NULL) {
            for (int i=0; i<ht2->ptrNum; i++) {
                if (temp->array[i] != NULL) {
                    BHInsert(heap, temp->array[i]->key, searchInTree(key, temp->array[i]->key, date1, date2, tree));
                }
            }
            temp = temp->next;
        }
    }

    BHNodePtr bhnode = NULL;
    for (int i=0; i<k; i++) {
        bhnode = BHRemove(heap);
        printf("%s %d \n", bhnode->key, bhnode->volume);
        free(bhnode->key);
        free(bhnode);
    }
    BHDestroy(heap);
}

void topkCountries(HashTablePtr ht1, HashTablePtr ht2, datePtr date1, datePtr date2, int k, char* key)
{
    HTNodePtr temp = ht1->table[hashFunction(key)];
    treeNodePtr tree = NULL;
    BinaryHeapPtr heap = BHInit();

    while(temp != NULL){
        for (int i=0; i<ht1->ptrNum; i++) {
            if (!strcmp(temp->array[i]->key, key))
                tree = temp->array[i]->tree;           //found the tree of the hash node with given key
        }
        temp = temp->next;
    }

    for (int j=0; j<ht2->size; j++) {
        temp = ht2->table[j];
        while (temp != NULL) {
            for (int i=0; i<ht2->ptrNum; i++) {
                if (temp->array[i] != NULL) {
                    BHInsert(heap, temp->array[i]->key, searchInTree(temp->array[i]->key, key, date1, date2, tree));
                }
            }
            temp = temp->next;
        }
    }

    BHNodePtr bhnode = NULL;
    for (int i=0; i<k; i++) {
        bhnode = BHRemove(heap);
        printf("%s %d \n", bhnode->key, bhnode->volume);
        free(bhnode->key);
        free(bhnode);
    }
    BHDestroy(heap);
}