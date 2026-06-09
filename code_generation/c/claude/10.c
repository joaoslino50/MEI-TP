#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define the linked list structure
typedef struct {
    Node* head;
    int size;
} LinkedList;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Initialize a new linked list
void initList(LinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

// Insert at the beginning
void insertAtBeginning(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) return;
    
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

// Insert at the end
void insertAtEnd(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) return;
    
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

// Insert at a specific position (0-based index)
bool insertAtPosition(LinkedList* list, int data, int position) {
    if (position < 0 || position > list->size) {
        printf("Invalid position!\n");
        return false;
    }
    
    if (position == 0) {
        insertAtBeginning(list, data);
        return true;
    }
    
    Node* newNode = createNode(data);
    if (newNode == NULL) return false;
    
    Node* current = list->head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    list->size++;
    return true;
}

// ITERATIVE REVERSE - Most common and efficient
void reverseListIterative(LinkedList* list) {
    if (list->head == NULL || list->head->next == NULL) {
        return; // Empty or single node list
    }
    
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;
    
    while (current != NULL) {
        next = current->next;  // Store next node
        current->next = prev;  // Reverse the link
        prev = current;        // Move prev forward
        current = next;        // Move current forward
    }
    
    list->head = prev; // Update head to new first node
}

// RECURSIVE REVERSE - Elegant but uses stack space
Node* reverseRecursiveHelper(Node* head) {
    // Base case: empty list or single node
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    // Recursively reverse the rest of the list
    Node* newHead = reverseRecursiveHelper(head->next);
    
    // Adjust pointers
    head->next->next = head;
    head->next = NULL;
    
    return newHead;
}

void reverseListRecursive(LinkedList* list) {
    if (list->head == NULL || list->head->next == NULL) {
        return;
    }
    list->head = reverseRecursiveHelper(list->head);
}

// REVERSE IN GROUPS OF K
Node* reverseInGroups(Node* head, int k) {
    if (head == NULL || k <= 1) {
        return head;
    }
    
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;
    int count = 0;
    
    // Reverse first k nodes
    while (current != NULL && count < k) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }
    
    // Recursively reverse the remaining list
    if (next != NULL) {
        head->next = reverseInGroups(next, k);
    }
    
    return prev;
}

void reverseListInGroups(LinkedList* list, int k) {
    if (list->head == NULL || k <= 1) {
        return;
    }
    list->head = reverseInGroups(list->head, k);
}

// Utility function to print the list
void printList(const LinkedList* list) {
    if (list->head == NULL) {
        printf("Empty list\n");
        return;
    }
    
    Node* current = list->head;
    printf("List (size %d): ", list->size);
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf(" -> NULL\n");
}

// Function to print list with detailed view
void printListDetailed(const LinkedList* list, const char* title) {
    printf("\n%s:\n", title);
    if (list->head == NULL) {
        printf("  Empty list\n");
        return;
    }
    
    Node* current = list->head;
    int position = 0;
    printf("  Head -> ");
    while (current != NULL) {
        printf("[%d|", current->data);
        if (current->next) {
            printf("·] -> ");
        } else {
            printf("X]");
        }
        current = current->next;
        position++;
    }
    printf("\n");
}

// Get the length of the list
int getLength(const LinkedList* list) {
    return list->size;
}

// Search for an element
bool search(const LinkedList* list, int target) {
    Node* current = list->head;
    int position = 0;
    
    while (current != NULL) {
        if (current->data == target) {
            printf("Found %d at position %d\n", target, position);
            return true;
        }
        current = current->next;
        position++;
    }
    printf("%d not found in the list\n", target);
    return false;
}

// Delete a node by value
bool deleteByValue(LinkedList* list, int value) {
    if (list->head == NULL) {
        return false;
    }
    
    // If head needs to be deleted
    if (list->head->data == value) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        list->size--;
        return true;
    }
    
    // Search for the node to delete
    Node* current = list->head;
    while (current->next != NULL && current->next->data != value) {
        current = current->next;
    }
    
    if (current->next == NULL) {
        return false;
    }
    
    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
    list->size--;
    return true;
}

// Free the entire list
void freeList(LinkedList* list) {
    Node* current = list->head;
    Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    list->head = NULL;
    list->size = 0;
}

// Create a list from an array
void createListFromArray(LinkedList* list, int arr[], int n) {
    initList(list);
    for (int i = 0; i < n; i++) {
        insertAtEnd(list, arr[i]);
    }
}

// Function to demonstrate step-by-step reversal
void demonstrateReverseStepByStep(LinkedList* list) {
    printf("\n=== STEP-BY-STEP REVERSAL ===\n");
    printf("Original list:\n");
    printListDetailed(list, "Initial");
    
    if (list->head == NULL || list->head->next == NULL) {
        printf("List too short to demonstrate steps\n");
        return;
    }
    
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;
    int step = 1;
    
    printf("\nReversal process:\n");
    while (current != NULL) {
        printf("\nStep %d:\n", step++);
        printf("  Before: current = %d, prev = %s\n", 
               current->data, prev ? (printf("%d", prev->data), "set") : "NULL");
        
        next = current->next;
        printf("  Store next = %s\n", next ? (printf("%d", next->data), "set") : "NULL");
        
        current->next = prev;
        printf("  Reverse link: current->next points to %s\n", 
               prev ? (printf("%d", prev->data), "prev") : "NULL");
        
        prev = current;
        printf("  Move prev to current (%d)\n", current->data);
        
        current = next;
        printf("  Move current to next (%s)\n", 
               next ? (printf("%d", next->data), "set") : "NULL");
        
        printf("  Partial reversal: ");
        Node* temp = prev;
        while (temp != NULL) {
            printf("%d", temp->data);
            if (temp->next) printf(" -> ");
            temp = temp->next;
        }
        printf(" -> NULL\n");
    }
    
    list->head = prev;
    printf("\nFinal reversed list:\n");
    printListDetailed(list, "Result");
}

