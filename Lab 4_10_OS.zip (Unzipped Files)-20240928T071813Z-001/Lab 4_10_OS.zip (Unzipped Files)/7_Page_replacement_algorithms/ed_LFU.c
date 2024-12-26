#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 10

typedef struct {
    int page_number;
    int frequency;
} Page;

void LFU(int pages[], int n) {
    int frame_size = 3; // Adjust frame size as needed
    Page frames[frame_size];
    int frame_count = 0;
    int fault_count = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in frames
        for (int j = 0; j < frame_count; j++) {
            if (frames[j].page_number == page) {
                frames[j].frequency++;
                found = 1;
                break;
            }
        }

        // If page is not found in frames, replace LFU page
        if (!found) {
            fault_count++;

            if (frame_count < frame_size) {
                frames[frame_count].page_number = page;
                frames[frame_count].frequency = 1;
                frame_count++;
            } else {
                int min_freq = frames[0].frequency;
                int min_index = 0;

                for (int j = 1; j < frame_size; j++) {
                    if (frames[j].frequency < min_freq) {
                        min_freq = frames[j].frequency;
                        min_index = j;
                    }
                }

                frames[min_index].page_number = page;
                frames[min_index].frequency = 1;
            }
        }
    }

    printf("Page Fault Rate: %.2f%%\n", (float)fault_count / n * 100);
}

int main() {
    int pages[] = {1, 2, 3, 1, 4, 5, 1, 2, 3, 4};
    int n = sizeof(pages) / sizeof(pages[0]);

    LFU(pages, n);

    return 0;
}