//
// Created by Yusuf on 3.11.2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int patientCount = 0;

//Hasta tanimi
typedef struct Patient {
    int number;
    char name[50];
    char situation[50];
    struct Patient* next;
} Patient;

//Kuyruk tanimi
typedef struct Queue {
    Patient* front;
    Patient* rear;
    int count;
}Queue;

//Yigin tanimi
typedef struct Stack {
    Patient* front;
    int count;
}Stack;

//Liste tanimi
typedef struct List {
    Patient* front;
    int count;
}List;

//Yeni Hasta tanimi
Patient* newPatient(char* name, char* Situation) {
    Patient* new_p = (Patient*)malloc(sizeof(Patient));
    if (new_p == NULL) {
        printf("Not enough space\n");
        return NULL;
    }
    new_p->number = patientCount++;
    strcpy(new_p->name, name);
    strcpy(new_p->situation,Situation);
    new_p->next = NULL;
    return new_p;
}

//Kuyruk olusturma
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
    return q;
}

//Kuyruga hasta ekleme
void enqueue(Queue* q, char* name) {
    Patient* new_p = newPatient(name,"Waiting");
    if (q->rear == NULL) {
        q->front = new_p;
        q->rear = new_p;
    } else {
        q->rear->next = new_p;
        q->rear = new_p;
    }
    q->count++;
    printf("\nPatient %s with number %d added to the queue.\n", name, new_p->number);
}

//Kuyruktan hasta cikarma
Patient* dequeue(Queue* q) {
    if (q->front == NULL) {
        printf("\nQueue is empty\n");
        return NULL;
    }
    Patient* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    temp->next = NULL;
    q->count--;
    printf("\nPatient %s with number %d removed from the queue.\n", temp->name, temp->number);
    return temp;
}

//Kuyrugu gosterme
void displayQueue(Queue* q) {
    if (q->front == NULL) {
        printf("\nQueue is empty\n");
        return;
    }
    Patient* temp = q->front;
    printf("\nPatients in the queue:\n");
    while (temp != NULL) {
        printf("Number: %d, Name: %s, Situation: %s\n", temp->number, temp->name, temp->situation);
        temp = temp->next;
    }
    printf("\nTotal number of patients waiting in queue: %d\n", q->count);
}

//Stack olusturma
Stack* createStack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->front = NULL;
    s->count = 0;
    return s;
}

//Stacke hasta ekleme
void addStack(Stack* s, Patient* p) {
    strcpy(p->situation,"Treated");
    p->next = s->front;
    s->front = p;
    s->count++;
    printf("\nPatient %s with number %d added to the stack.\n", p->name, p->number);
}

//Stackten hasta cikarma
Patient* popStack(Stack* s) {
    if (s->front == NULL) {
        printf("\nThere are no patients in the examination room.\n");
        return NULL;
    }
    Patient* temp = s->front;
    s->front = s->front->next;
    temp->next = NULL;
    s->count--;
    printf("\nPatient %s with number %d removed from the stack.\n", temp->name, temp->number);
    return temp;
}

//Muayene odasindaki hastalari gosterme
void displayStack(Stack* s) {
    if (s->front == NULL) {
        printf("\nThere are no patients in the examination room.\n");
        return;
    }
    Patient* temp = s->front;
    printf("\nPatients in the examination room:\n");
    while (temp != NULL) {
        printf("Number: %d, Name: %s, Situation: %s\n", temp->number, temp->name, temp->situation);
        temp = temp->next;
    }
    printf("\nTotal number of patients in the examination room: %d\n", s->count);
}

//Liste olusturma
List* createList() {
    List* l = (List*)malloc(sizeof(List));
    l->front = NULL;
    l->count = 0;
    return l;
}

// Listeye hasta ekle (Tamamlanan hastalar)
void addList(List*l, Patient* p) {
    p->next = l->front;
    l->front = p;
    l->count++;
    printf("\nPatient %s with number %d added to the completed list.\n", p->name, p->number);
}

//Tamamlanan hastalari gosterme
void displayList(List* l) {
    printf("\n========== COMPLETED PATIENTS ==========\n");
    if (l->front == NULL) {
        printf("\nThere are no patients in the completed list.\n");
        return;
    }
    Patient* temp = l->front;
    int count = 0;
    while (temp != NULL) {
        printf("Number: %d | Name: %s | Situation: %s\n", temp->number, temp->name, temp->situation);
        temp = temp->next;
        count++;
    }
    printf("\nTotal number of completed patients: %d\n", count);
}

//Hastayi kuyruga ekle
void savePatient(Queue* q, char* name) {
    enqueue(q, name);
}

//Hastayi muayeneye al
void examinePatient(Queue* q, Stack* s) {
    Patient* p = dequeue(q);
    if (p != NULL) {
        addStack(s, p);
    }
}

// Muayeneyi tamamla
void completeExamination(Stack* s, List* l) {
    Patient* p = popStack(s);
    if (p != NULL) {
        addList(l, p);
    }
}

//Tum sistem goster
void displaySystem(Queue* q, Stack* s, List* l) {
    printf("\n=========== HOSPITAL SYSTEM ===========\n");
    displayQueue(q);
    displayStack(s);
    displayList(l);
    printf("\n========================================\n");
}

//Menu goster
void showMenu() {
    printf("\n=== HOSPITAL PATIENT TRACKING SYSTEM - MENU ===\n");
    printf("1. Register new patient (Add to waiting queue)\n");
    printf("2. Take patient to examination\n");
    printf("3. Complete examination\n");
    printf("4. Show waiting patients\n");
    printf("5. Show patients in examination room\n");
    printf("6. Show completed patients (Registry)\n");
    printf("7. Show entire system status\n");
    printf("0. Exit\n");
    printf("===============================================\n");
    printf("Your choice: ");
}

//Kuyruk temizleme
void cleanupQueue(Queue* q) {
    Patient* current = q->front;
    Patient* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(q);
}

//Stack temizleme
void cleanupStack(Stack* s) {
    Patient* current = s->front;
    Patient* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(s);
}

//Liste temizleme
void cleanupList(List* l) {
    Patient* current = l->front;
    Patient* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(l);
}

int main() {
    Queue* waitingQueue = createQueue();
    Stack* examinationStack = createStack();
    List* completedList = createList();

    int choice;
    char name[50];

    printf("\n================================================\n");
    printf("  HOSPITAL PATIENT TRACKING SYSTEM - WELCOME   \n");
    printf("================================================\n");

    while (1) {
        showMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter the name of the patient: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                savePatient(waitingQueue, name);
                break;
            case 2:
                examinePatient(waitingQueue, examinationStack);
                break;
            case 3:
                completeExamination(examinationStack, completedList);
                break;
            case 4:
                displayQueue(waitingQueue);
                break;
            case 5:
                displayStack(examinationStack);
                break;
            case 6:
                displayList(completedList);
                break;
            case 7:
                displaySystem(waitingQueue, examinationStack, completedList);
                break;
            case 0:
                printf("Exiting the system. Goodbye!\n");
                cleanupQueue(waitingQueue);
                cleanupStack(examinationStack);
                cleanupList(completedList);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    return 0;
}


