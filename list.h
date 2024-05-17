#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

struct list_element_struct {
    double val;
    int next;
};

typedef struct list_element_struct list_element;

struct list_struct {
    int capacity;
    int length;
    int first;
    int last;
    list_element* elements;
};

typedef struct list_struct* list;

struct list_iter_struct {
    list iterating_list;
    int current_index;
};

typedef struct list_iter_struct list_iter;

void list_grow(list l);
list_iter list_begin(list l);
list_iter list_end(list l);
double list_iter_val(list_iter iter);
list_iter list_iter_next(list_iter iter);
list list_init();
void swap_halves(list l);
int list_length(list l);
void remove_at(list_iter iter);
void insert_before(list_iter iter, double val);
void insert_after(list_iter iter, double val);
void print_list(list l);
void list_destroy(list l);

#endif //LIST_H
