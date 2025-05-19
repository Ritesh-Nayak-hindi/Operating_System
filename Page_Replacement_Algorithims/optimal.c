#include <stdio.h>
#define MAX 50

// Function to find the index of the page to replace
// (page which is not used for the longest time in future)
int optimal_index(int frames[], int pages[], int n, int current_index, int f) {
    int farthest = current_index;
    int pos = -1;

    for (int i = 0; i < f; i++) {
        int j;
        // Find next use of frames[i]
        for (j = current_index + 1; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        // If frame[i] is never used again, choose this immediately
        if (j == n) {
            return i;
        }
    }

    // If all are used again, but pos was not updated, replace frame 0
    if (pos == -1)
        return 0;
    else
        return pos;
}

void Optimal(int pages[], int n, int f) {
    int frames[MAX];
    int faults = 0;

    for (int i = 0; i < f; i++)
        frames[i] = -1;  // initialize frames as empty

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if page already in frame (hit)
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            // Find empty frame if any
            int pos = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame, use optimal index to replace
            if (pos == -1)
                pos = optimal_index(frames, pages, n, i, f);

            frames[pos] = pages[i];
            faults++;
        }

        // Print frames after this page reference
        printf("Frame after page %d: ", pages[i]);
        for (int j = 0; j < f; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults (Optimal): %d\n", faults);
}

int main(void) {
    int n, f, pages[MAX];

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    Optimal(pages, n, f);

    return 0;
}




/*
OUTPUT:

Enter number of pages: 12
Enter page reference string:
7
0
1
2
0
3
0
4
2
3
0
3
Enter number of frames: 3
Frame after page 7: 7 
Frame after page 0: 7 0 
Frame after page 1: 7 0 1 
Frame after page 2: 2 0 1 
Frame after page 0: 2 0 1 
Frame after page 3: 2 0 3 
Frame after page 0: 2 0 3 
Frame after page 4: 2 4 3 
Frame after page 2: 2 4 3 
Frame after page 3: 2 4 3 
Frame after page 0: 0 4 3 
Frame after page 3: 0 4 3 
Total Page Faults (Optimal): 7
Program ended with exit code: 0
*/
