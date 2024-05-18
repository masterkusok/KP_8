#include "list.h"

int main(void) {
    list l = list_init();
    insert_after(list_begin(l), 1);
    insert_after(list_begin(l), 2);
    insert_after(list_end(l), 3);
    insert_before(list_end(l), 4);
    insert_before(list_end(l), 5);
    insert_before(list_end(l), 6);
    print_list(l);
    swap_halves(l);
    print_list(l);
    remove_at(list_begin(l));
    remove_at(list_begin(l));
    remove_at(list_begin(l));
    print_list(l);

    list_destroy(l);
    return 0;
}
