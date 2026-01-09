#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int heap[MAX];
int size = 0;

void insert(int value) {
    int i = size;
    heap[size++] = value;

    // Yukarı doğru düzenleme (heapify up)
    while (i != 0 && heap[(i - 1) / 2] > heap[i]) {
        int temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

int extractMin() {
    if (size <= 0)
        return -1;

    int min = heap[0];
    heap[0] = heap[--size];

    // Aşağı doğru düzenleme (heapify down)
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < size && heap[left] < heap[smallest])
            smallest = left;

        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != i) {
            int temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }
    return min;
}

int main() {
    int values[] = {5, 3, 8, 1, 2, 7};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        insert(values[i]);
    }
    printf("Extracted elements in order:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", extractMin());
    }
    printf("\n");
    return 0;
}