int main() {
    printf("LINKED LIST REVERSAL IMPLEMENTATION\n");
    printf("===================================\n");
    
    // Test 1: Basic iterative reversal
    printf("\n1. ITERATIVE REVERSAL\n");
    LinkedList list1;
    initList(&list1);
    
    // Create list: 1 -> 2 -> 3 -> 4 -> 5
    for (int i = 1; i <= 5; i++) {
        insertAtEnd(&list1, i);
    }
    printList(&list1);
    
    reverseListIterative(&list1);
    printf("After iterative reversal: ");
    printList(&list1);
    
    // Test 2: Recursive reversal
    printf("\n2. RECURSIVE REVERSAL\n");
    LinkedList list2;
    initList(&list2);
    
    for (int i = 1; i <= 5; i++) {
        insertAtEnd(&list2, i);
    }
    printList(&list2);
    
    reverseListRecursive(&list2);
    printf("After recursive reversal: ");
    printList(&list2);
    
    // Test 3: Reverse in groups of k
    printf("\n3. REVERSE IN GROUPS\n");
    LinkedList list3;
    initList(&list3);
    
    for (int i = 1; i <= 8; i++) {
        insertAtEnd(&list3, i);
    }
    printList(&list3);
    
    int k = 3;
    reverseListInGroups(&list3, k);
    printf("After reversing in groups of %d: ", k);
    printList(&list3);
    
    // Test 4: Edge cases
    printf("\n4. EDGE CASES\n");
    
    // Empty list
    LinkedList emptyList;
    initList(&emptyList);
    printf("Empty list: ");
    printList(&emptyList);
    reverseListIterative(&emptyList);
    printf("After reversal: ");
    printList(&emptyList);
    
    // Single element
    LinkedList singleList;
    initList(&singleList);
    insertAtEnd(&singleList, 42);
    printf("\nSingle element list: ");
    printList(&singleList);
    reverseListIterative(&singleList);
    printf("After reversal: ");
    printList(&singleList);
    
    // Two elements
    LinkedList twoList;
    initList(&twoList);
    insertAtEnd(&twoList, 10);
    insertAtEnd(&twoList, 20);
    printf("\nTwo element list: ");
    printList(&twoList);
    reverseListIterative(&twoList);
    printf("After reversal: ");
    printList(&twoList);
    
    // Test 5: Step-by-step demonstration
    LinkedList demoList;
    initList(&demoList);
    for (int i = 1; i <= 4; i++) {
        insertAtEnd(&demoList, i);
    }
    demonstrateReverseStepByStep(&demoList);
    
    // Test 6: Operations after reversal
    printf("\n5. OPERATIONS AFTER REVERSAL\n");
    LinkedList list4;
    createListFromArray(&list4, (int[]){10, 20, 30, 40, 50}, 5);
    printList(&list4);
    
    reverseListIterative(&list4);
    printf("Reversed: ");
    printList(&list4);
    
    // Insert after reversal
    insertAtBeginning(&list4, 5);
    insertAtEnd(&list4, 55);
    insertAtPosition(&list4, 25, 3);
    printf("After insertions: ");
    printList(&list4);
    
    // Search after reversal
    search(&list4, 30);
    search(&list4, 99);
    
    // Delete after reversal
    deleteByValue(&list4, 30);
    printf("After deleting 30: ");
    printList(&list4);
    
    // Test 7: Large list performance
    printf("\n6. PERFORMANCE TEST\n");
    LinkedList largeList;
    initList(&largeList);
    
    printf("Creating list with 1000 elements...\n");
    for (int i = 0; i < 1000; i++) {
        insertAtEnd(&largeList, i);
    }
    printf("List size: %d\n", largeList.size);
    
    reverseListIterative(&largeList);
    printf("List reversed successfully\n");
    printf("First element after reversal: %d\n", largeList.head->data);
    printf("Last element after reversal: ");
    Node* current = largeList.head;
    while (current->next != NULL) {
        current = current->next;
    }
    printf("%d\n", current->data);
    
    // Free all allocated memory
    freeList(&list1);
    freeList(&list2);
    freeList(&list3);
    freeList(&emptyList);
    freeList(&singleList);
    freeList(&twoList);
    freeList(&demoList);
    freeList(&list4);
    freeList(&largeList);
    
    // Summary
    printf("\n=== IMPLEMENTATION SUMMARY ===\n");
    printf("Time Complexity:\n");
    printf("  - Iterative reversal: O(n)\n");
    printf("  - Recursive reversal: O(n)\n");
    printf("  - Reverse in groups: O(n)\n");
    printf("Space Complexity:\n");
    printf("  - Iterative reversal: O(1)\n");
    printf("  - Recursive reversal: O(n) due to recursion stack\n");
    printf("  - Reverse in groups: O(n/k) recursion depth\n");
    printf("\nKey Points:\n");
    printf("  - Iterative method is preferred for large lists\n");
    printf("  - Recursive method is more elegant but uses more memory\n");
    printf("  - All methods modify the list in-place\n");
    printf("  - Always handle edge cases (empty, single node)\n");
    
    return 0;
}