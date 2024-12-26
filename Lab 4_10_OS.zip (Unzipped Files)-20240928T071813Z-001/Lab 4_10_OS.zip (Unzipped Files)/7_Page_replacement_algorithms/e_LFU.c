#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

// Structure to represent a page frame with frequency and page number
typedef struct {
    int page_number;
    int frequency;
} PageFrame;

// Function to find the least frequently used page in the frames
int find_LFU(PageFrame frames[], int frame_count) {
    int min_frequency = frames[0].frequency;
    int min_index = 0;

    for (int i = 1; i < frame_count; i++) {
        if (frames[i].frequency < min_frequency) {
            min_frequency = frames[i].frequency;
            min_index = i;
        }
    }

    return min_index;
}

// Function to check if a page is in the frames
int is_page_in_frames(PageFrame frames[], int frame_count, int page) {
    for (int i = 0; i < frame_count; i++) {
        if (frames[i].page_number == page) {
            return i;
        }
    }
    return -1;
}

// Function to simulate LFU Page Replacement
void simulate_LFU(int pages[], int page_count, int frame_count) {
    PageFrame frames[MAX_FRAMES];
    int page_faults = 0;

    // Initialize frames
    for (int i = 0; i < frame_count; i++) {
        frames[i].page_number = -1;
        frames[i].frequency = 0;
    }

    // Process each page
    for (int i = 0; i < page_count; i++) {
        int current_page = pages[i];
        int index = is_page_in_frames(frames, frame_count, current_page);

        if (index == -1) { // Page not in frames
            int lfu_index = find_LFU(frames, frame_count);

            if (frames[lfu_index].page_number != -1) {
                printf("Page %d replaced with Page %d (LFU)\n", frames[lfu_index].page_number, current_page);
            }

            // Replace the least frequently used page
            frames[lfu_index].page_number = current_page;
            frames[lfu_index].frequency = 1;
            page_faults++;

        } else { // Page is already in frames
            frames[index].frequency++;
            printf("Page %d accessed, increased frequency to %d\n", current_page, frames[index].frequency);
        }
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES];
    int page_count, frame_count;

    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &frame_count);

    // Input the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &page_count);

    // Input the page reference string
    printf("Enter the page reference string: ");
    for (int i = 0; i < page_count; i++) {
        scanf("%d", &pages[i]);
    }

    // Simulate LFU Page Replacement
    simulate_LFU(pages, page_count, frame_count);

    return 0;
}
