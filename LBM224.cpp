#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void shell(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] < temp; j -= gap) {  // Fixed the comparison condition
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;  // Fixed the comparison logic
}

int main(void) {
    setlocale(LC_ALL, "Russian");
    int count = 10000; // Количество элементов в массиве

    int* items_shell = (int*)malloc(count * sizeof(int));
    int* items_qs = (int*)malloc(count * sizeof(int));
    int* items_qsort = (int*)malloc(count * sizeof(int));

    // Генерация убывающе-возрастающего набора значений массива
    for (int i = 0; i < count; i++) {
        items_shell[i] = (i < count / 2) ? count - i : i - count / 2;
        items_qs[i] = items_shell[i];
        items_qsort[i] = items_shell[i];
    }

    clock_t start, end;

    // Сортировка Шелла
    start = clock();
    shell(items_shell, count);
    end = clock();
    double cpu_time_used_shell = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время работы алгоритма сортировки Шелла на убывающе-возрастающем наборе значений: %f секунд\n", cpu_time_used_shell);

    // QuickSort (qs)
    start = clock();
    qsort(items_qs, count, sizeof(int), compare);
    end = clock();
    double cpu_time_used_qs = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время работы алгоритма QuickSort на убывающе-возрастающем наборе значений: %f секунд\n", cpu_time_used_qs);

    // qsort
    start = clock();
    qsort(items_qsort, count, sizeof(int), compare);
    end = clock();
    double cpu_time_used_qsort = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время работы функции qsort на убывающе-возрастающем наборе значений: %f секунд\n", cpu_time_used_qsort);

    free(items_shell);
    free(items_qs);
    free(items_qsort);

    return 0;
}