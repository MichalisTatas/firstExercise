#include "../include/queue.h"

void QInit(QueuePtr Q)
{
    Q->front = NULL;
    Q->rear = NULL;
}

void QInsert(QueuePtr Q, QueueNodePtr node)
{
    QueueNodePtr temp = malloc(sizeof(QueueNode));
    temp->name = malloc(strlen(node->name) + 1);
    if (temp == NULL || temp->name == NULL) {
        printf("system has no more space\n");
        return ;
    }

    strcpy(temp->name, node->name);
    temp->size = node->size;

    temp->next = NULL;
    if (Q->rear == NULL) {
        Q->front = temp;
        Q->rear = temp;
    }
    else {
        Q->rear->next = temp;
        Q->rear = temp;
    }
}

QueueNodePtr QRemove(QueuePtr Q)
{
    QueueNodePtr temp;

    if(Q->front == NULL) {
        printf ("trying to remove from empty q \n");
        return NULL;
    }
    else {
        temp = Q->front;
        Q->front = temp->next;
        if (Q->front == NULL)
            Q->rear = NULL;
        return temp;
    }
}
