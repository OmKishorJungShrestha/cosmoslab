#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants
#define MAX_BLOCKS 100
#define BLOCK_SIZE 1024
#define MAX_FILE_NAME 100

// Define inode structure
struct inode {
    int file_size;              // Size of the file in bytes
    int blocks[MAX_BLOCKS];     // Array to store block numbers
    int block_count;            // Number of blocks allocated
    char file_name[MAX_FILE_NAME];  // Name of the file
};

// Simulate a disk with blocks
int disk[MAX_BLOCKS][BLOCK_SIZE];

// Function to allocate a file
void allocate_file(struct inode *node, const char *file_name, int size) {
    node->file_size = size;
    node->block_count = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    strncpy(node->file_name, file_name, MAX_FILE_NAME);

    printf("Allocating file '%s' of size %d bytes...\n", file_name, size);

    for (int i = 0; i < node->block_count; i++) {
        node->blocks[i] = i; // Assign block numbers (simply sequential here)
        printf("Block %d allocated to file '%s'\n", i, node->file_name);
    }

    printf("File '%s' allocated with %d blocks.\n", node->file_name, node->block_count);
}

// Function to display inode details
void display_inode(struct inode *node) {
    printf("\nInode Information:\n");
    printf("File Name: %s\n", node->file_name);
    printf("File Size: %d bytes\n", node->file_size);
    printf("Blocks Allocated: %d\n", node->block_count);
    printf("Block Numbers: ");
    for (int i = 0; i < node->block_count; i++) {
        printf("%d ", node->blocks[i]);
    }
    printf("\n");
}

int main() {
    struct inode file_node;

    // Allocate a file with the inode
    allocate_file(&file_node, "example.txt", 5000);

    // Display the inode details
    display_inode(&file_node);

    return 0;
}
