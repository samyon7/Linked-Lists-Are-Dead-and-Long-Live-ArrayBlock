%%writefile jancok2.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct NoCacheList {
    Node* head;
} NoCacheList;

void initNoCacheList(NoCacheList* list) {
    list->head = NULL;
}

void insertNoCacheList(NoCacheList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
}

void deleteNoCacheList(NoCacheList* list, int data) {
    Node* current = list->head;
    Node* previous = NULL;

    while (current != NULL) {
        if (current->data == data) {
            if (previous == NULL) {
                list->head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void clearNoCacheList(NoCacheList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}


typedef struct LinkedList {
    Node* head;
} LinkedList;

void initLinkedList(LinkedList* list) {
    list->head = NULL;
}

void insertLinkedList(LinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
}

void deleteLinkedList(LinkedList* list, int data) {
    Node* current = list->head;
    Node* previous = NULL;

    while (current != NULL) {
        if (current->data == data) {
            if (previous == NULL) {
                list->head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void clearLinkedList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}


typedef struct SingleList {
    Node* head;
} SingleList;

void initSingleList(SingleList* list) {
    list->head = NULL;
}

void insertSingleList(SingleList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
}

void deleteSingleList(SingleList* list, int data) {
    Node* current = list->head;
    Node* previous = NULL;

    while (current != NULL) {
        if (current->data == data) {
            if (previous == NULL) {
                list->head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void clearSingleList(SingleList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}


typedef struct ArrayList {
    int* data;
    int capacity;
    int size;
} ArrayList;

void initArrayList(ArrayList* list, int capacity) {
    list->data = (int*)malloc(capacity * sizeof(int));
    list->capacity = capacity;
    list->size = 0;
}

void insertArrayList(ArrayList* list, int data) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->data = (int*)realloc(list->data, list->capacity * sizeof(int));
    }
    list->data[list->size++] = data;
}

void deleteArrayList(ArrayList* list, int data) {
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

void clearArrayList(ArrayList* list) {
    free(list->data);
    list->data = NULL;
    list->capacity = 0;
    list->size = 0;
}


typedef struct ArrayRing {
    int* data;
    int capacity;
    int size;
    int head;
    int tail;
} ArrayRing;

void initArrayRing(ArrayRing* ring, int capacity) {
    ring->data = (int*)malloc(capacity * sizeof(int));
    ring->capacity = capacity;
    ring->size = 0;
    ring->head = 0;
    ring->tail = 0;
}

void insertArrayRing(ArrayRing* ring, int data) {
    if (ring->size == ring->capacity) {
        int* newData = (int*)malloc(ring->capacity * 2 * sizeof(int));
        for (int i = 0; i < ring->size; i++) {
            newData[i] = ring->data[(ring->head + i) % ring->capacity];
        }
        free(ring->data);
        ring->data = newData;
        ring->head = 0;
        ring->tail = ring->size;
        ring->capacity *= 2;
    }
    ring->data[ring->tail] = data;
    ring->tail = (ring->tail + 1) % ring->capacity;
    ring->size++;
}

void deleteArrayRing(ArrayRing* ring, int data) {
    for (int i = 0; i < ring->size; i++) {
        if (ring->data[(ring->head + i) % ring->capacity] == data) {
            for (int j = i; j < ring->size - 1; j++) {
                ring->data[(ring->head + j) % ring->capacity] = ring->data[(ring->head + j + 1) % ring->capacity];
            }
            ring->size--;
            return;
        }
    }
}

void clearArrayRing(ArrayRing* ring) {
    free(ring->data);
    ring->data = NULL;
    ring->capacity = 0;
    ring->size = 0;
    ring->head = 0;
    ring->tail = 0;
}


typedef struct ArrayBlock {
    int* data;
    int capacity;
    int size;
    int blockSize;
} ArrayBlock;

void initArrayBlock(ArrayBlock* block, int capacity, int blockSize) {
    block->data = (int*)malloc(capacity * sizeof(int));
    block->capacity = capacity;
    block->size = 0;
    block->blockSize = blockSize;
}

void insertArrayBlock(ArrayBlock* block, int data) {
    if (block->size == block->capacity) {
        block->capacity += block->blockSize;
        block->data = (int*)realloc(block->data, block->capacity * sizeof(int));
    }
    block->data[block->size++] = data;
}

void deleteArrayBlock(ArrayBlock* block, int data) {
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

void clearArrayBlock(ArrayBlock* block) {
    free(block->data);
    block->data = NULL;
    block->capacity = 0;
    block->size = 0;
    block->blockSize = 0;
}


void stroustrupBenchmark(void* list, void (*insert)(void*, int), void (*delete)(void*, int), int n) {
    for (int i = 0; i < n; i++) {
        insert(list, i);
    }
    for (int i = 0; i < n; i++) {
        delete(list, i);
    }
}

void benchmarkStroustrup() {
    const int n = 1000000;
    NoCacheList noCacheList;
    LinkedList linkedList;
    SingleList singleList;
    ArrayList arrayList;
    ArrayRing arrayRing;
    ArrayBlock arrayBlock;

    initNoCacheList(&noCacheList);
    initLinkedList(&linkedList);
    initSingleList(&singleList);
    initArrayList(&arrayList, 1000);
    initArrayRing(&arrayRing, 1000);
    initArrayBlock(&arrayBlock, 1000, 1000);

    clock_t start, end;
    double time_spent;

    start = clock();
    stroustrupBenchmark(&noCacheList, (void (*)(void*, int))insertNoCacheList, (void (*)(void*, int))deleteNoCacheList, n);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("NoCacheList: %f seconds\n", time_spent);

    start = clock();
    stroustrupBenchmark(&linkedList, (void (*)(void*, int))insertLinkedList, (void (*)(void*, int))deleteLinkedList, n);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("LinkedList: %f seconds\n", time_spent);

    start = clock();
    stroustrupBenchmark(&singleList, (void (*)(void*, int))insertSingleList, (void (*)(void*, int))deleteSingleList, n);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("SingleList: %f seconds\n", time_spent);

    start = clock();
    stroustrupBenchmark(&arrayList, (void (*)(void*, int))insertArrayList, (void (*)(void*, int))deleteArrayList, n);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("ArrayList: %f seconds\n", time_spent);

    start = clock();
    stroustrupBenchmark(&arrayRing, (void (*)(void*, int))insertArrayRing, (void (*)(void*, int))deleteArrayRing, n);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("ArrayRing: %f seconds\n", time_spent);

    start = clock();
    stroustrupBenchmark(&arrayBlock, (void (*)(void*, int))insertArrayBlock, (void (*)(void*, int))deleteArrayBlock, n);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("ArrayBlock: %f seconds\n", time_spent);

    clearNoCacheList(&noCacheList);
    clearLinkedList(&linkedList);
    clearSingleList(&singleList);
    clearArrayList(&arrayList);
    clearArrayRing(&arrayRing);
    clearArrayBlock(&arrayBlock);
}


void fairbench(void* list, void (*insert)(void*, int), void (*delete)(void*, int), int n) {
    for (int i = 0; i < n; i++) {
        insert(list, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        delete(list, i);
    }
}

void benchmarkFairbench() {
    const int n = 1000000;
    NoCacheList noCacheList;
    LinkedList linkedList;
    SingleList singleList;
    ArrayList arrayList;
    ArrayRing arrayRing;
    ArrayBlock arrayBlock;

    initNoCacheList(&noCacheList);
    initLinkedList(&linkedList);
    initSingleList(&singleList);
    initArrayList(&arrayList, 1000);
    initArrayRing(&arrayRing, 1000);
    initArrayBlock(&arrayBlock, 1000, 1000);

    clock_t start, end;
    double time_spent;

    start = clock();
    fairbench(&noCacheList, (void (*)(void*, int))insertNoCacheList, (void (*)(void*, int))deleteNoCacheList, n);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("NoCacheList: %f seconds\n", time_spent);

    start = clock();
    fairbench(&linkedList, (void (*)(void*, int))insertLinkedList, (void (*)(void*, int))deleteLinkedList, n);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("LinkedList: %f seconds\n", time_spent);

    start = clock();
    fairbench(&singleList, (void (*)(void*, int))insertSingleList, (void (*)(void*, int))deleteSingleList, n);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("SingleList: %f seconds\n", time_spent);

    start = clock();
    fairbench(&arrayList, (void (*)(void*, int))insertArrayList, (void (*)(void*, int))deleteArrayList, n);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("ArrayList: %f seconds\n", time_spent);

    start = clock();
    fairbench(&arrayRing, (void (*)(void*, int))insertArrayRing, (void (*)(void*, int))deleteArrayRing, n);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("ArrayRing: %f seconds\n", time_spent);

    start = clock();
    fairbench(&arrayBlock, (void (*)(void*, int))insertArrayBlock, (void (*)(void*, int))deleteArrayBlock, n);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("ArrayBlock: %f seconds\n", time_spent);

    clearNoCacheList(&noCacheList);
    clearLinkedList(&linkedList);
    clearSingleList(&singleList);
    clearArrayList(&arrayList);
    clearArrayRing(&arrayRing);
    clearArrayBlock(&arrayBlock);
}


int main() {
    printf("Running Bjarne Stroustrup's Benchmark:\n");
    benchmarkStroustrup();

    printf("\nRunning Fairbench:\n");
    benchmarkFairbench();

    return 0;
}
