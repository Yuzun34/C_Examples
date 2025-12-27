#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int arr[5];
    int top;
} Stack;

void initStack(Stack *stack) {
    stack->top =  -1;
}

int isFull(Stack *stack) {
    return stack->top == 4;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
}

void pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return;
    }
    stack->top--;
}

int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->arr[stack->top];
}

void display(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}

int main() {
    Stack stack;
    initStack(&stack);

    display(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    push(&stack, 40);
    push(&stack, 50);
    push(&stack, 60);
    display(&stack);

    printf("Top element is %d\n", peek(&stack));

    pop(&stack);
    display(&stack);
    printf("Top element is %d\n", peek(&stack));

    return 0;
}

