#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 10

int pageFrames[MAX_FRAMES];
int pageOrder[MAX_FRAMES];
int pageReference[MAX_PAGES];
int pageCounter = 0;

void initializePageFrames() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        pageFrames[i] = -1;
        pageOrder[i] = -1;
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
            return i;
        }
    }
    return -1;
}

void updatePageOrder(int index) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (i == index) {
            pageOrder[i] = 0;
        } else if (pageOrder[i] != -1) {
            pageOrder[i]++;
        }
    }
}

int findLRUPage() {
    int maxOrder = -1;
    int lruIndex = -1;

    for (int i = 0; i < MAX_FRAMES; i++) {
        if (pageOrder[i] > maxOrder) {
            maxOrder = pageOrder[i];
            lruIndex = i;
        }
    }

    return lruIndex;
}

void lruPageReplacement() {
    for (int i = 0; i < MAX_PAGES; i++) {
        int page = pageReference[i];
        int frameIndex = isPageInFrames(page);

        if (frameIndex == -1) {
            // Page fault, find LRU page and replace it
            int lruIndex = findLRUPage();
            pageFrames[lruIndex] = page;
            pageOrder[lruIndex] = 0;
        } else {
            updatePageOrder(frameIndex);
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

    printf("Simulation of LRU Page Replacement Algorithm:\n");
    lruPageReplacement();

    return 0;
}
