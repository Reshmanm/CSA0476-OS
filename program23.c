#include <stdio.h>
#include <stdlib.h>

void scan(int arr[], int size, int start, int direction) {
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

    int left = 0, right = size - 1;

    while (direction == 1 ? cur_track <= total_tracks : cur_track >= 0) {
        if (direction == 1) {
            // Moving right
            while (left < size && arr[left] <= cur_track) {
                left++;
            }
            if (left < size) {
                seek_sequence[seek_count++] = arr[left];
                cur_track = arr[left];
            } else {
                direction = -1;
            }
        } else {
            // Moving left
            while (right >= 0 && arr[right] >= cur_track) {
                right--;
            }
            if (right >= 0) {
                seek_sequence[seek_count++] = arr[right];
                cur_track = arr[right];
            } else {
                direction = 1;
            }
        }
    }

    printf("Seek Sequence is: ");
    for (int i = 0; i < seek_count; i++) {
        printf("%d ", seek_sequence[i]);
    }

    int total_seek_operations = seek_count - 1;
    printf("\nTotal seek operations: %d\n", total_seek_operations);
}

int main() {
    int size, start, direction;
    
    printf("Enter the number of tracks: ");
    scanf("%d", &size);
    
    int arr[size];
    
    printf("Enter the track positions: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Enter the initial head position: ");
    scanf("%d", &start);

    printf("Enter the initial direction (1 for right, -1 for left): ");
    scanf("%d", &direction);

    scan(arr, size, start, direction);

    return 0;
}
