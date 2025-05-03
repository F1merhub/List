#include "list.h"

List *List_Constructor(error_code *err) {
    List *lst = (List *)calloc(1, sizeof(List));
    if (lst == NULL) {
        *err = NULL_LST;
        return NULL;
    }

    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;

    return lst;
}

error_code List_Destructor(List **lst) {
    LIST_NULL_CHECK(lst);
    if (lst && *lst) {
        Node *current = (*lst)->head;
        while (current) {
            Node *next_node = current->next;
            free(current);
            current = next_node;
        }
        free(*lst);
        *lst = NULL;
    }
    return OK;
}

error_code List_Verify(List *lst, int adress) {
    LIST_NULL_CHECK(lst);
    if (adress < 0 || adress > lst->size)
        return INVALID_ADRESS;
    return OK;
}

error_code List_Add(List *lst, list_element value, int adress) {

    error_code status = List_Verify(lst, adress);
    if (status != OK)
        return status;

    Node *new_node = (Node *)calloc(1, sizeof(Node));
    LIST_NULL_CHECK(lst);

    new_node->value = value;

        if (lst->head == NULL) { // пустой список
                lst->head = new_node;
                lst->tail = new_node;
            }

        else if (adress == 0) { // начало
                new_node->next = lst->head;
                lst->head->prev = new_node;
                lst->head = new_node;
        }

        else if (adress == lst->size) { // конец
                lst->tail->next = new_node;
                new_node->prev = lst->tail;
                lst->tail = new_node;
        }

        else {   // добавление внутрь
            Node *current = lst->head;
            for (int i = 0; i < adress - 1; i++)
                current = current->next;

            new_node->next = current->next;
            new_node->prev = current;
            current->next->prev = new_node;
            current->next = new_node;
        }

    lst->size++;
    return OK;
}

error_code List_Remove_Pointer(List *lst, Node *ptr) {
    if (lst == NULL || ptr == NULL) {
        return INVALID_POINTER;
    }

    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;

    free(ptr);

    return OK;
}

error_code List_Print(List *lst) {
   if (! lst)
       return NULL_LST;

    Node* current_node = lst->head;
    printf("\t---------------------------------------------------------------------------------------\n");
    while (current_node)
    {
        printf("\t[%p]: value = %d, next = [%p], previous = [%p]\n",
                current_node, current_node->value, current_node->next, current_node->prev);

        current_node = current_node->next;
    }
    printf("\t---------------------------------------------------------------------------------------\n");

    return OK;
}

Node* List_Get_First(List* lst) {
    if (lst) return lst->head;
    else     return NULL;
}

Node* List_Get_Last(List* lst) {
    if (lst) return lst->tail;
    else     return NULL;
}

Node* List_Get_Next(Node* current) {
    if (current) return current->next;
    else     return NULL;
}

Node* List_Get_Prev(Node* current) {
    if (current) return current->prev;
    else     return NULL;
}


Node* List_Find(List *lst, list_element value, error_code* err) {  // первое вхождение
    if (lst == NULL) {
        *err = NULL_LST;
        return NULL;
    }
    Node *current = lst->head;
    while (current)
    {
        if (current->value == value)
            return current;
        current = current->next;
    }

    return NULL;
}

error_code List_Remove_Index(List *lst, int adress) { // FIXME call List_Remove_Pointer
    List_Verify(lst, adress);

    Node *current = lst->head;
    for(int i = 0; i < adress; i++) {
        current = current->next; 
    }
    List_Remove_Pointer(lst, current);

    return OK;
}

