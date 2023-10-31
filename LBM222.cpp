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

// Функция для обмена элементов
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Итеративная функция сортировки QuickSort
void quicksort(int arr[], int low, int high) {
    int* stack = (int*)malloc(sizeof(int) * (high - low + 1));
    int top = -1;

    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0) {
        high = stack[top--];
        low = stack[top--];

        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }

        swap(&arr[i + 1], &arr[high]);

        int pi = i + 1;

        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }

        if (low < pi - 1) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }
    }

    free(stack);
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

    if (items_shell == NULL || items_qs == NULL || items_qsort == NULL) {
        printf("Ошибка выделения памяти.\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        items_shell[i] = i;
        items_qs[i] = i;
        items_qsort[i] = i;
    }

    clock_t start, end;
    double cpu_time_used;

    // Оценка времени работы алгоритма сортировки Шелла
    start = clock();
    shell(items_shell, count);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время работы алгоритма сортировки Шелла на массиве возрастающей последовательности: %f секунд\n", cpu_time_used);

    // Оценка времени работы итеративного алгоритма QuickSort (qs)
    start = clock();
    quicksort(items_qs, 0, count - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время работы итеративного алгоритма QuickSort (qs) на массиве возрастающей последовательности: %f секунд\n", cpu_time_used);

    // Оценка времени работы функции qsort
    start = clock(); 
    qsort(items_qsort, count, sizeof(int), compare);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время работы функции qsort на массиве возрастающей последовательности: %f секунд\n", cpu_time_used);

    free(items_shell);
    free(items_qs);
    free(items_qsort);

    return 0;
}