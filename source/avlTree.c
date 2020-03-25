#include "../include/avlTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

treeNodePtr createNode(patientPtr patient, char* key)
{
    treeNodePtr node = malloc(sizeof(treeNode));
    node->patient = patient;
    node->right = NULL;
    node->left = NULL;
    node->height = 1;
    strcpy(node->key, key);
}

treeNodePtr AVLInsert(treeNodePtr tree, patientPtr patient, char* key)
{
    if (tree == NULL)
        return (createNode(patient, key));
    if (compareDates(patient->entryDate, tree->patient->entryDate) == 1)
        tree->right = AVLInsert(tree->right, patient, key);
    else if (compareDates(patient->entryDate, tree->patient->entryDate) == -1)
        tree->left = AVLInsert(tree->left, patient, key);
    else
        return tree;                // if equal dont insert into tree

    tree->height = 1 + max(tree->left->height, tree->right->height);

    //right right
    if ((tree->left->height - tree->right->height) < -1 && compareDates(tree->right->patient->entryDate, patient->entryDate) == -1)
        return leftRotation(tree);

    //right left
    if ((tree->left->height - tree->right->height) < -1 && compareDates(tree->right->patient->entryDate, patient->entryDate) == 1) {
        tree->right = rightRotation(tree->right);
        return leftRotation(tree);
    }
    

    //left right
    if ((tree->left->height - tree->right->height) > 1 && compareDates(tree->right->patient->entryDate, patient->entryDate) == -1) {
        tree->left = leftRotation(tree->left);
        return rightRotation(tree);
    }

    //left left
    if ((tree->left->height - tree->right->height) > 1 && compareDates(tree->right->patient->entryDate, patient->entryDate) == 1)
        return rightRotation(tree);
}