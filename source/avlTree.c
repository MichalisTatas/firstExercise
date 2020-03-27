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
    node->key = malloc(strlen(key) + 1);
    strcpy(node->key, key);
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

void preorder(treeNodePtr node)
{
    if (node != NULL)
    {
        printf ("%d-%d-%d\n", node->patient->entryDate->day, node->patient->entryDate->month, node->patient->entryDate->year);
        preorder(node->left);
        preorder(node->right);
    }
}

void AVLDestroy(treeNodePtr node)
{
    if (node != NULL)
    {
        AVLDestroy(node->left);
        AVLDestroy(node->right);
        free(node->key);
        free(node);
    }
}