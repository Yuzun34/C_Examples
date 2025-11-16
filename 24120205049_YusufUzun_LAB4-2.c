//
// Created by Yusuf on 25.10.2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
    char text[50];
    struct Word* next;
} Word;

//fonksiyonlar
void pushWord(Word** top, char* text);
void popWord(Word** top);
void showWords(Word* top);
void freeStack(Word** top);
int isEmpty(Word* top);

//kelime ekleme
void pushWord(Word** top, char* text) {
    // Yeni dugum olustur
    Word* newWord = (Word*)malloc(sizeof(Word));
    if (newWord == NULL) {
        printf("Bellek tahsisi basarisiz!\n");
        return;
    }

    strcpy(newWord->text, text);

    // Yeni dugumu tepeye ekle
    newWord->next = *top;
    *top = newWord;

    printf("'%s' eklendi.\n", text);
}

//kelime cikarma
void popWord(Word** top) {
    // Stack bos mu kontrol et
    if (*top == NULL) {
        printf("Stack bos!\n");
        return;
    }

    Word* temp = *top;
    *top = (*top)->next;

    printf("'%s' geri alindi.\n", temp->text);

    free(temp);
}

//tum kelimeleri goster
void showWords(Word* top) {
    if (top == NULL) {
        printf("\nMetin: (bos)\n\n");
        return;
    }

    int count = 0;
    Word* temp = top;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    char** words = (char**)malloc(count * sizeof(char*));
    if (words == NULL) {
        printf("Bellek tahsisi basarisiz!\n");
        return;
    }

    temp = top;
    for (int i = count - 1; i >= 0; i--) {
        words[i] = temp->text;
        temp = temp->next;
    }

    // Kelimeleri yazdir
    printf("\nMetin: ");
    for (int i = 0; i < count; i++) {
        printf("%s", words[i]);
        if (i < count - 1) {
            printf(" ");
        }
    }
    printf("\n\n");

    free(words);
}

int isEmpty(Word* top) {
    return top == NULL;
}

//Temizleme
void freeStack(Word** top) {
    Word* current = *top;
    Word* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *top = NULL;
}

// Stack'teki eleman sayisini dondurur
int getStackSize(Word* top) {
    int count = 0;
    Word* temp = top;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

// Stack yapisini goster
void showStackStructure(Word* top) {
    if (top == NULL) {
        printf("\nStack Yapisi: [BOS]\n\n");
        return;
    }

    printf("\nStack Yapisi (Tepeden Alta):\n");

    Word* temp = top;
    int index = 1;

    while (temp != NULL) {
        printf("%d. %s", index++, temp->text);
        if (temp == top) {
            printf(" <- TOP");
        }
        printf("\n");
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Word* textStack = NULL;
    char choice[10];
    char word[50];


    printf("\n========== MENU ==========\n");
    printf("%-5s - %-20s\n", "Kelime Ekle", "add");
    printf("%-5s - %-20s\n", "Geri Al", "undo");
    printf("%-5s - %-20s\n", "Metini Goster", "show");
    printf("%-5s - %-20s\n", "Stacki Goster", "stack");
    printf("%-5s - %-20s\n", "Metini Temizle", "clear");
    printf("%-5s - %-20s\n", "Cikis", "exit");
    printf("==========================\n");

    while (1) {
        printf("> ");

        if (scanf("%s", choice) != 1) {
            printf("Gecersiz giris!\n");
            while (getchar() != '\n');
            continue;
        }

        if (strcmp(choice, "add") == 0) {

            if (scanf("%s", word) != 1) {
                printf("Kelime girilmedi!\n");
                while (getchar() != '\n');
                continue;
            }

            if (strlen(word) == 0) {
                printf("Bos kelime eklenemez!\n");
                continue;
            }

            pushWord(&textStack, word);

        } else if (strcmp(choice, "undo") == 0) {
            popWord(&textStack);

        } else if (strcmp(choice, "show") == 0) {
            showWords(textStack);

        } else if (strcmp(choice, "stack") == 0) {
            showStackStructure(textStack);

        } else if (strcmp(choice, "clear") == 0) {
            if (isEmpty(textStack)) {
                printf("Stack zaten bos.\n");
            } else {
                int size = getStackSize(textStack);
                freeStack(&textStack);
                printf("%d kelime temizlendi.\n", size);
            }

        } else if (strcmp(choice, "exit") == 0) {
            printf("\nCikis yapiliyor...\n");
            freeStack(&textStack);
            printf("Bellek temizlendi. Cikis yapiliyor.\n");
            break;

        } else {
            printf("Bilinmeyen komut: '%s'\n", choice);
            printf("Yardim icin: add, undo, show, stack, clear, exit\n");
        }

        while (getchar() != '\n');
    }

    return 0;
}