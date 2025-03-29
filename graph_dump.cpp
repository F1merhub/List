#include "list.h"

int List_Dump_Dot(List *lst) {
    char buffer[BUFFER_SIZE];
    int buffer_len = 0;

    buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - buffer_len,
                           "digraph G {\n"
                           "\trankdir = LR;\n"
                           "\tbgcolor=\"#E6D5B8\";\n");

    Node *current = lst->head;
    int index = 0;

    // Создание узлов
    while (current != nullptr) {
        buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - buffer_len,
                               "\tnode%03d [shape=Mrecord; style=filled; color=\"#8A9A5B\"; fontcolor=\"#2E382E\"; "
                               "label=\" { ip: %03d } | { value: %3d } | { next: %3d } | { prev: %3d } \"];\n",
                               index, index, current->value,
                               (current->next ? index + 1 : -1),
                               (current->prev ? index - 1 : -1));
        current = current->next;
        index++;
    }

    buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - buffer_len, "\n");

    // Создание прямых связей
    current = lst->head;
    index = 0;
    while (current != nullptr && current->next != nullptr) {
        buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - buffer_len,
                               "\tnode%03d -> node%03d [style=bold; weight=1000; color=\"#E1A95F\"];\n",
                               index, index + 1);
        index++;
        current = current->next;
    }
    int last_index = index;

    // Создание обратных связей
    current = lst->tail;
    index = lst->size - 1;
    while (current != nullptr && current->prev != nullptr) {
        buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - buffer_len,
                               "\tnode%03d -> node%03d [weight=0; color=\"#A67B5B\"; constraint=false];\n",
                               index, index - 1);
        index--;
        current = current->prev;
    }

    buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - buffer_len, "\n");

    // Создание элементов Head и Tail
    buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - buffer_len,
                           "\thead [shape=Mrecord; style=filled; color=\"#4A7023\"; fontcolor=\"white\"; label=\"Head\"];\n");

    if (lst->head != nullptr) {
        buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - buffer_len,
                               "\thead -> node000 [style=dashed; color=\"#4A7023\"];\n");
    }

    buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - buffer_len,
                           "\ttail [shape=hexagon; style=filled; color=\"#4A7023\"; fontcolor=\"white\"; label=\"Tail\"];\n");

    if (lst->tail != nullptr) {
        buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - buffer_len,
                               "\ttail -> node%03d [style=dashed; color=\"#4A7023\"; constraint=false];\n", last_index);
    }

    buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - buffer_len, "}\n");

    FILE *file = fopen("GraphDump/dump.dot", "w+");
    if (!file) {
        fprintf(stderr, "dump.dot don't open\n");
        return -1;
    }

    fprintf(file, "%s", buffer);
    fclose(file);

    return 0;
}
