#include "sorting.h"
#include <sys/time.h>
#include <stdlib.h>

double get_time_seconds(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
}

SortResult bubbleSort(int* arr, int size, int method) {
    double start = get_time_seconds();
    SortResult result = { 0, 0 };

    for (int i = 0; i < size - 1; i++) {
        int swapped = 0;

        for (int j = 0; j < size - i - 1; j++) {
            if (method == 2) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    result.swapCount++;
                    swapped = 1;
                }
            }
            else if (method == 1) {
                if (arr[j] < arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    result.swapCount++;
                    swapped = 1;
                }
            }
        }

        if (!swapped) {
            break;
        }
    }

    double end = get_time_seconds();
    result.time_spent = end - start;
    return result;
}
