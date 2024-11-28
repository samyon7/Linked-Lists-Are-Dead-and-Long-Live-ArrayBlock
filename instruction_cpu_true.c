#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Linked List Node
typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

// Array List
typedef struct {
    int *data;
    int capacity;
    int size;
} ArrayList;

// Array Block
typedef struct {
    int *data;
    int capacity;
    int size;
    int blockSize;
} ArrayBlock;

// Function prototypes
ListNode* createListNode(int data);
void insertAtEndLinkedList(ListNode **head, int data);
void deleteNodeLinkedList(ListNode **head, int data);
void printLinkedList(ListNode *head);
void freeLinkedList(ListNode *head);

void initArrayList(ArrayList *list, int capacity);
void insertAtEndArrayList(ArrayList *list, int data);
void deleteElementArrayList(ArrayList *list, int data);
void printArrayList(ArrayList *list);
void freeArrayList(ArrayList *list);

void initArrayBlock(ArrayBlock *block, int capacity, int blockSize);
void insertAtEndArrayBlock(ArrayBlock *block, int data);
void deleteElementArrayBlock(ArrayBlock *block, int data);
void printArrayBlock(ArrayBlock *block);
void freeArrayBlock(ArrayBlock *block);

void benchmark();

// Linked List Functions
ListNode* createListNode(int data) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtEndLinkedList(ListNode **head, int data) {
    ListNode *newNode = createListNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        ListNode *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void deleteNodeLinkedList(ListNode **head, int data) {
    ListNode *temp = *head, *prev = NULL;
    if (temp != NULL && temp->data == data) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp);
}

void printLinkedList(ListNode *head) {
    ListNode *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeLinkedList(ListNode *head) {
    ListNode *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Array List Functions
void initArrayList(ArrayList *list, int capacity) {
    list->data = (int *)malloc(capacity * sizeof(int));
    if (list->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    list->capacity = capacity;
    list->size = 0;
}

void insertAtEndArrayList(ArrayList *list, int data) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->data = (int *)realloc(list->data, list->capacity * sizeof(int));
        if (list->data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
    }
    list->data[list->size++] = data;
}

void deleteElementArrayList(ArrayList *list, int data) {
    for (int i = 0; i < list->size; i++) {
        if (list->data[i] == data) {
            for (int j = i; j < list->size - 1; j++) {
                list->data[j] = list->data[j + 1];
            }
            list->size--;
            return;
        }
    }
}

void printArrayList(ArrayList *list) {
    for (int i = 0; i < list->size; i++) {
        printf("%d -> ", list->data[i]);
    }
    printf("NULL\n");
}

void freeArrayList(ArrayList *list) {
    free(list->data);
}

// Array Block Functions
void initArrayBlock(ArrayBlock *block, int capacity, int blockSize) {
    block->data = (int *)malloc(capacity * sizeof(int));
    if (block->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    block->capacity = capacity;
    block->size = 0;
    block->blockSize = blockSize;
}

void insertAtEndArrayBlock(ArrayBlock *block, int data) {
    if (block->size == block->capacity) {
        block->capacity += block->blockSize;
        block->data = (int *)realloc(block->data, block->capacity * sizeof(int));
        if (block->data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
    }
    block->data[block->size++] = data;
}

void deleteElementArrayBlock(ArrayBlock *block, int data) {
    for (int i = 0; i < block->size; i++) {
        if (block->data[i] == data) {
            for (int j = i; j < block->size - 1; j++) {
                block->data[j] = block->data[j + 1];
            }
            block->size--;
            return;
        }
    }
}

void printArrayBlock(ArrayBlock *block) {
    for (int i = 0; i < block->size; i++) {
        printf("%d -> ", block->data[i]);
    }
    printf("NULL\n");
}

void freeArrayBlock(ArrayBlock *block) {
    free(block->data);
}

// Benchmarking function
void benchmark() {
    const int numOperations = 100000;
    const int blockSize = 1024;

    // Linked List
    ListNode *head = NULL;
    clock_t start = clock();
    for (int i = 0; i < numOperations; i++) {
        insertAtEndLinkedList(&head, i);
    }
    for (int i = 0; i < numOperations; i++) {
        deleteNodeLinkedList(&head, i);
    }
    clock_t end = clock();
    double timeLinkedList = (double)(end - start) / CLOCKS_PER_SEC;
    freeLinkedList(head);

    // Array List
    ArrayList arrayList;
    initArrayList(&arrayList, numOperations);
    start = clock();
    for (int i = 0; i < numOperations; i++) {
        insertAtEndArrayList(&arrayList, i);
    }
    for (int i = 0; i < numOperations; i++) {
        deleteElementArrayList(&arrayList, i);
    }
    end = clock();
    double timeArrayList = (double)(end - start) / CLOCKS_PER_SEC;
    freeArrayList(&arrayList);

    // Array Block
    ArrayBlock arrayBlock;
    initArrayBlock(&arrayBlock, numOperations, blockSize);
    start = clock();
    for (int i = 0; i < numOperations; i++) {
        insertAtEndArrayBlock(&arrayBlock, i);
    }
    for (int i = 0; i < numOperations; i++) {
        deleteElementArrayBlock(&arrayBlock, i);
    }
    end = clock();
    double timeArrayBlock = (double)(end - start) / CLOCKS_PER_SEC;
    freeArrayBlock(&arrayBlock);

    // Print results
    printf("Time for Linked List: %.6f seconds\n", timeLinkedList);
    printf("Time for Array List: %.6f seconds\n", timeArrayList);
    printf("Time for Array Block: %.6f seconds\n", timeArrayBlock);
}

int main() {
    benchmark();
    return 0;
}
