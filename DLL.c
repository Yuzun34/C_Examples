// DLL.c
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} Node;

static Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertAtBeginning(Node** headRef, int data) {
    Node* newNode = createNode(data);
    newNode->next = *headRef;
    if (*headRef) {
        (*headRef)->prev = newNode;
    }
    *headRef = newNode;
}

void insertAtEnd(Node** headRef, int data) {
    Node* newNode = createNode(data);
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    Node* current = *headRef;
    while (current->next) current = current->next;
    current->next = newNode;
    newNode->prev = current;
}

void insertAtPosition(Node** headRef, int data, int position) {
    if (position <= 0 || *headRef == NULL) {
        insertAtBeginning(headRef, data);
        return;
    }
    Node* current = *headRef;
    for (int i = 0; i < position - 1 && current->next; i++) {
        current = current->next;
    }
    Node* newNode = createNode(data);
    newNode->next = current->next;
    newNode->prev = current;
    if (current->next) current->next->prev = newNode;
    current->next = newNode;
}

void deleteAtBeginning(Node** headRef) {
    if (*headRef == NULL) {
        printf("The list is empty\n");
        return;
    }
    Node* temp = *headRef;
    *headRef = temp->next;
    if (*headRef) (*headRef)->prev = NULL;
    free(temp);
}

void deleteAtEnd(Node** headRef) {
    if (*headRef == NULL) {
        printf("The list is empty\n");
        return;
    }
    if ((*headRef)->next == NULL) {
        free(*headRef);
        *headRef = NULL;
        return;
    }
    Node* current = *headRef;
    while (current->next) current = current->next;
    current->prev->next = NULL;
    free(current);
}

void deleteAtPosition(Node** headRef, int position) {
    if (*headRef == NULL) {
        printf("The list is empty\n");
        return;
    }
    if (position <= 0) {
        deleteAtBeginning(headRef);
        return;
    }
    Node* current = *headRef;
    for (int i = 0; i < position && current; i++) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Invalid position\n");
        return;
    }
    if (current->prev) current->prev->next = current->next;
    else *headRef = current->next;
    if (current->next) current->next->prev = current->prev;
    free(current);
}

void displayList(Node* head) {
    if (head == NULL) {
        printf("The list is empty\n");
        return;
    }
    Node* current = head;
    while (current) {
        printf("%d <-> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(Node** headRef) {
    Node* current = *headRef;
    while (current) {
        Node* nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *headRef = NULL;
}

int main(void) {
    Node* head = NULL;

    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    displayList(head);

    insertAtBeginning(&head, 5);
    displayList(head);

    insertAtPosition(&head, 15, 2);
    displayList(head);

    deleteAtBeginning(&head);
    displayList(head);

    deleteAtEnd(&head);
    displayList(head);

    deleteAtPosition(&head, 1);
    displayList(head);

    freeList(&head);
    return 0;
}