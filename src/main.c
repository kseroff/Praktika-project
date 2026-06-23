#include "sorting.h"
#include "file_utils.h"
#include "utils.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");

    clear_screen();
    srand((unsigned)time(NULL));

    char current_filename[100] = "Array.txt";
    int size = 0;
    int* current_array = NULL;

    while (1) {
        printf("\nМеню:\n");
        printf("1. Создать массив с клавиатуры\n");
        printf("2. Сгенерировать случайный массив\n");
        printf("3. Загрузить массив из файла\n");
        printf("4. Отсортировать текущий массив\n");
        printf("5. Выйти\n");
        printf("Выберите действие: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода. Пожалуйста, введите число.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1: {
            while (getchar() != '\n');
            printf("Введите имя файла (по умолчанию %s): ", default_filename);

            char filename_buffer[100];
            fgets(filename_buffer, sizeof(filename_buffer), stdin);
            filename_buffer[strcspn(filename_buffer, "\n")] = '\0';

            if (strlen(filename_buffer) > 0) {
                strcpy(current_filename, filename_buffer);
            }

            if (OwnArray(current_filename)) {
                if (current_array) {
                    free(current_array);
                    current_array = NULL;
                }

                if (readArrayFromFile(current_filename, &current_array, &size)) {
                    printf("Массив успешно загружен. Размер: %d\n", size);
                }
                else {
                    printf("Не удалось загрузить массив из файла.\n");
                    current_array = NULL;
                    size = 0;
                }
            }

            printf("Нажмите Enter чтобы продолжить.\n");
            getchar();
            clear_screen();
            break;
        }

        case 2: {
            int size_input, min, max;

            printf("Введите размер массива: ");
            if (scanf("%d", &size_input) != 1 || size_input <= 0 || checkForExtraChars()) {
                printf("Неверный размер массива.\n");
                while (getchar() != '\n');
                continue;
            }

            printf("Введите min: ");
            if (scanf("%d", &min) != 1 || checkForExtraChars()) {
                printf("Неверный min.\n");
                while (getchar() != '\n');
                continue;
            }

            printf("Введите max: ");
            if (scanf("%d", &max) != 1 || max <= min || checkForExtraChars()) {
                printf("Неверный max.\n");
                while (getchar() != '\n');
                continue;
            }

            if (MakeArrayFile(min, max, size_input, current_filename)) {
                if (current_array) {
                    free(current_array);
                    current_array = NULL;
                }

                if (readArrayFromFile(current_filename, &current_array, &size)) {
                    printf("Массив успешно создан и загружен. Размер: %d\n", size);
                }
                else {
                    printf("Не удалось загрузить массив из файла.\n");
                    current_array = NULL;
                    size = 0;
                }
            }

            printf("Нажмите Enter чтобы продолжить.\n");
            getchar();
            clear_screen();
            break;
        }

        case 3: {
            while (getchar() != '\n');

            printf("Введите имя файла: ");
            char filename_buffer[100];
            fgets(filename_buffer, sizeof(filename_buffer), stdin);
            filename_buffer[strcspn(filename_buffer, "\n")] = '\0';

            if (current_array) {
                free(current_array);
                current_array = NULL;
            }

            if (readArrayFromFile(filename_buffer, &current_array, &size)) {
                strcpy(current_filename, filename_buffer);
                printf("Массив успешно загружен. Размер: %d\n", size);
            }
            else {
                printf("Не удалось загрузить массив из файла %s.\n", filename_buffer);
                current_array = NULL;
                size = 0;
            }

            printf("Нажмите Enter чтобы продолжить.\n");
            getchar();
            clear_screen();
            break;
        }

        case 4: {
            if (!current_array || size == 0) {
                printf("Нет загруженного массива для сортировки.\n");
                break;
            }

            printf("Тип сортировки:\n1. По убыванию\n2. По возрастанию\nВыберите: ");
            int method;
            if (scanf("%d", &method) != 1 || (method != 1 && method != 2) || checkForExtraChars()) {
                printf("Неверный выбор.\n");
                while (getchar() != '\n');
                continue;
            }

            SortResult sortResult = bubbleSort(current_array, size, method);

            printf("Отсортированный массив:\n");
            for (int i = 0; i < size; i++) {
                printf("%d ", current_array[i]);
            }
            printf("\nВремя выполнения: %.6f секунд\n", sortResult.time_spent);
            printf("Количество перестановок: %lld\n", sortResult.swapCount);

            int result = RecordSortedArray(sorted_filename, current_array, size);
            if (result == 0) {
                printf("Файл успешно записан\n");
            } else {
                printf("Ошибка записи файла\n");
                return 1;
            }
            printf("Нажмите Enter чтобы продолжить.\n");
            getchar();
            clear_screen();
            break;
        }

        case 5:
            clear_screen();
            printf("\n\n\n\n==========================\nРабота программы завершена.\nЖелаем хорошего дня.\n==========================\n\n\n\n");
            if (current_array) free(current_array);
            return 0;

        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
}
