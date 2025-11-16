//
// Created by Yusuf on 25.10.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//node yapisi
typedef struct Song {
    char name[50];
    struct Song* next;
    struct Song* prev;
} Song;

//fonksiyonlar
void addSongToEnd(Song** head, char* name);
void removeSong(Song** head, char* name);
void playNext(Song** current);
void playPrevious(Song** current);
void displayPlaylist(Song* head);
void freePlaylist(Song** head);

//Sona sarki ekleme
void addSongToEnd(Song** head, char* name) {
    //Yeni dugum ekler
    Song* newSong = (Song*)malloc(sizeof(Song));
    if (newSong == NULL) {
        printf("Bellek tahsisi basarisiz!\n");
        return;
    }

    strcpy(newSong->name, name);
    newSong->next = NULL;
    newSong->prev = NULL;

    if (*head == NULL) {
        *head = newSong;
        printf("'%s' oynatma listesine eklendi (ilk sarki).\n", name);
        return;
    }

    Song* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newSong;
    newSong->prev = temp;

    printf("'%s' oynatma listesine eklendi.\n", name);
}

//sarkiyi listeden silme
void removeSong(Song** head, char* name) {
    if (*head == NULL) {
        printf("Liste bos! Silinecek sarki yok.\n");
        return;
    }

    Song* temp = *head;

    //Sarki bul
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("'%s' oynatma listesinde bulunamadi.\n", name);
        return;
    }

    if (temp == *head) {
        *head = temp->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    }

    else {
        if (temp->prev != NULL) {
            temp->prev->next = temp->next;
        }
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
    }

    printf("'%s' oynatma listesinden silindi.\n", name);
    free(temp);
}

//Sonraki sarki
void playNext(Song** current) {
    if (*current == NULL) {
        printf("Liste bos! Oynatilacak sarki yok.\n");
        return;
    }

    if ((*current)->next == NULL) {
        printf("Son sarkidasiniz. Bir sonraki sarki yok.\n");
        return;
    }

    *current = (*current)->next;
    printf("Sonraki sarki oynatiliyor: '%s'\n", (*current)->name);
}

//Onceki sarki
void playPrevious(Song** current) {
    if (*current == NULL) {
        printf("Liste bos! Oynatilacak sarki yok.\n");
        return;
    }

    if ((*current)->prev == NULL) {
        printf("Ilk sarkidasiniz. Bir onceki sarki yok.\n");
        return;
    }

    *current = (*current)->prev;
    printf("Onceki sarki oynatiliyor: '%s'\n", (*current)->name);
}

//Calma listesini gosterme
void displayPlaylist(Song* head) {
    if (head == NULL) {
        printf("\n=== OYNATMA LISTESI ===\n");
        printf("Liste bos!\n");
        printf("======================\n\n");
        return;
    }

    printf("\n=== OYNATMA LISTESI ===\n");
    Song* temp = head;
    int index = 1;

    while (temp != NULL) {
        printf("%d. %s\n", index++, temp->name);
        temp = temp->next;
    }
    printf("======================\n\n");
}

//Free fonksiyonu
void freePlaylist(Song** head) {
    Song* current = *head;
    Song* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

int main() {
    Song* playlist = NULL;
    Song* currentSong = NULL;
    int choice;
    char songName[50];

    while (1) {
        printf("=== MENU ===\n");
        printf("%-5s %-10s\n", "1.", "Sarki Ekle");
        printf("%-5s %-10s\n", "2.", "Sarki Sil");
        printf("%-5s %-10s\n", "3.", "Sonraki Sarki");
        printf("%-5s %-10s\n", "4.", "Onceki Sarki");
        printf("%-5s %-10s\n", "5.", "Oynatma Listesini Goster");
        printf("%-5s %-10s\n", "6.", "Mevcut Calan Sarki");
        printf("%-5s %-10s\n", "7.", "Ilk Sarkiyi Oynat");
        printf("%-5s %-10s\n", "0.", "Cikis");
        printf("Seciminiz: ");

        if (scanf("%d", &choice) != 1) {
            printf("Gecersiz giris!\n");
            while (getchar() != '\n');
        }
        getchar();

        switch (choice) {
            case 1:
                printf("Eklenecek sarki adini girin: ");
                fgets(songName, sizeof(songName), stdin);
                songName[strcspn(songName, "\n")] = 0;

                if (strlen(songName) == 0) {
                    printf("Sarki adi bos olamaz!\n");
                    break;
                }

                addSongToEnd(&playlist, songName);

                if (currentSong == NULL) {
                    currentSong = playlist;
                }
                break;

            case 2:
                printf("Silinecek sarki adini giriniz: ");
                fgets(songName, sizeof(songName), stdin);
                songName[strcspn(songName, "\n")] = 0;

                if (strlen(songName) == 0) {
                    printf("Sarki adi bos birakilamaz!\n");
                    break;
                }

                if (currentSong != NULL && strcmp(currentSong->name, songName) == 0) {
                    Song* temp = currentSong;
                    if (currentSong->next != NULL) {
                        currentSong = currentSong->next;
                    } else if (currentSong->prev != NULL) {
                        currentSong = currentSong->prev;
                    } else {
                        currentSong = NULL;
                    }
                }

                removeSong(&playlist, songName);
                break;

            case 3:
                playNext(&currentSong);
                break;

            case 4:
                playPrevious(&currentSong);
                break;

            case 5:
                displayPlaylist(playlist);
                break;

            case 6:
                if (currentSong == NULL) {
                    printf("Sarki Calmamakta.\n");
                } else {
                    printf("Suanda calan: '%s'\n", currentSong->name);
                }
                break;

            case 7:
                if (playlist == NULL) {
                    printf("Liste bos!\n");
                } else {
                    currentSong = playlist;
                    printf("Ilk sarki oynatiliyor: '%s'\n", currentSong->name);
                }
                break;

            case 0:
                printf("\nCikis yapiliyor...\n");
                printf("Bellek temizleniyor...\n");
                freePlaylist(&playlist);
                printf("Muzik calar kapatildi. Gule gule!\n");
                return 0;

            default:
                printf("Gecersiz secim! Lutfen 0-7 arasi bir deger giriniz.\n");
        }
    }

    return 0;
}