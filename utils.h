#ifndef UTILS_H
#define UTILS_H

void clear_input_buffer(void);
int get_int_input(const char *prompt);
float get_float_input(const char *prompt);
void get_string_input(const char *prompt, char *buffer, int size);

#endif
