#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2
#define BLOCK_SIZE 100

// Singly Linked List Implementation

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void insert(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
}

void delete(Node** head, int value) {
    Node* temp = *head;
    Node* prev = NULL;
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Array-Based List Implementation

typedef struct ArrayList {
    int* data;
    int size;
    int capacity;
} ArrayList;

void initArrayList(ArrayList* list) {
    list->data = (int*)malloc(INITIAL_CAPACITY * sizeof(int));
    if (!list->data) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
}

void insertArrayList(ArrayList* list, int value) {
    if (list->size >= list->capacity) {
        list->capacity *= GROWTH_FACTOR;
        list->data = (int*)realloc(list->data, list->capacity * sizeof(int));
        if (!list->data) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
    }
    list->data[list->size++] = value;
}

void deleteArrayList(ArrayList* list, int value) {
    for (int i = 0; i < list->size; i++) {
        if (list->data[i] == value) {
            for (int j = i; j < list->size - 1; j++) {
                list->data[j] = list->data[j + 1];
            }
            list->size--;
            return;
        }
    }
}

void printArrayList(ArrayList* list) {
    for (int i = 0; i < list->size; i++) {
        printf("%d -> ", list->data[i]);
    }
    printf("NULL\n");
}

// ArrayBlock Implementation

typedef struct ArrayBlock {
    int** blocks;
    int numBlocks;
    int currentBlockIndex;
    int currentBlockSize;
} ArrayBlock;

void initArrayBlock(ArrayBlock* block) {
    block->blocks = (int**)malloc(sizeof(int*));
    if (!block->blocks) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    block->blocks[0] = (int*)malloc(BLOCK_SIZE * sizeof(int));
    if (!block->blocks[0]) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    block->numBlocks = 1;
    block->currentBlockIndex = 0;
    block->currentBlockSize = 0;
}

void insertArrayBlock(ArrayBlock* block, int value) {
    if (block->currentBlockSize >= BLOCK_SIZE) {
        block->currentBlockIndex++;
        if (block->currentBlockIndex >= block->numBlocks) {
            block->numBlocks *= GROWTH_FACTOR;
            block->blocks = (int**)realloc(block->blocks, block->numBlocks * sizeof(int*));
            if (!block->blocks) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
            block->blocks[block->currentBlockIndex] = (int*)malloc(BLOCK_SIZE * sizeof(int));
            if (!block->blocks[block->currentBlockIndex]) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
        }
        block->currentBlockSize = 0;
    }
    block->blocks[block->currentBlockIndex][block->currentBlockSize++] = value;
}

void deleteArrayBlock(ArrayBlock* block, int value) {
    // Simple implementation: search and remove the first occurrence
    for (int i = 0; i <= block->currentBlockIndex; i++) {
        for (int j = 0; j < block->currentBlockSize; j++) {
            if (block->blocks[i][j] == value) {
                // Shift elements to fill the gap
                for (int k = j; k < block->currentBlockSize - 1; k++) {
                    block->blocks[i][k] = block->blocks[i][k + 1];
                }
                block->currentBlockSize--;
                return;
            }
        }
    }
}

void printArrayBlock(ArrayBlock* block) {
    for (int i = 0; i <= block->currentBlockIndex; i++) {
        for (int j = 0; j < block->currentBlockSize; j++) {
            printf("%d -> ", block->blocks[i][j]);
        }
    }
    printf("NULL\n");
}

// Benchmarking

double timeOperation(void (*operation)(void*, int), void* arg, int numElements) {
    clock_t start = clock();
    operation(arg, numElements);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

void benchmarkInsert(void* arg, int numElements) {
    if (arg == NULL) return;
    switch (*(int*)arg) {
        case 0: {  // Linked List
            Node** head = (Node**)arg;
            for (int i = 0; i < numElements; i++) {
                insert(head, i);
            }
            break;
        }
        case 1: {  // Array List
            ArrayList* list = (ArrayList*)arg;
            for (int i = 0; i < numElements; i++) {
                insertArrayList(list, i);
            }
            break;
        }
        case 2: {  // Array Block
            ArrayBlock* block = (ArrayBlock*)arg;
            for (int i = 0; i < numElements; i++) {
                insertArrayBlock(block, i);
            }
            break;
        }
    }
}

void benchmarkDelete(void* arg, int numElements) {
    if (arg == NULL) return;
    switch (*(int*)arg) {
        case 0: {  // Linked List
            Node** head = (Node**)arg;
            for (int i = 0; i < numElements; i++) {
                delete(head, i);
            }
            break;
        }
        case 1: {  // Array List
            ArrayList* list = (ArrayList*)arg;
            for (int i = 0; i < numElements; i++) {
                deleteArrayList(list, i);
            }
            break;
        }
        case 2: {  // Array Block
            ArrayBlock* block = (ArrayBlock*)arg;
            for (int i = 0; i < numElements; i++) {
                deleteArrayBlock(block, i);
            }
            break;
        }
    }
}

int main() {
    Node* linkedList = NULL;
    ArrayList arrayList;
    initArrayList(&arrayList);
    ArrayBlock arrayBlock;
    initArrayBlock(&arrayBlock);

    int numElements = 10000;

    // Benchmark Insert Operations
    double timeLinkedInsert = timeOperation(benchmarkInsert, &linkedList, numElements);
    double timeArrayInsert = timeOperation(benchmarkInsert, &arrayList, numElements);
    double timeBlockInsert = timeOperation(benchmarkInsert, &arrayBlock, numElements);

    printf("Time for linked list insert: %f seconds\n", timeLinkedInsert);
    printf("Time for array list insert: %f seconds\n", timeArrayInsert);
    printf("Time for array block insert: %f seconds\n", timeBlockInsert);

    // Benchmark Delete Operations
    double timeLinkedDelete = timeOperation(benchmarkDelete, &linkedList, numElements);
    double timeArrayDelete = timeOperation(benchmarkDelete, &arrayList, numElements);
    double timeBlockDelete = timeOperation(benchmarkDelete, &arrayBlock, numElements);

    printf("Time for linked list delete: %f seconds\n", timeLinkedDelete);
    printf("Time for array list delete: %f seconds\n", timeArrayDelete);
    printf("Time for array block delete: %f seconds\n", timeBlockDelete);

    // Clean up
    // Free linked list
    while (linkedList != NULL) {
        Node* temp = linkedList;
        linkedList = linkedList->next;
        free(temp);
    }

    // Free array list
    free(arrayList.data);

    // Free array block
    for (int i = 0; i < arrayBlock.numBlocks; i++) {
        free(arrayBlock.blocks[i]);
    }
    free(arrayBlock.blocks);

    return 0;
}
