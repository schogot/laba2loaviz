#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void shell(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] < temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int compare(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}

int main(void) {
    setlocale(LC_ALL, "Russian");
    int count = 10000; // Количество элементов в массиве

    int* items_shell = (int*)malloc(count * sizeof(int));
    int* items_qs = (int*)malloc(count * sizeof(int));
    int* items_qsort = (int*)malloc(count * sizeof(int));

    // Генерация убывающего набора значений массива
    for (int i = 0; i < count; i++) {
        items_shell[i] = count - i;
        items_qs[i] = count - i;
        items_qsort[i] = count - i;
    }

    clock_t start, end;

    // Сортировка Шелла
    start = clock();
    shell(items_shell, count);
    end = clock();
    double cpu_time_used_shell = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время работы алгоритма сортировки Шелла на убывающем наборе значений: %f секунд\n", cpu_time_used_shell);

    // QuickSort (qs)
    start = clock();
    qsort(items_qs, count, sizeof(int), compare);
    end = clock();
    double cpu_time_used_qs = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время работы алгоритма QuickSort на убывающем наборе значений: %f секунд\n", cpu_time_used_qs);

    // qsort
    start = clock();
    qsort(items_qsort, count, sizeof(int), compare);
    end = clock();
    double cpu_time_used_qsort = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время работы функции qsort на убывающем наборе значений: %f секунд\n", cpu_time_used_qsort);

    free(items_shell);
    free(items_qs);
    free(items_qsort);

    return 0;
}