#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
    int leftThread, rightThread;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->leftThread = 1;
    newNode->rightThread = 1;
    return newNode;
}

Node* insert(Node* root, int data) {
    Node* ptr = root;
    Node* parent = NULL;

    while (ptr != NULL) {
        if (data == ptr->data) {
            printf("Duplicate key not allowed.\n");
            return root;
        }

        parent = ptr;

        if (data < ptr->data) {
            if (ptr->leftThread == 0)
                ptr = ptr->left;
            else
                break;
        } else {
            if (ptr->rightThread == 0)
                ptr = ptr->right;
            else
                break;
        }
    }

    Node* newNode = createNode(data);
    if (parent == NULL) {
        root = newNode;
    } else if (data < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->leftThread = 0;
        parent->left = newNode;
    } else {
        newNode->right = parent->right;
        newNode->left = parent;
        parent->rightThread = 0;
        parent->right = newNode;
    }

    return root;
}

void inorderTraversal(Node* root) {
    if (root == NULL)
        return;

    Node* ptr = root;
    while (ptr->leftThread == 0)
        ptr = ptr->left;

    while (ptr != NULL) {
        printf("%d ", ptr->data);

        if (ptr->rightThread == 1)
            ptr = ptr->right;
        else {
            ptr = ptr->right;
            while (ptr != NULL && ptr->leftThread == 0)
                ptr = ptr->left;
        }
    }
}

int main() {
    Node* root = NULL;
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);

    printf("Inorder Traversal of the Threaded Binary Tree:\n");
    inorderTraversal(root);

    return 0;
}
