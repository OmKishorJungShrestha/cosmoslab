#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 100
#define BLOCK_SIZE 1024
#define MAX_FILE_NAME 100
#define END_OF_FILE -1

// Structure to represent a file in FAT
struct file {
    char file_name[MAX_FILE_NAME];
    int start_block;
    int size;
};

// Global File Allocation Table
int FAT[MAX_BLOCKS];

// Simulate a disk with blocks
int disk[MAX_BLOCKS][BLOCK_SIZE];

// Function to initialize FAT table
void initialize_FAT() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        FAT[i] = -1;  // -1 indicates that the block is free
    }
}

// Function to find the first free block in the FAT
int find_free_block() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (FAT[i] == -1) {
            return i;
        }
    }
    return -1;  // No free blocks available
}

// Function to allocate file in FAT
void allocate_file(struct file *f, const char *file_name, int size) {
    int blocks_needed = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    int previous_block = -1;

    strncpy(f->file_name, file_name, MAX_FILE_NAME);
    f->size = size;

    printf("Allocating file '%s' of size %d bytes...\n", file_name, size);

    for (int i = 0; i < blocks_needed; i++) {
        int current_block = find_free_block();

        if (current_block == -1) {
            printf("Error: Not enough free blocks available.\n");
            return;
        }

        if (i == 0) {
            f->start_block = current_block;
        } else {
            FAT[previous_block] = current_block;
        }

        previous_block = current_block;
        FAT[current_block] = END_OF_FILE;  // Mark the end of the file in the FAT

        printf("Block %d allocated to file '%s'\n", current_block, f->file_name);
    }

    printf("File '%s' allocated successfully.\n", f->file_name);
}

// Function to display the FAT
void display_FAT() {
    printf("\nFile Allocation Table (FAT):\n");
    printf("Block\tNext Block\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        printf("%d\t%d\n", i, FAT[i]);
    }
}

// Function to display the file's allocated blocks
void display_file_blocks(struct file *f) {
    printf("\nBlocks allocated to file '%s':\n", f->file_name);
    int block = f->start_block;

    while (block != END_OF_FILE) {
        printf("%d ", block);
        block = FAT[block];
    }

    printf("\n");
}

int main() {
    struct file f1;
    
    // Initialize the FAT table
    initialize_FAT();

    // Allocate a file in FAT
    allocate_file(&f1, "example.txt", 5000);

    // Display the FAT table
    display_FAT();

    // Display the blocks allocated to the file
    display_file_blocks(&f1);

    return 0;
}
