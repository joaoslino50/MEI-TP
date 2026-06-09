#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

/*
 * Creates a new linked list node.
 */
Node *create_node(int data) {
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

/*
 * Inserts a new node at the end of the list.
 */
void append(Node **head, int data) {
    Node *new_node = create_node(data);

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node *current = *head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;
}

/*
 * Reverses the linked list in-place.
 *
 * Example:
 * 1 -> 2 -> 3 -> NULL
 *
 * becomes:
 * 3 -> 2 -> 1 -> NULL
 */
void reverse(Node **head) {
    Node *previous = NULL;
    Node *current = *head;
    Node *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    *head = previous;
}

/*
 * Prints the linked list.
 */
void print_list(Node *head) {
    Node *current = head;

    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }

    printf("NULL\n");
}

/*
 * Frees all nodes in the linked list.
 */
void free_list(Node *head) {
    Node *current = head;

    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node *head = NULL;

    append(&head, 10);
    append(&head, 20);
    append(&head, 30);
    append(&head, 40);

    printf("Original list:\n");
    print_list(head);

    reverse(&head);

    printf("Reversed list:\n");
    print_list(head);

    free_list(head);

    return 0;
}