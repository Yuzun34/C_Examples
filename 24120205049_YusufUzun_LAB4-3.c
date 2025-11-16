#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//node yapisi
typedef struct PrintJob {
    char fileName[50];
    struct PrintJob* next;
} PrintJob;

//kuyruk yapisi
typedef struct Queue {
    PrintJob* front;
    PrintJob* rear;
} Queue;

//fonksiyonlar
void enqueuePrintJob(Queue* q, char* fileName);
void processNextJob(Queue* q);
void showQueue(Queue q);
void initQueue(Queue* q);
int isEmpty(Queue q);

//kuyruk
void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

//kuyruk bos mu
int isEmpty(Queue q) {
    return (q.front == NULL);
}

//yeni dosya ekleme
void enqueuePrintJob(Queue* q, char* fileName) {
    PrintJob* newJob = (PrintJob*)malloc(sizeof(PrintJob));
    
    if (newJob == NULL) {
        printf("Bellek tahsisi basarisiz!\n");
        return;
    }
    
    strcpy(newJob->fileName, fileName);
    newJob->next = NULL;
    
    if (isEmpty(*q)) {
        q->front = newJob;
        q->rear = newJob;
    } else {
        q->rear->next = newJob;
        q->rear = newJob;
    }
    
    printf("'%s' dosyasi kuyruga eklendi.\n", fileName);
}

//sonraki is
void processNextJob(Queue* q) {
    if (isEmpty(*q)) {
        printf("\nKuyruk bos! Yazdirilacak dosya yok.\n");
        return;
    }
    
    PrintJob* temp = q->front;
    
    printf("\nYazdiriliyor: '%s'\n", temp->fileName);
    printf("Yazdirma islemi tamamlandi!\n");
    
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
}

//kuruk goruntuleme
void showQueue(Queue q) {
    if (isEmpty(q)) {
        printf("\nKuyruk bos!\n");
        return;
    }
    
    printf("\n========== KUYRUK ==========\n");
    PrintJob* current = q.front;
    int position = 1;
    
    while (current != NULL) {
        printf("%d. %s\n", position, current->fileName);
        current = current->next;
        position++;
    }
    printf("====================================\n");
}

//temizle
void clearQueue(Queue* q) {
    while (!isEmpty(*q)) {
        PrintJob* temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
}

int main() {
    Queue printerQueue;
    initQueue(&printerQueue);
    
    int choice;
    char fileName[50];
    
    while (1) {
        printf("\n==== KUYRUK SISTEMI ====\n");
        printf("1. Yeni dosya ekle\n");
        printf("2. Yazdir\n");
        printf("3. Kuyrugu goster\n");
        printf("4. Cikis\n");
        printf("========================\n");
        printf("Seciminiz: ");
        
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                printf("Dosya adini girin: ");
                fgets(fileName, sizeof(fileName), stdin);
                fileName[strcspn(fileName, "\n")] = '\0';
                
                if (strlen(fileName) > 0) {
                    enqueuePrintJob(&printerQueue, fileName);
                } else {
                    printf("Dosya ismi bos birakilamaz!\n");
                }
                break;
                
            case 2:
                processNextJob(&printerQueue);
                break;
                
            case 3:
                showQueue(printerQueue);
                break;
                
            case 4:
                printf("\nProgram sonlandiriliyor...\n");
                clearQueue(&printerQueue);
                return 0;
                
            default:
                printf("Gecersiz secim!\n");
        }
    }
    
    return 0;
}