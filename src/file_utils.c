#define _CRT_SECURE_NO_WARNINGS

#include "file_utils.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* default_filename = "Array.txt";
const char* sorted_filename = "SortedArray.txt";

int readArrayFromFile(const char* filename, int** array, int* size) {
    FILE* file;
    char token[256];
    int count = 0;
    int value;
    int index = 0;

    if (filename == NULL || array == NULL || size == NULL) {
        printf("Ошибка: некорректные аргументы функции чтения файла.\n");
        return 0;
    }

    *array = NULL;
    *size = 0;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        return 0;
    }

    while (fscanf(file, "%255s", token) == 1) {
        if (!parse_int(token, &value)) {
            printf("Ошибка: файл содержит некорректное значение: %s\n", token);
            fclose(file);
            return 0;
        }
        count++;
    }

    if (count == 0) {
        printf("Файл пуст или не содержит чисел.\n");
        fclose(file);
        return 0;
    }

    *array = (int*)malloc((size_t)count * sizeof(int));
    if (*array == NULL) {
        printf("Ошибка выделения памяти.\n");
        fclose(file);
        return 0;
    }

    rewind(file);
    while (fscanf(file, "%255s", token) == 1) {
        if (!parse_int(token, &value)) {
            printf("Ошибка чтения числа из файла.\n");
            free(*array);
            *array = NULL;
            fclose(file);
            return 0;
        }

        (*array)[index] = value;
        index++;
    }

    fclose(file);
    *size = count;
    return 1;
}

int RecordSortedArray(const char* filename, const int* array, int size) {
    FILE* file;

    if (filename == NULL || array == NULL || size <= 0) {
        printf("Ошибка: некорректные данные для записи массива.\n");
        return 0;
    }

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка: не удалось создать файл %s\n", filename);
        return 0;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d", array[i]);
        if (i + 1 < size) {
            fprintf(file, " ");
        }
    }
    fprintf(file, "\n");

    fclose(file);
    printf("Массив успешно записан в файл %s\n", filename);
    return 1;
}

int MakeArrayFile(int min, int max, int size, const char* filename) {
    FILE* file;

    if (filename == NULL) {
        printf("Ошибка: имя файла не задано.\n");
        return 0;
    }

    if (min >= max) {
        printf("Ошибка: нижний предел должен быть меньше верхнего.\n");
        return 0;
    }

    if (size <= 0) {
        printf("Ошибка: размер массива должен быть положительным.\n");
        return 0;
    }

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка: не удалось создать или открыть файл %s.\n", filename);
        return 0;
    }

    for (int i = 0; i < size; i++) {
        int num = rand() % (max - min + 1) + min;
        printf("%d", num);
        fprintf(file, "%d", num);

        if (i + 1 < size) {
            printf(" ");
            fprintf(file, " ");
        }
    }

    fprintf(file, "\n");
    fclose(file);
    printf("\nФайл %s успешно создан.\n", filename);
    return 1;
}

int OwnArray(const char* filename) {
    FILE* file;
    char input[256];
    int has_numbers = 0;

    if (filename == NULL) {
        printf("Ошибка: имя файла не задано.\n");
        return 0;
    }

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        return 0;
    }

    printf("Введите целые числа через пробел или каждое с новой строки.\n");
    printf("Для завершения ввода введите '!' на новой строке:\n");

    while (1) {
        char* token;

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        token = strtok(input, " \t\r\n");
        while (token != NULL) {
            int value;

            if (strcmp(token, "!") == 0) {
                fclose(file);
                if (!has_numbers) {
                    printf("Ошибка: массив не содержит чисел.\n");
                    remove(filename);
                    return 0;
                }
                printf("Файл %s успешно создан.\n", filename);
                return 1;
            }

            if (!parse_int(token, &value)) {
                printf("Ошибка: '%s' не является целым числом. Ввод массива отменён.\n", token);
                fclose(file);
                remove(filename);
                return 0;
            }

            if (has_numbers) {
                fprintf(file, " ");
            }
            fprintf(file, "%d", value);
            has_numbers = 1;

            token = strtok(NULL, " \t\r\n");
        }
    }

    fclose(file);

    if (!has_numbers) {
        printf("Ошибка: массив не содержит чисел.\n");
        remove(filename);
        return 0;
    }

    printf("Файл %s успешно создан.\n", filename);
    return 1;
}
