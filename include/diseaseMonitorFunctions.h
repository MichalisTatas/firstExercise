#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"
#include "avlTree.h"
#include "hashTable.h"
#include <wordexp.h>


void topkDiseases(HashTablePtr, HashTablePtr, datePtr, datePtr, int, char*);
int searchInTree(char*, char*, datePtr, datePtr, treeNodePtr);
void statsFrequency(char*, char*, datePtr, datePtr, HashTablePtr);
int countNullExitDates(treeNodePtr);
void printCurrPatients(char*, HashTablePtr);
