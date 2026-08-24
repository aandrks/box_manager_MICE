#include <stdio.h>
#include <string.h>
#include "data.h"
#include "file_io.h"
#include "utils.h"

#define FILENAME "boxes.txt"

int main() {
    int choice, num, idx;
    char name[MAX_NAME], cat[MAX_CAT];
    float price;

    init_storage(10);
    load_boxes(FILENAME);

    do {
        printf("\n--- СИСТЕМА УЧЁТА КОРОБОК ---\n");
        printf("1. Создать коробку\n");
        printf("2. Добавить товар в коробку\n");
        printf("3. Показать содержимое коробки\n");
        printf("4. Показать все коробки\n");
        printf("5. Удалить коробку\n");
        printf("6. Удалить товар из коробки\n");
        printf("7. Сохранить в файл\n");
        printf("8. Загрузить из файла\n");
        printf("9. Очистить все\n");
        printf("0. Выход\n");
        printf("Коробок: %d\n", box_count);
        choice = get_int_input("Выберите действие: ");

        switch (choice) {
            case 1:
                num = get_int_input("Номер новой коробки: ");
                add_box(num);
                break;
            case 2:
                num = get_int_input("Номер коробки: ");
                clear_input_buffer();
                get_string_input("Название товара: ", name, MAX_NAME);
                get_string_input("Категория: ", cat, MAX_CAT);
                price = get_float_input("Цена: ");
                add_item(num, name, cat, price);
                break;
            case 3:
                num = get_int_input("Номер коробки: ");
                display_box(num);
                break;
            case 4:
                display_all_boxes();
                break;
            case 5:
                num = get_int_input("Номер коробки для удаления: ");
                delete_box(num);
                break;
            case 6:
                num = get_int_input("Номер коробки: ");
                display_box(num);
                idx = get_int_input("Номер товара для удаления: ");
                delete_item(num, idx - 1);
                break;
            case 7:
                save_boxes(FILENAME);
                break;
            case 8:
                load_boxes(FILENAME);
                break;
            case 9:
                printf("Очистить все? (1-да / 0-нет): ");
                int confirm;
                scanf("%d", &confirm);
                clear_input_buffer();
                if (confirm == 1) {
                    clear_all_boxes();
                }
                break;
            case 0:
                printf("Выход...\n");
                save_boxes(FILENAME);
                break;
            default:
                printf("Неверный выбор\n");
        }
    } while (choice != 0);

    free_storage();
    return 0;
}
