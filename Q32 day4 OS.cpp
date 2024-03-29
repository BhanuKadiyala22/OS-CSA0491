#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

int main() {
    int frames[MAX_FRAMES], pages[MAX_PAGES], last_used[MAX_FRAMES];
    int num_frames, num_pages;
    int page_faults = 0, next_frame = 0;

    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);

    printf("Enter the number of pages: ");
    scanf("%d", &num_pages);

    printf("Enter the page reference string: ");
    for (int i = 0; i < num_pages; i++)
        scanf("%d", &pages[i]);

    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        last_used[i] = 0;
    }

    printf("\nPage Reference String: ");
    for (int i = 0; i < num_pages; i++)
        printf("%d ", pages[i]);

    printf("\n\nPage Faults:\n");
    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                last_used[j] = i + 1;
                break;
            }
        }

        if (!found) {
            int min = 0;
            for (int j = 1; j < num_frames; j++) {
                if (last_used[j] < last_used[min])
                    min = j;
            }

            printf("Page %d -> ", page);
            frames[min] = page;
            last_used[min] = i + 1;
            page_faults++;

            for (int j = 0; j < num_frames; j++) {
                if (frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf("x ");
            }
            printf("\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}
