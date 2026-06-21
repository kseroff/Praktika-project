#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <locale.h>

void clear_screen() {
    if (getenv("TERM")) {
        system("clear");
    }
    else {
        printf("\n\n\n\n\n");
    }
}

int checkForExtraChars() {
    int c = getchar();
    return (c != '\n' && c != EOF);
}

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
            printf("Введите имя файла (по умолчанию %s): ", current_filename);

            char filename_buffer[100];
            fgets(filename_buffer, sizeof(filename_buffer), stdin);
            filename_buffer[strcspn(filename_buffer, "\n")] = '\0';

            if (strlen(filename_buffer) > 0) {
                strcpy(current_filename, filename_buffer);
            }

            // OwnArray(current_filename);
            // readArrayFromFile(current_filename, &current_array, &size);

            printf("Нажмите Enter чтобы продолжить.\n");
            getchar();
            clear_screen();
            break;
        }

        case 2: {
            printf("Введите размер массива: ");
            if (scanf("%d", &size) != 1 || size <= 0 || checkForExtraChars()) {
                printf("Неверный размер массива.\n");
                while (getchar() != '\n');
                continue;
            }

            int min, max;
            printf("Введите диапазон (min max): ");
            if (scanf("%d %d", &min, &max) != 2 || min >= max || checkForExtraChars()) {
                printf("Неверный диапазон.\n");
                while (getchar() != '\n');
                continue;
            }

            // MakeArrayFile(min, max, size, current_filename);
            // readArrayFromFile(current_filename, &current_array, &size);

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

            // readArrayFromFile(filename_buffer, &current_array, &size);

            if (current_array) strcpy(current_filename, filename_buffer);
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

            // SortResult sortResult = bubbleSort(current_array, size, method);
            // RecordSortedArray(sorted_filename, current_array, size);

            printf("Нажмите Enter чтобы продолжить.\n");
            getchar();
            clear_screen();
            break;
        }

        case 5:
            clear_screen();
            printf("\n\n\n\n\nРабота программы завершена.\nЖелаем хорошего дня.\n\n\n\n\n");
            if (current_array) free(current_array);
            return 0;

        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
}