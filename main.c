#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "file_io.h"
#include "utils.h"

#define FILENAME "boxes.txt"
#define INITIAL_CAPACITY 10

int main() {
    int choice;
    int number;
    char name[MAX_NAME];
    char category[MAX_CAT];
    float price;

    printf("\n=== СИСТЕМА УЧЁТА ТОВАРОВ В КОРОБКАХ ===\n");
    init_storage(INITIAL_CAPACITY);

    printf("Загрузка данных из файла...\n");
    load_boxes(FILENAME);

    do {
        printf("\n--- МЕНЮ ---\n");
        printf("1. Добавить коробку\n");
        printf("2. Показать все коробки\n");
        printf("3. Найти по номеру\n");
        printf("4. Найти по названию\n");
        printf("5. Удалить по номеру\n");
        printf("6. Сохранить в файл\n");
        printf("7. Загрузить из файла\n");
        printf("8. Очистить все\n");
        printf("9. Информация о хранилище\n");
        printf("0. Выход\n");
        printf("Записей: %d | Ёмкость: %d\n", box_count, box_capacity);

        choice = get_int_input("Выберите действие: ");
        clear_input_buffer();

        switch (choice) {
            case 1: {
                printf("ДОБАВЛЕНИЕ\n");
                number = get_int_input("Номер коробки: ");
                if (find_box_by_number(number) != -1) {
                    printf("Коробка с номером %d уже существует\n", number);
                    break;
                }
                get_string_input("Название товара: ", name, MAX_NAME);
                get_string_input("Категория: ", category, MAX_CAT);
                price = get_float_input("Цена: ");
                add_box(number, name, category, price);
                break;
            }
            case 2:
                display_all_boxes();
                break;
            case 3: {
                number = get_int_input("Введите номер: ");
                int idx = find_box_by_number(number);
                if (idx != -1) {
                    printf("Номер: %d\n", (*boxes[idx]).number);
                    printf("Название: %s\n", (*boxes[idx]).name);
                    printf("Категория: %s\n", (*boxes[idx]).category);
                    printf("Цена: %.2f\n", (*boxes[idx]).price);
                } else {
                    printf("Не найдено\n");
                }
                break;
            }
            case 4: {
                get_string_input("Введите название: ", name, MAX_NAME);
                int idx = find_box_by_name(name);
                if (idx != -1) {
                    printf("Номер: %d\n", (*boxes[idx]).number);
                    printf("Название: %s\n", (*boxes[idx]).name);
                    printf("Категория: %s\n", (*boxes[idx]).category);
                    printf("Цена: %.2f\n", (*boxes[idx]).price);
                } else {
                    printf("Не найдено\n");
                }
                break;
            }
            case 5: {
                number = get_int_input("Номер для удаления: ");
                delete_box_by_number(number);
                break;
            }
            case 6:
                save_boxes(FILENAME);
                break;
            case 7:
                load_boxes(FILENAME);
                break;
            case 8:
                printf("Очистить все? (1-да / 0-нет): ");
                int confirm;
                scanf("%d", &confirm);
                clear_input_buffer();
                if (confirm == 1) {
                    clear_all_boxes();
                }
                break;
            case 9:
                printf("Всего записей: %d\n", box_count);
                printf("Ёмкость: %d\n", box_capacity);
                printf("Заполнено: %.1f%%\n", (float)box_count / box_capacity * 100);
                break;
            case 0:
                printf("Выход. Сохранение...\n");
                save_boxes(FILENAME);
                break;
            default:
                printf("Неверный выбор\n");
        }
    } while (choice != 0);

    free_storage();
    return 0;
}
