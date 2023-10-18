#include <stdio.h>
#include <stdlib.h>

void cscan(int arr[], int size, int start) {
    int total_tracks = 200; // Change this value to match your system's total tracks.
    int seek_sequence[size + 3];

    // Sort the track positions in ascending order.
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    int cur_track = start;
    int seek_count = 0;

    // Perform the forward scan
    int i = 0;
    while (i < size && arr[i] <= cur_track) {
        i++;
    }

    // Add all tracks in the forward direction
    for (; i < size; i++) {
        seek_sequence[seek_count++] = arr[i];
        cur_track = arr[i];
    }

    // Go to the beginning of the disk
    seek_sequence[seek_count++] = total_tracks - 1;
    cur_track = 0;

    // Perform the second forward scan
    for (i = 0; i < size; i++) {
        if (arr[i] >= cur_track) {
            seek_sequence[seek_count++] = arr[i];
            cur_track = arr[i];
        }
    }

    printf("Seek Sequence is: ");
    for (i = 0; i < seek_count; i++) {
        printf("%d ", seek_sequence[i]);
    }

    int total_seek_operations = seek_count - 1;
    printf("\nTotal seek operations: %d\n", total_seek_operations);
}

int main() {
    int size, start;

    printf("Enter the number of tracks: ");
    scanf("%d", &size);

    int arr[size];

    printf("Enter the track positions: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &start);

    cscan(arr, size, start);

    return 0;
}
