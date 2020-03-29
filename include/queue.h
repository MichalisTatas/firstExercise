#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct QueueNode
{
    int size;
    char* name;
    struct QueueNode* next;
} QueueNode;
typedef QueueNode* QueueNodePtr;

typedef struct Queue
{
    QueueNodePtr front;
    QueueNodePtr rear;
} Queue;
typedef Queue* QueuePtr;

void QInit(QueuePtr);
void QInsert(QueuePtr, QueueNodePtr);
QueueNodePtr QRemove(QueuePtr);