#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define P 5
#define R 3

int alloc[P][R] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int max[P][R] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int avail[R] = {3, 3, 2};
int need[P][R];

void calculateNeed() {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

bool isSafe(int safe_seq[P]) {
    int work[R];
    bool finish[P] = {false};

    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += alloc[i][k];
                    safe_seq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}

bool requestResources(int p_id, int request[]) {
    for (int i = 0; i < R; i++) {
        if (request[i] > need[p_id][i]) {
            printf("Error: Request exceeds need for P%d\n", p_id);
            return false;
        }
        if (request[i] > avail[i]) {
            printf("Error: Resources not available for P%d\n", p_id);
            return false;
        }
    }

    // Pretend allocation
    for (int i = 0; i < R; i++) {
        avail[i] -= request[i];
        alloc[p_id][i] += request[i];
        need[p_id][i] -= request[i];
    }

    int temp_seq[P];
    if (isSafe(temp_seq)) {
        printf("Request granted. System is still in safe state.\n");
        return true;
    } else {
        // Rollback
        for (int i = 0; i < R; i++) {
            avail[i] += request[i];
            alloc[p_id][i] -= request[i];
            need[p_id][i] += request[i];
        }
        printf("Request denied. System would be unsafe.\n");
        return false;
    }
}

int main() {
    calculateNeed();

    int safe_seq[P];
    if (isSafe(safe_seq)) {
        printf("Initial system is in a safe state.\nSafe Sequence: ");
        for (int i = 0; i < P; i++)
            printf("P%d ", safe_seq[i]);
        printf("\n");
    } else {
        printf("Initial system is not in a safe state.\n");
        return 0;
    }

    char choice;
    do {
        int p_id;
        int request[R];

        printf("\nEnter process ID (0 to %d) making request: ", P - 1);
        scanf("%d", &p_id);

        printf("Enter the request vector (%d values): ", R);
        for (int i = 0; i < R; i++)
            scanf("%d", &request[i]);

        requestResources(p_id, request);

        printf("\nDo you want to make another request? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
