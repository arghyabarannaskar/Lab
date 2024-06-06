#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data);
void printList(struct Node* head);
void bubbleSort(struct Node* head);
void insertionSort(struct Node** head_ref);
void selectionSort(struct Node* head);

int main() {
    struct Node* head = NULL;
    int choice, data;

    printf("Menu:\n");
    printf("1. Bubble Sort\n");
    printf("2. Insertion Sort\n");
    printf("3. Selection Sort\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter the number of elements in the list: ");
    int n;
    scanf("%d", &n);
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        push(&head, data);
    }

    printf("\nOriginal List: ");
    printList(head);
    printf("\n");

    switch (choice) {
        case 1:
            bubbleSort(head);
            printf("Sorted List using Bubble Sort: ");
            printList(head);
            break;
        case 2:
            insertionSort(&head);
            printf("Sorted List using Insertion Sort: ");
            printList(head);
            break;
        case 3:
            selectionSort(head);
            printf("Sorted List using Selection Sort: ");
            printList(head);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}


void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}


void bubbleSort(struct Node* head) {
    int swapped;
    struct Node* ptr1;
    struct Node* lptr = NULL;

    if (head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Insertion Sort for singly linked list
void insertionSort(struct Node** head_ref) {
    struct Node* sorted = NULL;
    struct Node* current = *head_ref;
    while (current != NULL) {
        struct Node* next = current->next;
        sortedInsert(&sorted, current);
        current = next;
    }
    *head_ref = sorted;
}


void sortedInsert(struct Node** head_ref, struct Node* new_node) {
    struct Node* current;
    if (*head_ref == NULL || (*head_ref)->data >= new_node->data) {
        new_node->next = *head_ref;
        *head_ref = new_node;
    } else {
        current = *head_ref;
        while (current->next != NULL &&
               current->next->data < new_node->data) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void selectionSort(struct Node* head) {
    struct Node* current = head;
    while (current->next != NULL) {
        struct Node* min = current;
        struct Node* r = current->next;
        while (r != NULL) {
            if (min->data > r->data)
                min = r;
            r = r->next;
        }
        int temp = current->data;
        current->data = min->data;
        min->data = temp;
        current = current->next;
    }
}
