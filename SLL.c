#include <stdio.h>
#include <stdlib.h>

typedef struct node {
int data;
struct node *next;
} Node;

Node* createNode(int data){
Node* newNode = (Node*)malloc(sizeof(Node));
newNode->data = data;
newNode->next = NULL;
return newNode;
}

void insertAtTheBeggining(Node** head, int value) {
    Node* newNode = createNode(value);
    if (*head == NULL) {
        head = &newNode;
        return;
    }
    newNode->next = *head;
    *head = newNode;
}

void insertAtTheEnd(Node** head, int value) {
    Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void insertAtThePosition(Node** head, int value, int position) {
    Node* newNode = createNode(value);
    if (position == 0) {
        insertAtTheEnd(head, newNode->data);
        return;
    }
    Node* current = *head;
    for (int i=0; i<position-1; i++) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void displayList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(Node* head) {
    Node* current = head;
    Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

void removeAtEnd(Node** head) {
    if (*head == NULL) {
        printf("list is empty\n");
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    Node* current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
}

void removeAtPosition(Node** head, int position) {
    if (*head == NULL) {
        printf("list is empty\n");
        return;
    }

    if (position == 0) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    Node* current = *head;
    for (int i=0; i<position-1; i++) {
        current = current->next;
    }

    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
}

int main() {
    Node* head = NULL;

    insertAtTheEnd(&head, 10);
    insertAtTheEnd(&head, 20);
    insertAtTheBeggining(&head, 5);
    displayList(head);
    insertAtThePosition(&head, 15, 2);
    displayList(head);

    removeAtEnd(&head);
    displayList(head);

    removeAtPosition(&head, 1);
    displayList(head);

    freeList(head);
    return 0;
}