#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LinkedList_node
{
    void *data;
    struct LinkedList_node *next;
} LinkedList_node_t;


extern size_t LinkedList_data_size;


// return TRUE if match
bool LinkedList_data_matches(void *data, void *other_data);
int LinkedList_length(LinkedList_node_t **head);
LinkedList_node_t *LinkedList_malloc_node(void *data);

LinkedList_node_t *LinkedList_prepend(LinkedList_node_t **head, void *data);
LinkedList_node_t *LinkedList_append(LinkedList_node_t **head, void *data);
LinkedList_node_t *LinkedList_insert_after(LinkedList_node_t **head, void *data, void *after_data);
LinkedList_node_t *LinkedList_insert_before(LinkedList_node_t **head, void *data, void *before_data);
LinkedList_node_t *LinkedList_insert(LinkedList_node_t **head, void *data, int index);

LinkedList_node_t *LinkedList_get_by_index(LinkedList_node_t **head, int index);
// return -1 if not found
int LinkedList_get_index(LinkedList_node_t **head, void *data);
LinkedList_node_t *LinkedList_get_after(LinkedList_node_t **head, void *data);
LinkedList_node_t *LinkedList_get_before(LinkedList_node_t **head, void *data);
LinkedList_node_t *LinkedList_get_tail(LinkedList_node_t **head);

void *LinkedList_pop_head(LinkedList_node_t **head);
void *LinkedList_pop_tail(LinkedList_node_t **head);
void *LinkedList_pop_after(LinkedList_node_t **head, void *data);
void *LinkedList_pop_before(LinkedList_node_t **head, void *data);
void *LinkedList_pop_index(LinkedList_node_t **head, int index);
void *LinkedList_pop_data(LinkedList_node_t **head, void*data);

LinkedList_node_t *LinkedList_delete_list(LinkedList_node_t **head);
void LinkedList_delete_head(LinkedList_node_t **head);
void LinkedList_delete_by_data(LinkedList_node_t **head, void *data);
void LinkedList_delete_after(LinkedList_node_t **head, void *data);
void LinkedList_delete_before(LinkedList_node_t **head, void *data);
void LinkedList_delete_index(LinkedList_node_t **head, int index);
