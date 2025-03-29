#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int list_element;
const size_t BUFFER_SIZE = 4048;
#define ELEMENT_SPECIFICATOR "%d";

typedef struct Node
{
    Node *next = NULL;
    Node *prev = NULL;
    list_element value = 0;
} Node;

typedef struct List
{
    Node *head = NULL;
    Node *tail = NULL;
    int size = 0;
} List;

enum error_code
{
    OK = 0,
    NULL_LST = 1,
    MEMORY_ALLOCATION_ERROR = 2,
    INVALID_ADRESS = 3
};

error_code List_Remove_Pointer(List *lst, Node *remove_node);
Node* List_Find(List *lst, list_element value);
Node* List_Get_First(List* lst);
Node* List_Get_Last(List* lst);
Node* List_Get_Next(Node* current);
Node* List_Get_Prev(Node* current);
error_code List_Add_First(List *lst, list_element value);
error_code List_Add_Last(List *lst, list_element value);
error_code List_Add(List *lst, list_element value, int adress);
void List_Destructor(List **lst);
List *List_Constructor();
error_code List_Print(List *lst);
int List_Dump_Dot(List *lst);
error_code List_Remove_Adress(List *lst, int adress);
error_code List_Remove_Index(List *lst, int adress);

#endif
