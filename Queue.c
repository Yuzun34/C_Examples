#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

void initQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

void enQueue (Queue* queue, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    }else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

void deQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue Underflow\n");
        return;
    }
    Node* temp = queue->front;
    queue->front = queue->front->next;
    free(temp);
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
}

int peek(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue Underflow\n");
        return -1;
    }
    return queue->front->data;
}

void display(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue Underflow\n");
        return;
    }
    Node* temp = queue->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Queue queue;
    initQueue(&queue);

    display(&queue);

    enQueue(&queue, 10);
    enQueue(&queue, 20);
    enQueue(&queue, 30);
    display(&queue);

    printf("Front element: %d\n", peek(&queue));

    deQueue(&queue);
    display(&queue);

    printf("Front element: %d\n", peek(&queue));

    return 0;
}