#include "list.h"

const int INIT_CAPACITY = 2;
const float GROW_FACTOR = 3.0/2.0;


void list_grow(list l) {
    int new_capacity = l->capacity * GROW_FACTOR;
    if (!l->capacity) {
        new_capacity = INIT_CAPACITY;
    }
    size_t new_size = new_capacity * sizeof(list_element);
    if (l->elements) {
        l->elements = realloc(l->elements, new_size);
    } else {
        l->elements = malloc(new_size);
    }

    for(int i = 0; i < l->capacity; i++) {
        l->elements[i].next = i + 1;
    }
    l->capacity = new_capacity;
}

list list_init() {
    list l = malloc(sizeof(list));
    l->capacity = INIT_CAPACITY;
    l->length = 0;
    l->elements = NULL;
    list_grow(l);
    // барьерный элемент
    l->elements[0] = (list_element){-1, 0};
    l->first = 0;
    l->last = 0;
    l->length++;
    return l;
}

list_iter list_begin(list l) {
    return (list_iter){l, l->first};
}

list_iter list_end(list l) {
    return (list_iter){l, l->last};
}

double list_iter_val(list_iter iter) {
    return iter.iterating_list->elements[iter.current_index].val;
}

list_iter list_iter_next(list_iter iter) {
    return (list_iter){iter.iterating_list, iter.iterating_list->elements[iter.current_index].next};
}

bool iter_end(list_iter iter) {
    return iter.current_index == iter.iterating_list->length-1;
}

void insert_at(list l, int index, double val) {
    if(l->length + 1 >= l->capacity) {
        list_grow(l);
    }

    for (int i = l->length-2; i >= index; i--) {
        l->elements[i+1] = l->elements[i];
        l->elements[i+1].next = i+2;
    }
    list_element new = {val, index + 1};
    l->elements[index] = new;
    l->last++;
    l->length++;
}

void insert_before(list_iter iter, double val) {
    list l = iter.iterating_list;
    int index = iter.current_index;
    insert_at(l, index, val);
}

void insert_after(list_iter iter, double val) {
    list l = iter.iterating_list;
    int index = iter.current_index + 1;
    if (l->length == 1) {
        index = 0;
    }
    if (index == l->length) {
        index--;
    }
    insert_at(l, index, val);
}

void remove_at(list_iter iter) {
    list l = iter.iterating_list;

    if (iter.current_index > l->length - 1 || iter.current_index < 0) {
        return;
    }

    if (iter.current_index == l->length-2) {
        l->elements[l->length-2] = l->elements[l->length-1];
    } else {
        for(int i = iter.current_index; i < l->length-1; i++) {
            l->elements[i] = l->elements[i+1];
            l->elements[i].next--;
        }
    }

    l->length--;
    l->last = l->length-1;
}

void swap_halves(list l) {
    int half_index = ((l->length-1) / 2)-1;
    int half_distance = half_index+1;
    if (l->length % 2 == 0){
        half_index++;
    }

    for (int i = 0; i <= half_index; i++) {
        double buff_val = l->elements[i].val;
        l->elements[i].val = l->elements[i+half_distance].val;
        l->elements[i+half_distance].val = buff_val;
    }
}

void print_list(list l) {
    for(list_iter first = list_begin(l); !iter_end(first); first = list_iter_next(first)) {
        printf("%lf ", list_iter_val(first));
    }
    printf("\n");
}

int list_length(list l) {
    return l->length-1;
}

void list_destroy(list l) {
    free(l->elements);
    free(l);
}
