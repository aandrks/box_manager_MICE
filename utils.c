#include <stdio.h>
#include <string.h>
#include "utils.h"

void clear_input_buffer(void) {
    while (getchar() != '\n') {}
}

int get_int_input(const char *prompt) {
    int value;
    char term;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d%c", &value, &term) == 2 && term == '\n') {
            return value;
        } else {
            printf("Ошибка: введите целое число\n");
            clear_input_buffer();
        }
    }
}

float get_float_input(const char *prompt) {
    float value;
    char term;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f%c", &value, &term) == 2 && term == '\n') {
            return value;
        } else {
            printf("Ошибка: введите число (например, 19.99)\n");
            clear_input_buffer();
        }
    }
}

void get_string_input(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    clear_input_buffer();
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}
