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


// Ağaca düğüm ekleme
Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }

    return root;
}


// Inorder Dolasma (Sol - Kök - Sağ)
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder Dolasma (Kök - Sol - Sağ)
void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder Dolasma (Sol - Sağ - Kök)
void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Bellek temizleme
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;
    int choice, data;

    while (1) {
        printf("\n1. Node Ekle\n2. Inorder Dolasma\n3. Preorder Dolasma\n4. Postorder Dolasma\n5. Cikis\nSeciminiz: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Eklenecek dugum degerini girin: ");
                if (scanf("%d", &data) != 1) {
                    printf("Gecersiz karakter, Lutfen bir tamsayi girin.\n");
                    while(getchar() != '\n');
                    break;
                }
                root = insert(root, data);
                break;
            case 2:
                printf("Inorder Dolasma: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Preorder Dolasma: ");
                preorder(root);
                printf("\n");
                break;
            case 4:
                printf("Postorder Dolasma: ");
                postorder(root);
                printf("\n");
                break;
            case 5:
                freeTree(root);
                exit(0);
            default:
                printf("Gecersiz secim! Tekrar deneyin.\n");
        }
    }

    return 0;
}
