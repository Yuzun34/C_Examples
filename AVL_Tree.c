#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
    int height;
}TreeNode;

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // New node is initially added at leaf
    return newNode;
}

int getHeight(TreeNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalance(TreeNode* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// A utility function to right rotate subtree rooted with y
TreeNode* rightRotate(TreeNode* root) {
    TreeNode* newRoot = root->left;
    TreeNode* movedSubtree = newRoot->right;

    // Perform rotation
    newRoot->right = root;
    root->left = movedSubtree;

    // Update heights
    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? getHeight(root->left) : getHeight(root->right));
    newRoot->height = 1 + (getHeight(newRoot->left) > getHeight(newRoot->right) ? getHeight(newRoot->left) : getHeight(newRoot->right));

    // Return new root
    return newRoot;
}

// A utility function to left rotate subtree rooted with x
TreeNode* leftRotate(TreeNode* root) {
    TreeNode* y = root->right;
    TreeNode* T2 = y->left;

    // Perform rotation
    y->left = root;
    root->right = T2;

    // Update heights
    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? getHeight(root->left) : getHeight(root->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));

    // Return new root
    return y;
}


TreeNode* insertNode(TreeNode* node, int data) {
    // 1. Perform the normal BST insertion
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else // Duplicate keys are not allowed in the AVL tree
        return node;

    // 2. Update height of this ancestor node
    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));

    // 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // return the (unchanged) node pointer
    return node;
}

void preOrder(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}



int main() {
    TreeNode* root = NULL;

    // Constructing tree given in the above figure
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);
    root = insertNode(root, 25);
    // Preorder traversal of the constructed AVL tree is
    printf("Preorder traversal of the constructed AVL tree is \n");
    preOrder(root);

    return 0;
}