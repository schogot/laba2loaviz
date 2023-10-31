#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Функция сортировки Шелла
void shell(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Рекурсивная функция сортировки QuickSort
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        int pi = i + 1;

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Функция сравнения для qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main(void) {
    setlocale(LC_ALL, "Russian");
    int count = 10000; // Количество элементов в массиве

    int* items_shell = (int*)malloc(count * sizeof(int));
    int* items_qs = (int*)malloc(count * sizeof(int));
    int* items_qsort = (int*)malloc(count * sizeof(int));

    for (int i = 0; i < count; i++) {
        int value = rand() % 1000;
        items_shell[i] = value;
        items_qs[i] = value;
        items_qsort[i] = value;
    }

    clock_t start, end;
    double cpu_time_used;

    // Оценка времени работы алгоритма сортировки Шелла
    start = clock();
    shell(items_shell, count);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время работы алгоритма сортировки Шелла на случайном наборе значений: %f секунд\n", cpu_time_used);

    // Оценка времени работы алгоритма QuickSort (qs)
    start = clock();
    quicksort(items_qs, 0, count - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время работы алгоритма QuickSort (qs) на случайном наборе значений: %f секунд\n", cpu_time_used);

    // Оценка времени работы функции qsort
    start = clock();
    qsort(items_qsort, count, sizeof(int), compare);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время работы функции qsort на случайном наборе значений: %f секунд\n", cpu_time_used);

    free(items_shell);
    free(items_qs);
    free(items_qsort);

    return 0;
}