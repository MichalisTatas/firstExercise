#include "../include/avlTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void preorder(treeNodePtr node)
{
    if (node != NULL)
    {
        printf ("%s\n", node->patient->recordID );//entryDate->day, node->patient->entryDate->month, node->patient->entryDate->year);
        preorder(node->left);
        preorder(node->right);
    }
}

bool existInTree(treeNodePtr tree, patientPtr patient)
{
    treeNodePtr temp = tree;
    while (temp != NULL) {
        if (compareDates(tree->patient->entryDate, patient->entryDate) == 1)
            temp = temp->left;
        else if (compareDates(tree->patient->entryDate, patient->entryDate) == -1)
            temp = temp->right;
        else if (strcmp(tree->patient->recordID, patient->recordID) == 0)
            return true;
    }

    return false;
}

treeNodePtr createNode(patientPtr patient)
{
    treeNodePtr node = malloc(sizeof(treeNode));
    node->patient = patient;
    node->right = NULL;
    node->left = NULL;
    node->height = 1;
    return node;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int getHeight(treeNodePtr node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

treeNodePtr rightRotation(treeNodePtr node)
{
    treeNodePtr nodeLeft = node->left;
    treeNodePtr right = nodeLeft->right;
    
    nodeLeft->right = node;
    node->left = right;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    nodeLeft->height = 1 + max(getHeight(nodeLeft->left), getHeight(nodeLeft->right));

    return nodeLeft;
}

treeNodePtr leftRotation(treeNodePtr node)
{
    treeNodePtr nodeRight = node->right;
    treeNodePtr left = nodeRight->left;

    nodeRight->left = node;
    node->right = left;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    nodeRight->height = 1 + max(getHeight(nodeRight->left), getHeight(nodeRight->right));

    return nodeRight;
}

int getBalance(treeNodePtr node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

treeNodePtr AVLInsert(treeNodePtr tree, patientPtr patient)
{
    if (tree == NULL)
        return (createNode(patient));
    if (compareDates(patient->entryDate, tree->patient->entryDate) == 1)
        tree->right = AVLInsert(tree->right, patient);
    else if (compareDates(patient->entryDate, tree->patient->entryDate) == -1)
        tree->left = AVLInsert(tree->left, patient);
    else
        return tree;                // if equal dont insert into tree

    tree->height = 1 + max(getHeight(tree->left), getHeight(tree->right));

// DO I NEED TO CHECK IF TREE IS NULL ?????

    //right right
    if (getHeight(tree->left) - getHeight(tree->right) < -1 && compareDates(tree->right->patient->entryDate, patient->entryDate) == -1)
        return leftRotation(tree);

    // //right left
    if (getHeight(tree->left) - getHeight(tree->right) < -1 && compareDates(tree->right->patient->entryDate, patient->entryDate) == 1) {
        tree->right = rightRotation(tree->right);
        return leftRotation(tree);
    }
    

    // //left right
    if (getHeight(tree->left) - getHeight(tree->right) > 1 && compareDates(tree->left->patient->entryDate, patient->entryDate) == -1) {
        tree->left = leftRotation(tree->left);
        return rightRotation(tree);
    }

    // //left left
    if (getHeight(tree->left) - getHeight(tree->right) > 1 && compareDates(tree->left->patient->entryDate, patient->entryDate) == 1)
        return rightRotation(tree);

    return tree;
}


void AVLDestroy(treeNodePtr node)
{
    if (node != NULL)
    {
        AVLDestroy(node->left);
        AVLDestroy(node->right);
        free(node);
    }
}