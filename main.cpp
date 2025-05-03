#include "list.h"

int main() {
    error_code err = OK;
    List *lst = List_Constructor(&err);
    List_Add(lst, 1, 0);
    List_Add(lst, 2, 1);
    List_Add(lst, 3, 2);
    List_Add(lst, 4, 3);
    List_Add(lst, 5, 4);
    List_Add(lst, 6, 5);
    // List_Remove_Pointer(lst, lst->head->next);
    List_Remove_Index(lst, 2);
    List_Print(lst);
    List_Dump_Dot(lst);
    List_Destructor(&lst);
    return 0;
}
