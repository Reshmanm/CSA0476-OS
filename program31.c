#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 10

int pageFrames[MAX_FRAMES];
int pageReference[MAX_PAGES];

void initializePageFrames() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        pageFrames[i] = -1;
    }
}

void displayPageFrames() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (pageFrames[i] == -1) {
            printf("[ ] ");
        } else {
            printf("[%d] ", pageFrames[i]);
        }
    }
    printf("\n");
}

int isPageInFrames(int page) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (pageFrames[i] == page) {
            return 1;
        }
    }
    return 0;
}

void fifoPageReplacement() {
    int rear = -1;
    for (int i = 0; i < MAX_PAGES; i++) {
        int page = pageReference[i];

        if (!isPageInFrames(page)) {
            rear = (rear + 1) % MAX_FRAMES;
            pageFrames[rear] = page;
        }

        printf("Page Reference: %d   Page Frames: ", page);
        displayPageFrames();
    }
}

int main() {
    initializePageFrames();

    // Example reference string
    int referenceString[MAX_PAGES] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3};
    for (int i = 0; i < MAX_PAGES; i++) {
        pageReference[i] = referenceString[i];
    }

    printf("Simulation of FIFO Page Replacement Algorithm:\n");
    fifoPageReplacement();

    return 0;
}
