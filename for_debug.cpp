 #include <stdio.h>
 #include <stdlib.h>
 #include <assert.h>

typedef struct List
 {
     int *head = nullptr;
     int *tail = nullptr;
     int size = 2;
     int error_code;
 } List;


int main() {
    List *lst = (List*)calloc(1, sizeof(List));
    lst->size = 2;
    printf("%d", lst->size);
    return 0;
}
