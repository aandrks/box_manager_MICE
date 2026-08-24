#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "file_io.h"

int save_boxes(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Ошибка открытия файла для записи\n");
        return 0;
    }
    for (int i = 0; i < box_count; i++) {
        Box *b = &boxes[i];
        for (int j = 0; j < b->item_count; j++) {
            fprintf(f, "%d|%s|%s|%.2f\n",
                    b->number,
                    b->items[j].name,
                    b->items[j].category,
                    b->items[j].price);
        }
    }
    fclose(f);
    printf("Сохранено товаров из %d коробок\n", box_count);
    return 1;
}

int load_boxes(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Файл %s не найден\n", filename);
        return 0;
    }
    clear_all_boxes();
    char line[512];
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = '\0';
        char *num_str = strtok(line, "|");
        char *name = strtok(NULL, "|");
        char *cat = strtok(NULL, "|");
        char *price_str = strtok(NULL, "|");
        if (!num_str || !name || !cat || !price_str) {
            printf("Некорректная строка: %s\n", line);
            continue;
        }
        int number = atoi(num_str);
        float price = atof(price_str);
        int idx = find_box(number);
        if (idx == -1) {
            add_box(number);
            idx = find_box(number);
            if (idx == -1) {
                printf("Ошибка создания коробки %d\n", number);
                continue;
            }
        }
        add_item(number, name, cat, price);
    }
    fclose(f);
    printf("Данные загружены из файла %s\n", filename);
    return 1;
}

int append_item_to_file(const char *filename, int number, const char *name, const char *category, float price) {
    FILE *f = fopen(filename, "a");
    if (!f) {
        printf("Ошибка открытия файла для добавления\n");
        return 0;
    }
    fprintf(f, "%d|%s|%s|%.2f\n", number, name, category, price);
    fclose(f);
    return 1;
}
