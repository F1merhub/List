#include "list.h"

int main() {
    List *lst = List_Constructor();

    List_Add(lst, 1, 0);
    List_Add(lst, 2, 1);
    List_Add(lst, 3, 2);
    ListDumpDot(lst);
    List_Print(lst);
    List_Destructor(&lst);
    return 0;
}
