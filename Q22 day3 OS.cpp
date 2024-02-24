#include <stdio.h>

#define MAX_BLOCKS 50
#define MAX_REQUESTS 50

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n], i, j, index;

    for (i = 0; i < n; i++)
        allocation[i] = -1;

    for (i = 0; i < n; i++) {
        index = -1;
        for (j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (index == -1)
                    index = j;
                else if (blockSize[j] < blockSize[index])
                    index = j;
            }
        }

        if (index != -1) {
            allocation[i] = index;
            blockSize[index] -= processSize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (i = 0; i < n; i++) {
        printf("%d \t\t%d \t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_REQUESTS], m, n;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter the size of each memory block:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the size of each process:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &processSize[i]);

    bestFit(blockSize, m, processSize, n);

    return 0;
}
