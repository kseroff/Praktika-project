#include "sorting.h"
#include <time.h>

double get_time_seconds(void) {
    return (double)clock() / CLOCKS_PER_SEC;
}

SortResult bubbleSort(int* arr, int size, int method) {
    double start = get_time_seconds();
    SortResult result = { 0.0, 0, 0 };

    if (arr == NULL || size <= 1) {
        result.time_spent = get_time_seconds() - start;
        return result;
    }

    for (int i = 0; i < size - 1; i++) {
        int swapped = 0;

        for (int j = 0; j < size - i - 1; j++) {
            result.comparisonCount++;

            if ((method == SORT_ASC && arr[j] > arr[j + 1]) ||
                (method == SORT_DESC && arr[j] < arr[j + 1])) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                result.swapCount++;
                swapped = 1;
            }
        }

        if (!swapped) {
            break;
        }
    }

    result.time_spent = get_time_seconds() - start;
    return result;
}
