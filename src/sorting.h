#ifndef SORTING_H
#define SORTING_H

#define SORT_DESC 1
#define SORT_ASC 2

typedef struct {
    double time_spent;
    long long swapCount;
    long long comparisonCount;
} SortResult;

double get_time_seconds(void);
SortResult bubbleSort(int* arr, int size, int method);

#endif // SORTING_H
