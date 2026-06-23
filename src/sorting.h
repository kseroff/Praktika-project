#ifndef SORTING_H
#define SORTING_H

typedef struct {
    double time_spent;
    long long swapCount;
} SortResult;

double get_time_seconds(void);
SortResult bubbleSort(int* arr, int size, int method);

#endif // SORTING_H
