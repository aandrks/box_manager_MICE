#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"

Box *boxes = NULL;
int box_count = 0;
int box_capacity = 0;

void init_storage(int initial_capacity) {
    if (initial_capacity <= 0) {
        initial_capacity = 10;
    }
    boxes = (Box*)malloc(initial_capacity * sizeof(Box));
    if (boxes == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    box_capacity = initial_capacity;
    box_count = 0;
    printf("Хранилище создано на %d записей\n", box_capacity);
}

void free_storage(void) {
    if (boxes != NULL) {
        free(boxes);
        boxes = NULL;
        box_count = 0;
        box_capacity = 0;
        printf("Память освобождена\n");
    }
}

void resize_storage(void) {
    int new_capacity = box_capacity * 2;
    Box *new_boxes = (Box*)realloc(boxes, new_capacity * sizeof(Box));
    if (new_boxes == NULL) {
        printf("Ошибка расширения памяти\n");
        return;
    }
    boxes = new_boxes;
    box_capacity = new_capacity;
    printf("Хранилище расширено до %d записей\n", box_capacity);
}

void add_box(int number, const char *name, const char *category, float price) {
    if (box_count >= box_capacity) {
        resize_storage();
    }
    if (find_box_by_number(number) != -1) {
        printf("Коробка с номером %d уже существует\n", number);
        return;
    }
    (*boxes[box_count]).number = number;
    strcpy((*boxes[box_count]).name, name);
    strcpy((*boxes[box_count]).category, category);
    (*boxes[box_count]).price = price;
    box_count++;
    printf("Коробка %d добавлена. Всего: %d\n", number, box_count);
}

void display_all_boxes(void) {
    int i;
    if (box_count == 0) {
        printf("Нет записей\n");
        return;
    }
    printf("\n------------------------------------------------------------\n");
    printf("| Номер | Название                     | Категория    | Цена |\n");
    printf("------------------------------------------------------------\n");
    for (i = 0; i < box_count; i++) {
        printf("| %-5d | %-27s | %-12s | %6.2f |\n",
               (*boxes[i]).number,
               (*boxes[i]).name,
               (*boxes[i]).category,
               (*boxes[i]).price);
    }
    printf("------------------------------------------------------------\n");
    printf("Всего записей: %d\n\n", box_count);
}

int find_box_by_number(int number) {
    int i;
    for (i = 0; i < box_count; i++) {
        if ((*boxes[i]).number == number) {
            return i;
        }
    }
    return -1;
}

int find_box_by_name(const char *name) {
    int i;
    for (i = 0; i < box_count; i++) {
        if (strcmp((*boxes[i]).name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int delete_box_by_number(int number) {
    int i;
    int idx = find_box_by_number(number);
    if (idx == -1) {
        printf("Коробка с номером %d не найдена\n", number);
        return 0;
    }
    for (i = idx; i < box_count - 1; i++) {
        (*boxes[i]) = (*boxes[i + 1]);
    }
    box_count--;
    printf("Коробка %d удалена. Осталось: %d\n", number, box_count);
    return 1;
}

void clear_all_boxes(void) {
    box_count = 0;
    printf("Все записи очищены\n");
}
