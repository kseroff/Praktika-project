#define _CRT_SECURE_NO_WARNINGS

#include "sorting.h"
#include "file_utils.h"
#include "utils.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_FILENAME_LENGTH 100

static void set_current_filename(char* destination, size_t destination_size, const char* source) {
    if (destination == NULL || destination_size == 0 || source == NULL) {
        return;
    }

    snprintf(destination, destination_size, "%s", source);
}

static void pause_and_clear(void) {
    printf("Нажмите Enter чтобы продолжить.");
    wait_for_enter();
    clear_screen();
}

int main(void) {
    char current_filename[MAX_FILENAME_LENGTH] = "Array.txt";
    int size = 0;
    int* current_array = NULL;

    setlocale(LC_ALL, "");
    srand((unsigned)time(NULL));

    clear_screen();

    while (1) {
        int choice;

        printf("\nМеню:\n");
        printf("1. Создать массив с клавиатуры\n");
        printf("2. Сгенерировать случайный массив\n");
        printf("3. Загрузить массив из файла\n");
        printf("4. Отсортировать текущий массив\n");
        printf("5. Выйти\n");

        if (!read_int_from_stdin("Выберите действие: ", &choice)) {
            printf("Ошибка ввода. Пожалуйста, введите число.\n");
            pause_and_clear();
            continue;
        }

        switch (choice) {
        case 1: {
            char filename_buffer[MAX_FILENAME_LENGTH];

            printf("Введите имя файла (по умолчанию %s): ", default_filename);
            if (!read_line(filename_buffer, sizeof(filename_buffer))) {
                printf("Ошибка чтения имени файла.\n");
                pause_and_clear();
                break;
            }

            if (strlen(filename_buffer) > 0) {
                set_current_filename(current_filename, sizeof(current_filename), filename_buffer);
            } else {
                set_current_filename(current_filename, sizeof(current_filename), default_filename);
            }

            if (OwnArray(current_filename)) {
                free(current_array);
                current_array = NULL;

                if (readArrayFromFile(current_filename, &current_array, &size)) {
                    printf("Массив успешно загружен. Размер: %d\n", size);
                } else {
                    printf("Не удалось загрузить массив из файла.\n");
                    current_array = NULL;
                    size = 0;
                }
            }

            pause_and_clear();
            break;
        }

        case 2: {
            int size_input;
            int min;
            int max;

            if (!read_int_from_stdin("Введите размер массива: ", &size_input) || size_input <= 0) {
                printf("Неверный размер массива.\n");
                pause_and_clear();
                break;
            }

            if (!read_int_from_stdin("Введите min: ", &min)) {
                printf("Неверный min.\n");
                pause_and_clear();
                break;
            }

            if (!read_int_from_stdin("Введите max: ", &max) || max <= min) {
                printf("Неверный max.\n");
                pause_and_clear();
                break;
            }

            if (MakeArrayFile(min, max, size_input, current_filename)) {
                free(current_array);
                current_array = NULL;

                if (readArrayFromFile(current_filename, &current_array, &size)) {
                    printf("Массив успешно создан и загружен. Размер: %d\n", size);
                } else {
                    printf("Не удалось загрузить массив из файла.\n");
                    current_array = NULL;
                    size = 0;
                }
            }

            pause_and_clear();
            break;
        }

        case 3: {
            char filename_buffer[MAX_FILENAME_LENGTH];

            printf("Введите имя файла: ");
            if (!read_line(filename_buffer, sizeof(filename_buffer))) {
                printf("Ошибка чтения имени файла.\n");
                pause_and_clear();
                break;
            }

            if (strlen(filename_buffer) == 0) {
                printf("Имя файла не может быть пустым.\n");
                pause_and_clear();
                break;
            }

            free(current_array);
            current_array = NULL;

            if (readArrayFromFile(filename_buffer, &current_array, &size)) {
                set_current_filename(current_filename, sizeof(current_filename), filename_buffer);
                printf("Массив успешно загружен. Размер: %d\n", size);
            } else {
                printf("Не удалось загрузить массив из файла %s.\n", filename_buffer);
                current_array = NULL;
                size = 0;
            }

            pause_and_clear();
            break;
        }

        case 4: {
            int method;
            SortResult sortResult;

            if (current_array == NULL || size == 0) {
                printf("Нет загруженного массива для сортировки.\n");
                pause_and_clear();
                break;
            }

            printf("Тип сортировки:\n1. По убыванию\n2. По возрастанию\n");
            if (!read_int_from_stdin("Выберите: ", &method) ||
                (method != SORT_DESC && method != SORT_ASC)) {
                printf("Неверный выбор.\n");
                pause_and_clear();
                break;
            }

            sortResult = bubbleSort(current_array, size, method);

            printf("Отсортированный массив:\n");
            for (int i = 0; i < size; i++) {
                printf("%d", current_array[i]);
                if (i + 1 < size) {
                    printf(" ");
                }
            }

            printf("\nВремя выполнения: %.6f секунд\n", sortResult.time_spent);
            printf("Количество сравнений: %lld\n", sortResult.comparisonCount);
            printf("Количество перестановок: %lld\n", sortResult.swapCount);

            if (!RecordSortedArray(sorted_filename, current_array, size)) {
                printf("Не удалось записать отсортированный массив.\n");
            }

            pause_and_clear();
            break;
        }

        case 5:
            clear_screen();
            printf("\n==========================\n");
            printf("Работа программы завершена.\n");
            printf("Желаем хорошего дня.\n");
            printf("==========================\n");
            free(current_array);
            return 0;

        default:
            printf("Неверный выбор. Попробуйте снова.\n");
            pause_and_clear();
            break;
        }
    }
}
