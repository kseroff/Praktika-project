#ifndef FILE_UTILS_H
#define FILE_UTILS_H

extern const char* default_filename;
extern const char* sorted_filename;

int readArrayFromFile(const char* filename, int** array, int* size);
int RecordSortedArray(const char* filename, const int* array, int size);
int MakeArrayFile(int min, int max, int size, const char* filename);
int OwnArray(const char* filename);

#endif // FILE_UTILS_H
