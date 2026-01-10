//
// Created by Yusuf on 9.01.2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
int heap[MAX];
int heap_size = 0;

void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(int i) {
    while (i > 0) {
        int parent = (i-1) / 2;

        if (heap[parent] < heap[i]) {
            swap(&heap[parent], &heap[i]);
            i= parent;
        }else {
            break;
        }
    }
}

void heapifyDown(int i) {
    while (1) {
        int left = 2*i + 1;
        int right = 2*i +1;
        int smallest = i;

        if (left < heap_size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < heap_size && heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            swap(&heap[i],&heap[smallest]);
            heapifyDown(smallest);
        }
    }
}

void insert(int value) {
    heap[heap_size] = value;
    heapifyUp(heap_size);
    heap_size++;
}

int extractMin() {
    if (heap_size == 0) {
        printf("Heap is empty\n");
        return -1;
    }
    int min = heap[0];
    heap[0] = heap[heap_size - 1];
    heap_size--;
    heapifyDown(0);
    return min;
}

void printHeap() {
    for (int i = 0; i < heap_size; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

int main() {
    printHeap();
    insert(10);
    insert(20);
    insert(5);
    insert(15);
    insert(30);

    printf("Heap elements: ");
    printHeap();

    printf("Extracted min: %d\n", extractMin());
    printf("Heap after extraction: ");
    printHeap();

    return 0;
}


