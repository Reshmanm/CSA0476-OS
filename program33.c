#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3
#define MAX_PAGES 10

int pageFrames[MAX_FRAMES];
int pageReference[MAX_PAGES];
int futureReferences[MAX_PAGES];
int pageCounter = 0;

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
            return i;
        }
    }
    return -1;
}

int findOptimalPageToReplace(int startIndex) {
    int optimalPage = -1;
    int farthestUse = -1;

    for (int i = 0; i < MAX_FRAMES; i++) {
        int page = pageFrames[i];
        bool foundInFuture = false;
        for (int j = startIndex; j < MAX_PAGES; j++) {
            if (pageReference[j] == page) {
                futureReferences[j] = 1;
                foundInFuture = true;
                break;
            }
        }

        if (!foundInFuture) {
            return i;  // Page not used in the future
        }

        if (futureReferences[i] == 0 && j > farthestUse) {
            farthestUse = j;
            optimalPage = i;
        }
    }

    return optimalPage;
}

void optimalPageReplacement() {
    for (int i = 0; i < MAX_PAGES; i++) {
        int page = pageReference[i];
        int frameIndex = isPageInFrames(page);

        if (frameIndex == -1) {
            // Page fault, find an optimal page to replace
            int optimalPageToReplace = findOptimalPageToReplace(i);
            pageFrames[optimalPageToReplace] = page;
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
        futureReferences[i] = 0;
    }

    printf("Simulation of Optimal Page Replacement Algorithm:\n");
    optimalPageReplacement();

    return 0;
}
