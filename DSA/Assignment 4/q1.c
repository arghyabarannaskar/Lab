#include <stdio.h>

void displayMenu();
int linearSearchIterative(int arr[], int n, int key);
int linearSearchRecursive(int arr[], int n, int key, int index);
int binarySearchIterative(int arr[], int n, int key);
int binarySearchRecursive(int arr[], int low, int high, int key);

int main() {
    int choice, n, key, result;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter the elements (in sorted order):\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the element to search: ");
                scanf("%d", &key);
                result = linearSearchIterative(arr, n, key);
                if(result != -1)
                    printf("Element found at index %d (Iterative Linear Search)\n", result);
                else
                    printf("Element not found (Iterative Linear Search)\n");
                break;
            case 2:
                printf("Enter the element to search: ");
                scanf("%d", &key);
                result = linearSearchRecursive(arr, n, key, 0);
                if(result != -1)
                    printf("Element found at index %d (Recursive Linear Search)\n", result);
                else
                    printf("Element not found (Recursive Linear Search)\n");
                break;
            case 3:
                printf("Enter the element to search: ");
                scanf("%d", &key);
                result = binarySearchIterative(arr, n, key);
                if(result != -1)
                    printf("Element found at index %d (Iterative Binary Search)\n", result);
                else
                    printf("Element not found (Iterative Binary Search)\n");
                break;
            case 4:
                printf("Enter the element to search: ");
                scanf("%d", &key);
                result = binarySearchRecursive(arr, 0, n-1, key);
                if(result != -1)
                    printf("Element found at index %d (Recursive Binary Search)\n", result);
                else
                    printf("Element not found (Recursive Binary Search)\n");
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please choose again.\n");
        }
    }
}

void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Iterative Linear Search\n");
    printf("2. Recursive Linear Search\n");
    printf("3. Iterative Binary Search\n");
    printf("4. Recursive Binary Search\n");
    printf("5. Exit\n");
}

int linearSearchIterative(int arr[], int n, int key) {
    for(int i = 0; i < n; i++) {
        if(arr[i] == key)
            return i;
    }
    return -1;
}

int linearSearchRecursive(int arr[], int n, int key, int index) {
    if(index >= n)
        return -1;
    if(arr[index] == key)
        return index;
    return linearSearchRecursive(arr, n, key, index + 1);
}

int binarySearchIterative(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(arr[mid] == key)
            return mid;
        else if(arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int binarySearchRecursive(int arr[], int low, int high, int key) {
    if(low > high)
        return -1;
    int mid = low + (high - low) / 2;
    if(arr[mid] == key)
        return mid;
    else if(arr[mid] < key)
        return binarySearchRecursive(arr, mid + 1, high, key);
    else
        return binarySearchRecursive(arr, low, mid - 1, key);
}
