#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *num = (int *)malloc(sizeof(int));

    if (num == NULL) {
        return 1;
    }

    printf("Enter the multiplication table number: ");
    if (scanf("%d", num) != 1) {
        printf("Invalid input. Please enter a number!\n");
        free(num);
        return 0;
    }

   printf("== %d times table ==\n", *num);	
    for (int i = 1; i <= 9; i++) {
        printf("%d x %d = %d\n", *num, i, (*num) * i);
    }

   
    free(num);

    return 0;
}
