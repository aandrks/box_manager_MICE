#ifndef FILE_IO_H
#define FILE_IO_H

int save_boxes(const char *filename);
int load_boxes(const char *filename);
int append_item_to_file(const char *filename, int number, const char *name, const char *category, float price);

#endif
