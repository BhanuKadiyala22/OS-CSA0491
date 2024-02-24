#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 100

struct Block {
    int size;
    int free;
};

struct Block* memory = NULL;

void initialize() {
    memory = (struct Block*)malloc(MEMORY_SIZE * sizeof(struct Block));
    memory[0].size = MEMORY_SIZE;
    memory[0].free = 1;
}

void split(int index, int size) {
    memory[index].size -= size;
    memory[index + size].size = size;
    memory[index + size].free = 0;
}

void *first_fit(int size) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].free && memory[i].size >= size) {
            if (memory[i].size > size) {
                split(i, size);
            }
            memory[i].free = 0;
            return (void*)&memory[i + 1];
        }
    }
    return NULL;
}

void *best_fit(int size) {
    int min_size = MEMORY_SIZE + 1;
    int index = -1;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].free && memory[i].size >= size && memory[i].size < min_size) {
            min_size = memory[i].size;
            index = i;
        }
    }
    if (index != -1) {
        if (memory[index].size > size) {
            split(index, size);
        }
        memory[index].free = 0;
        return (void*)&memory[index + 1];
    }
    return NULL;
}

void *worst_fit(int size) {
    int max_size = -1;
    int index = -1;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].free && memory[i].size >= size && memory[i].size > max_size) {
            max_size = memory[i].size;
            index = i;
        }
    }
    if (index != -1) {
        if (memory[index].size > size) {
            split(index, size);
        }
        memory[index].free = 0;
        return (void*)&memory[index + 1];
    }
    return NULL;
}

void deallocate(void *ptr) {
    struct Block *block = (struct Block*)ptr - 1;
    block->free = 1;
}

void display_memory() {
    printf("Memory Layout:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        printf("[%d-%d] ", i, i + memory[i].size - 1);
        if (memory[i].free) {
            printf("(Free)\n");
        } else {
            printf("(Allocated)\n");
        }
        i += memory[i].size - 1;
    }
    printf("\n");
}

int main() {
    initialize();

    // Example usage
    void *ptr1 = first_fit(20);
    printf("Allocated memory block 1 at address: %p\n", ptr1);
    display_memory();

    void *ptr2 = best_fit(10);
    printf("Allocated memory block 2 at address: %p\n", ptr2);
    display_memory();

    void *ptr3 = worst_fit(30);
    printf("Allocated memory block 3 at address: %p\n", ptr3);
    display_memory();

    deallocate(ptr2);
    printf("Deallocated memory block 2\n");
    display_memory();

    free(memory); // Free memory allocated for the memory array
    return 0;
}
