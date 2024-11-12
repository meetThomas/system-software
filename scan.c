#include <stdio.h>
#include <stdlib.h>

void main() {
    int n, head, diskSize, direction;
    int totalMovement = 0, distance, index = 0;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the head position: ");
    scanf("%d", &head);

    printf("Enter the size of the disk: ");
    scanf("%d", &diskSize);

    printf("Enter the request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the direction (1 for high, 0 for low): ");
    scanf("%d", &direction);

    // Sort the requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // Find the first request greater than or equal to the head position
    while (index < n && requests[index] < head) {
        index++;
    }

    printf("\nSeek Sequence:\n");

    // If the direction is towards higher values (right)
    if (direction == 1) {
        // Service requests to the right of the head
        for (int i = index; i < n; i++) {
            distance = abs(requests[i] - head);
            printf("Head moves from %d to %d (distance = %d)\n", head, requests[i], distance);
            totalMovement += distance;
            head = requests[i];
        }

        // Move to the end of the disk
        distance = abs(diskSize - 1 - head);
        printf("Head moves from %d to %d (distance = %d)\n", head, diskSize - 1, distance);
        totalMovement += distance;
        head = diskSize - 1;

        // Service requests on the left side
        for (int i = index - 1; i >= 0; i--) {
            distance = abs(requests[i] - head);
            printf("Head moves from %d to %d (distance = %d)\n", head, requests[i], distance);
            totalMovement += distance;
            head = requests[i];
        }
    }
    // If the direction is towards lower values (left)
    else {
        // Service requests to the left of the head
        for (int i = index - 1; i >= 0; i--) {
            distance = abs(requests[i] - head);
            printf("Head moves from %d to %d (distance = %d)\n", head, requests[i], distance);
            totalMovement += distance;
            head = requests[i];
        }

        // Move to the start of the disk
        distance = abs(head - 0);
        printf("Head moves from %d to %d (distance = %d)\n", head, 0, distance);
        totalMovement += distance;
        head = 0;

        // Service requests on the right side
        for (int i = index; i < n; i++) {
            distance = abs(requests[i] - head);
            printf("Head moves from %d to %d (distance = %d)\n", head, requests[i], distance);
            totalMovement += distance;
            head = requests[i];
        }
    }

    printf("Total head movement = %d\n", totalMovement);
}
