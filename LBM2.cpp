#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int sizes[] = { 100, 200, 400, 1000, 2000, 4000, 10000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int k = 0; k < num_sizes; k++)
    {
        int size = sizes[k];

        int** a = (int**)malloc(size * sizeof(int*));
        int** b = (int**)malloc(size * sizeof(int*));
        int** c = (int**)malloc(size * sizeof(int*));

        for (int i = 0; i < size; i++) {
            a[i] = (int*)malloc(size * sizeof(int));
            b[i] = (int*)malloc(size * sizeof(int));
            c[i] = (int*)malloc(size * sizeof(int));
        }

        clock_t start, end;

        // Заполнение матриц случайными числами
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                a[i][j] = rand() % 100 + 1;
                b[i][j] = rand() % 100 + 1;
            }
        }

        start = clock();

        // Выполнение умножения матриц
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int elem_c = 0;
                for (int r = 0; r < size; r++) {
                    elem_c = elem_c + a[i][r] * b[r][j];
                    c[i][j] = elem_c;
                }
            }
        }

        end = clock();

        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Matrix size: %dx%d, Time: %f seconds\n", size, size, cpu_time_used);

        for (int i = 0; i < size; i++) {
            free(a[i]);
            free(b[i]);
            free(c[i]);
        }

        free(a);
        free(b);
        free(c);
    }

    return 0;
}