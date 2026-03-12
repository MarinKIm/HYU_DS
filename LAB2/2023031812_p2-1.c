#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void perm(int *arr, int start, int end) {
    if (start == end) {
        printf("[ ");
        for (int i = 0; i <= end; i++) {
            printf(" %d ", arr[i]);
        }
        printf("]");
	printf("\n");
        return;
    }

    for (int i = start; i <= end; i++) {
        swap(&arr[start], &arr[i]);
        perm(arr, start + 1, end);
        swap(&arr[start], &arr[i]);
    }
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Error: Please provide a number as a command-line argument.\n");
        return 1;
    }

    int n = atoi(argv[1]);

    if (n <= 0) {
        printf("Error: Please provide a positive number.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    printf("The set of permutations is :\n");

    perm(arr, 0, n - 1);

    free(arr);

    return 0;
}

