#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"

Box *boxes = NULL;
int box_count = 0;
int box_capacity = 0;

void init_storage(int initial_capacity) {
    if (initial_capacity <= 0) initial_capacity = 10;
    boxes = (Box*)malloc(initial_capacity * sizeof(Box));
    if (!boxes) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    box_capacity = initial_capacity;
    box_count = 0;
    printf("Хранилище создано на %d коробок\n", box_capacity);
}

void free_storage(void) {
    for (int i = 0; i < box_count; i++) {
        free(boxes[i].items);
    }
    free(boxes);
    boxes = NULL;
    box_count = 0;
    box_capacity = 0;
    printf("Память освобождена\n");
}

void resize_boxes(void) {
    int new_cap = box_capacity * 2;
    Box *new_boxes = (Box*)realloc(boxes, new_cap * sizeof(Box));
    if (!new_boxes) {
        printf("Ошибка расширения хранилища коробок\n");
        return;
    }
    boxes = new_boxes;
    box_capacity = new_cap;
    printf("Хранилище расширено до %d коробок\n", box_capacity);
}

void resize_items(Box *box) {
    int new_cap = box->item_capacity * 2;
    Item *new_items = (Item*)realloc(box->items, new_cap * sizeof(Item));
    if (!new_items) {
        printf("Ошибка расширения списка товаров\n");
        return;
    }
    box->items = new_items;
    box->item_capacity = new_cap;
}

int add_box(int number) {
    if (find_box(number) != -1) {
        printf("Коробка с номером %d уже существует\n", number);
        return 0;
    }
    if (box_count >= box_capacity) resize_boxes();
    boxes[box_count].number = number;
    boxes[box_count].item_count = 0;
    boxes[box_count].item_capacity = INITIAL_ITEMS;
    boxes[box_count].items = (Item*)malloc(INITIAL_ITEMS * sizeof(Item));
    if (!boxes[box_count].items) {
        printf("Ошибка выделения памяти для товаров\n");
        return 0;
    }
    box_count++;
    printf("Коробка %d создана\n", number);
    return 1;
}

int find_box(int number) {
    for (int i = 0; i < box_count; i++) {
        if (boxes[i].number == number) return i;
    }
    return -1;
}

void add_item(int box_number, const char *name, const char *category, float price) {
    int idx = find_box(box_number);
    if (idx == -1) {
        printf("Коробка %d не найдена\n", box_number);
        return;
    }
    Box *b = &boxes[idx];
    if (b->item_count >= b->item_capacity) resize_items(b);
    strcpy(b->items[b->item_count].name, name);
    strcpy(b->items[b->item_count].category, category);
    b->items[b->item_count].price = price;
    b->item_count++;
    printf("Товар '%s' добавлен в коробку %d\n", name, box_number);
}

void display_box(int box_number) {
    int idx = find_box(box_number);
    if (idx == -1) {
        printf("Коробка %d не найдена\n", box_number);
        return;
    }
    Box *b = &boxes[idx];
    if (b->item_count == 0) {
        printf("Коробка %d пуста\n", box_number);
        return;
    }
    printf("\nСодержимое коробки %d:\n", box_number);
    printf("------------------------------------------------------------\n");
    printf("| № | Название                     | Категория    | Цена    |\n");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < b->item_count; i++) {
        printf("| %-2d| %-27s | %-12s | %6.2f |\n",
               i+1, b->items[i].name, b->items[i].category, b->items[i].price);
    }
    printf("------------------------------------------------------------\n");
}

void display_all_boxes(void) {
    if (box_count == 0) {
        printf("Нет коробок\n");
        return;
    }
    for (int i = 0; i < box_count; i++) {
        display_box(boxes[i].number);
        printf("\n");
    }
}

int delete_box(int number) {
    int idx = find_box(number);
    if (idx == -1) {
        printf("Коробка %d не найдена\n", number);
        return 0;
    }
    free(boxes[idx].items);
    for (int i = idx; i < box_count - 1; i++) {
        boxes[i] = boxes[i + 1];
    }
    box_count--;
    printf("Коробка %d удалена\n", number);
    return 1;
}

int delete_item(int box_number, int item_index) {
    int idx = find_box(box_number);
    if (idx == -1) {
        printf("Коробка %d не найдена\n", box_number);
        return 0;
    }
    Box *b = &boxes[idx];
    if (item_index < 0 || item_index >= b->item_count) {
        printf("Неверный номер товара\n");
        return 0;
    }
    for (int i = item_index; i < b->item_count - 1; i++) {
        b->items[i] = b->items[i + 1];
    }
    b->item_count--;
    printf("Товар удалён из коробки %d\n", box_number);
    return 1;
}

void clear_all_boxes(void) {
    for (int i = 0; i < box_count; i++) {
        free(boxes[i].items);
    }
    box_count = 0;
    printf("Все данные очищены\n");
}
