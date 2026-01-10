//
// Created by Yusuf on 10.01.2026.
//
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 100
#define EMPTY -1
#define DELETED -2

int hashTable[TABLE_SIZE];

void initalizeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = EMPTY;
    }
    printf("Hash Table Initialized(Size: %d)\n", TABLE_SIZE);
}

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

void displayTable() {
    printf("Hash Table:\n");
    for (int i = 0; i< TABLE_SIZE; i++) {
        printf("%d ", hashTable[i]);

        if (hashTable[i] == EMPTY) {
            printf("EMPTY\n");
        } else if (hashTable[i] == DELETED) {
            printf("DELETED\n");
        } else {
            printf("%d\n", hashTable[i]);
        }
    }
    printf("\n");
}

bool insert(int key) {
    int index = hashFunction(key);
    int originalIndex = hashTable[index];
    int probeCount = 0;

    printf("Insert %d into the table\n", key);

    // Linear Probing
    while (hashTable[index] != EMPTY && hashTable[index] != DELETED) {
        if (hashTable[index] == key) {
            printf("Key already exists\n");
            return false;
        }

        printf("Collision at index %d for key %d\n", index, key);

        index = (index + 1) % TABLE_SIZE;
        probeCount++;

        printf("  New index: (%d + 1) mod %d = %d\n",
                       index - 1 < 0 ? TABLE_SIZE - 1 : index - 1,
                       TABLE_SIZE, index);

        //Full Table
        if (index == originalIndex) {
            printf("ERROR: Hash Table is full\n");
            return false;
        }
    }
    hashTable[index] = key;
    printf("Key %d inserted at index %d with %d probes\n", key, index, probeCount);
    return true;
}

int search(int key) {
    int index = hashFunction(key);
    int originalIndex = hashTable[index];
    int probeCount = 0;

    printf("Start index: %d for searching key %d\n", index, key);

    while (hashTable[index] != EMPTY) {
        if (hashTable[index] == key) {
            printf("Key found at index %d with %d probes\n", index, probeCount);
            return index;
        }

        index = (index + 1) % TABLE_SIZE;
        probeCount++;

        if (index == originalIndex) {
            break;
        }
    }
    printf("Key %d not found after %d probes\n", key, probeCount);
    return -1;
}

bool delete(int key){
    int index = search(key);

    if (index == -1) {
        printf("Key %d not found, cannot delete\n", key);
        return false;
    }

    hashTable[index] = DELETED;
    printf("Key %d deleted from index %d\n", key, index);
    return true;
}

void printMenu() {
    printf("Menu:\n");
    printf("1. Insert\n");
    printf("2. Search\n");
    printf("3. Delete\n");
    printf("4. Display Table\n");
    printf("5. Exit\n");
}

int main() {
    initalizeTable();
    int choice, key;

    while (true) {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                search(key);
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                delete(key);
                break;
            case 4:
                displayTable();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}