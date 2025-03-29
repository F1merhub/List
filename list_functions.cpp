#include "list.h"

List *List_Constructor() {
    List *lst = (List *)calloc(1, sizeof(List));

    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;

    return lst;
}

void List_Destructor(List **lst) {
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
}

error_code List_Add(List *lst, list_element value, int adress) {

    if (! lst)
        return NULL_LST;

    if (adress > lst->size)
        return INVALID_ADRESS;

    if (! adress)
        return List_Add_First(lst, value);

    if (adress == lst->size)
        return List_Add_Last(lst, value);

    Node *new_node = (Node *)calloc(1, sizeof(Node));
    if (new_node == NULL)
        return MEMORY_ALLOCATION_ERROR;

    new_node->value = value;

    Node *current = lst->head;
    for (int i = 0; i < adress - 1; i++)
        current = current->next;

    new_node->next = current->next;
    new_node->prev = current;
    current->next->prev = new_node;
    current->next = new_node;

    lst->size++;
    return OK;
}

error_code List_Add_First(List *lst, list_element value) {

    if (! lst)
        return NULL_LST;

    Node *new_node = (Node *)calloc(1, sizeof(Node));
    if (! new_node)
        return MEMORY_ALLOCATION_ERROR;

    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (! lst->head) {
        new_node->next = NULL;
        lst->head = new_node;
        lst->tail = new_node;
    }
    else
    {
        new_node->next = lst->head;
        lst->head->prev = new_node;
        lst->head = new_node;
    }

    lst->size++;
    return OK;
}

error_code List_Add_Last(List *lst, list_element value) {
    if (! lst)
        return NULL_LST;

    Node *new_node = (Node*)calloc(1, sizeof(Node));
    if (! new_node)
        return MEMORY_ALLOCATION_ERROR;

    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (! lst->tail)
    {
        new_node->prev = NULL;
        lst->tail = new_node;
        lst->head = new_node;
    }
    else
    {
        new_node->prev = lst->tail;
        lst->tail->next = new_node;
        lst->tail = new_node;
    }

    lst->size++;
    return OK;
}

error_code List_Remove_Pointer(List *lst, Node *remove_node) {
    if (! lst || (!remove_node))
        return NULL_LST;

    if (remove_node->prev)
        remove_node->prev->next = remove_node->next;
    else if (remove_node == lst->head)
        lst->head = remove_node->next;

    if (remove_node->next)
        remove_node->next->prev = remove_node->prev;
    else if (remove_node == lst->tail)
        lst->tail = remove_node->prev;

    free(remove_node);
    lst->size--;
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


Node* List_Find(List *lst, list_element value) {  // первое вхождение
    if (! lst)
        return NULL;

    Node *current = lst->head;
    while (current)
    {
        if (current->value == value)
            return current;
        current = current->next;
    }

    return NULL;
}

error_code List_Remove_Index(List *lst, int adress) {
    if (! lst)
        return NULL_LST;

    if (adress > lst->size)
        return INVALID_ADRESS;

    Node *current = lst->head;
    for(int i = 0; i < adress; i++) {
        current = current->next; // лежит адрес нужного
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    lst->size--;
    free(current);

    return OK;
}
