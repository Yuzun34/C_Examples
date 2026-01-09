//
// Created by Yusuf on 9.01.2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct avlNode {
    int value;
    struct avlNode *left, *right;
    int height;
} AVL;

int height(AVL *node) {
    return node ? node->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

AVL *newAVLNode(int value) {
    AVL *node = (AVL *)malloc(sizeof(AVL));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

AVL* rotateRight(AVL *node) {
    AVL *newRoot = node->left;
    AVL *subTree = newRoot->right;

    newRoot->right = node;
    node->left = subTree;

    node->height = 1 +  max(height(newRoot->left), height(newRoot->right));
    newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));
    return newRoot;
}

AVL* rotateLeft(AVL *node) {
    AVL* newRoot = node->right;
    AVL* subTree = newRoot->left;

    newRoot->left = node;
    node->right = subTree;

    node->height = 1 + max(height(newRoot->left), height(newRoot->right));
    newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));
    return newRoot;
}

int getBalance(AVL *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

AVL* balance(AVL *node) {
    if (node == NULL) {
        return NULL;
    }

    int balanceFactor = getBalance(node);

    node->height = 1 + max(height(node->left), height(node->right));

    // Left-Left (LL)
    if (balanceFactor > 1 && getBalance(node->left) >= 0 ) {
        return rotateRight(node);
    }

    // Left-Right (LR)
    if (balanceFactor > 1 && getBalance(node->right) < 0 ) {
        node->right = rotateLeft(node->right);
        return rotateRight(node);
    }

    // Right-Right (RR)
    if (balanceFactor < -1 && getBalance(node->left) <= 0 ) {
        return rotateLeft(node);
    }

    // Right-Left (RL)
    if (balanceFactor < -1 && getBalance(node->right) > 0 ) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

AVL* insert(AVL *node, int value) {
    if (node == NULL) {
        return newAVLNode(value);
    }

    if (value < node->value) {
        node->left = insert(node->left, value);
    }else if (value > node->value) {
        node->right = insert(node->right, value);
    }else {
        return node;
    }

    return balance(node);
}

void preOrder(AVL *root) {
    if (root != NULL) {
        printf("%d ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(AVL *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->value);
        inOrder(root->right);
    }
}

void postOrder(AVL *root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->value);
    }
}

void printAVL(AVL *node) {
    if (node != NULL) {
        printf("Node: %d, Height: %d, Balance: %d\n", node->value, node->height, getBalance(node));
        printAVL(node->left);
        printAVL(node->right);
    }
}

int main() {
    AVL *root = NULL;
    int values[] = {30, 20, 40, 10, 25, 35, 50, 5};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    printf("Pre-order Traversal: ");
    preOrder(root);
    printf("\n");

    printf("In-order Traversal: ");
    inOrder(root);
    printf("\n");

    printf("Post-order Traversal: ");
    postOrder(root);
    printf("\n");

    printf("\nAVL Tree Structure:\n");
    printAVL(root);


    return 0;
}


