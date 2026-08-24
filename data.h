#ifndef DATA_H
#define DATA_H

#define MAX_NAME 100
#define MAX_CAT 50
#define INITIAL_ITEMS 5

typedef struct {
    char name[MAX_NAME];
    char category[MAX_CAT];
    float price;
} Item;

typedef struct {
    int number;
    Item *items;
    int item_count;
    int item_capacity;
} Box;

extern Box *boxes;
extern int box_count;
extern int box_capacity;

void init_storage(int initial_capacity);
void free_storage(void);
void resize_boxes(void);
void resize_items(Box *box);
int add_box(int number);
int find_box(int number);
void add_item(int box_number, const char *name, const char *category, float price);
void display_box(int box_number);
void display_all_boxes(void);
int delete_box(int number);
int delete_item(int box_number, int item_index);
void clear_all_boxes(void);

#endif
