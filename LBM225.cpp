#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int compare(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

int main(void)
{
    setlocale(LC_ALL, "russian");
    int count = 10000; // Количество элементов в массиве

    int* items = (int*)malloc(count * sizeof(int));

    srand(time(NULL));

    // Заполнение массива случайными значениями
    for (int i = 0; i < count; i++) {
        items[i] = rand();
    }

    clock_t start, end;

    start = clock();
    qsort(items, count, sizeof(int), compare); // Вызов стандартной функции qsort
    end = clock();

    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время работы стандартной функции qsort: %f секунд\n", cpu_time_used);

    free(items);

    return 0;
}