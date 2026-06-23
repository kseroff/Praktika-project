#include "file_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

const char* default_filename = "Array.txt";
const char* sorted_filename = "SortedArray.txt";

int readArrayFromFile(const char* filename, int** array, int* size) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        return 0;
    }

    int count = 0;
    int temp;
    while (fscanf(file, "%d", &temp) == 1) count++;

    if (count == 0) {
        printf("Файл пуст или содержит нечисловые данные\n");
        fclose(file);
        return 0;
    }

    *array = (int*)malloc(count * sizeof(int));
    if (*array == NULL) {
        printf("Ошибка выделения памяти\n");
        fclose(file);
        return 0;
    }

    rewind(file);
    for (int i = 0; i < count; i++) {
        if (fscanf(file, "%d", &(*array)[i]) != 1) {
            printf("Ошибка чтения числа из файла\n");
            free(*array);
            *array = NULL;
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    *size = count;
    return 1;
}

int RecordSortedArray(const char* filename, int* array, int size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return -1;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", array[i]);
    }

    fclose(file);
    return 0;
}

int MakeArrayFile(int min, int max, int size, const char* filename) {
    if (min >= max) {
        printf("Ошибка: нижний предел должен быть меньше верхнего.\n");
        return 0;
    }
    if (size <= 0) {
        printf("Ошибка: размер массива должен быть положительным.\n");
        return 0;
    }

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка: не удалось создать или открыть файл %s.\n", filename);
        return 0;
    }

    for (int i = 0; i < size; i++) {
        int num = rand() % (max - min + 1) + min;
        printf("%d ", num);
        fprintf(file, "%d ", num);
    }

    fclose(file);
    printf("\nФайл %s успешно создан.\n", filename);
    return 1;
}

int OwnArray(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        return 0;
    }

    printf("Введите целые числа через пробел или каждое с новой строки.\n");
    printf("Для завершения ввода введите '!' на новой строке:\n");

    char input[256];
    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        char* token = strtok(input, " \n");
        while (token != NULL) {
            if (strcmp(token, "!") == 0) {
                fclose(file);
                printf("Файл %s успешно создан.\n", filename);
                return 1;
            }

            int value;
            if (sscanf(token, "%d", &value) == 1) {
                fprintf(file, "%d ", value);
            }

            token = strtok(NULL, " \n");
        }
    }

    fclose(file);
    printf("Файл %s успешно создан.\n", filename);
    return 1;
}
