#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Maximum size of the binary tree

int tree[MAX];
int size = 0;

void create() {
    int n, data;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    printf("Enter the node values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        tree[size++] = data;
    }
}

void preorder(int index) {
    if (index >= size || tree[index] == -1) return;
    printf("%d ", tree[index]);
    preorder(2 * index + 1);
    preorder(2 * index + 2);
}

void inorder(int index) {
    if (index >= size || tree[index] == -1) return;
    inorder(2 * index + 1);
    printf("%d ", tree[index]);
    inorder(2 * index + 2);
}

void postorder(int index) {
    if (index >= size || tree[index] == -1) return;
    postorder(2 * index + 1);
    postorder(2 * index + 2);
    printf("%d ", tree[index]);
}

int main() {
    int choice;

    // Initialize the tree array with -1 to represent empty nodes
    for (int i = 0; i < MAX; i++) {
        tree[i] = -1;
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create\n");
        printf("2. Preorder Traversal\n");
        printf("3. Inorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorder(0);
                printf("\n");
                break;
            case 3:
                printf("Inorder Traversal: ");
                inorder(0);
                printf("\n");
                break;
            case 4:
                printf("Postorder Traversal: ");
                postorder(0);
                printf("\n");
                break;
            case 5:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
