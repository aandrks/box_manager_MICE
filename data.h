#ifndef DATA_H
#define DATA_H

#define MAX_NAME 100
#define MAX_CAT 50

typedef struct {
    int number;
    char name[MAX_NAME];
    char category[MAX_CAT];
    float price;
} Box;

extern Box *boxes;
extern int box_count;
extern int box_capacity;

void init_storage(int initial_capacity);
void free_storage(void);
void resize_storage(void);
void add_box(int number, const char *name, const char *category, float price);
void display_all_boxes(void);
int find_box_by_number(int number);
int find_box_by_name(const char *name);
int delete_box_by_number(int number);
void clear_all_boxes(void);

#endif
