#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;


Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}


Node* copyTreePreorder(Node* root) {
    if (root == NULL) {
        return NULL;
    }

    Node* newNode = createNode(root->data);
    newNode->left = copyTreePreorder(root->left);
    newNode->right = copyTreePreorder(root->right);

    return newNode;
}


void deleteTreePostorder(Node* root) {
    if (root == NULL) {
        return;
    }

    deleteTreePostorder(root->left);
    deleteTreePostorder(root->right);
    printf("Dugum %d bellekten siliniyor...\n", root->data);

    free(root);
}


void inorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}


int main() {
    Node* originalTree = NULL;
    Node* copiedTree = NULL;
    int numbers[6];

    printf("\nLutfen 6 adet sayi giriniz:\n");
    for (int i = 0; i < 6; i++) {
        printf("%d. sayi: ", i + 1);
        scanf("%d", &numbers[i]);
        originalTree = insert(originalTree, numbers[i]);
    }

    printf("\n--- Inorder ---\n");
    inorderTraversal(originalTree);
    printf("\n\n");

    copiedTree = copyTreePreorder(originalTree);

    printf("--- Copied Tree ---\n");
    inorderTraversal(copiedTree);
    printf("\n\n");

    printf("--- Postorder Dolasim ile Tree Siliniyor ---\n");
    deleteTreePostorder(originalTree);
    originalTree = NULL;
    printf("Tree tamamen silindi!\n\n");


    deleteTreePostorder(copiedTree);
    copiedTree = NULL;
    printf("Copied Tree tamamen silindi!\n\n");

    printf("\nTum bellek temizlendi!\n");

    return 0;
}