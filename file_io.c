#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "file_io.h"

int save_boxes(const char *filename) {
    int i;
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Не удалось открыть файл для записи\n");
        return 0;
    }
    for (i = 0; i < box_count; i++) {
        fprintf(f, "%d|%s|%s|%.2f\n",
                boxes[i].number,
                boxes[i].name,
                boxes[i].category,
                boxes[i].price);
    }
    fclose(f);
    printf("Сохранено %d записей в файл %s\n", box_count, filename);
    return 1;
}

int load_boxes(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Файл %s не найден\n", filename);
        return 0;
    }
    clear_all_boxes();
    char line[512];
    int loaded = 0;
    int errors = 0;
    while (fgets(line, sizeof(line), f) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        char *number_str = strtok(line, "|");
        char *name = strtok(NULL, "|");
        char *category = strtok(NULL, "|");
        char *price_str = strtok(NULL, "|");
        if (number_str != NULL && name != NULL && category != NULL && price_str != NULL) {
            int number = atoi(number_str);
            float price = atof(price_str);
            if (find_box_by_number(number) != -1) {
                printf("Дубликат номера %d пропущен\n", number);
                errors++;
                continue;
            }
            add_box(number, name, category, price);
            loaded++;
        } else {
            printf("Некорректная строка: %s\n", line);
            errors++;
        }
    }
    fclose(f);
    printf("Загружено %d записей. Ошибок: %d\n", loaded, errors);
    return 1;
}

int append_box_to_file(const char *filename, int number, const char *name, const char *category, float price) {
    FILE *f = fopen(filename, "a");
    if (f == NULL) {
        printf("Не удалось открыть файл для добавления\n");
        return 0;
    }
    fprintf(f, "%d|%s|%s|%.2f\n", number, name, category, price);
    fclose(f);
    return 1;
}
