#include "linked_list.h"

size_t LinkedList_data_size;

bool LinkedList_data_matches(void *data, void *other_data)
{
    if(!LinkedList_data_size){
        printf("FAIL. set LinkedList_data_size to size of your data");
        return false;
    }
    return memcmp(data, other_data, LinkedList_data_size) == 0;
}
int LinkedList_length(LinkedList_node_t **head)
{
    if (!head || !*head)
        return 0;

    LinkedList_node_t *tmp = *head;
    int i = 0;
    for (; tmp; i++)
        tmp = tmp->next;

    return i;
}
LinkedList_node_t *LinkedList_malloc_node(void *data)
{
    LinkedList_node_t *tmp = malloc(sizeof(LinkedList_node_t));
    if (tmp == NULL)
        return NULL;
    tmp->data = data;
    tmp->next = NULL;
    return tmp;
}

LinkedList_node_t *LinkedList_prepend(LinkedList_node_t **head, void *data)
{
    if (!head)
        return NULL;

    LinkedList_node_t *tmp = LinkedList_malloc_node(data);
    if (!tmp)
        return NULL;
    tmp->next = *head;
    *head = tmp;
    return *head;
}
LinkedList_node_t *LinkedList_append(LinkedList_node_t **head, void *data)
{
    if (!head)
        return NULL;

    if (*head == NULL)
        return LinkedList_prepend(head, data);

    LinkedList_node_t *tmp = *head;
    while (tmp->next)
        tmp = tmp->next;

    LinkedList_node_t *new_node = LinkedList_malloc_node(data);
    tmp->next = new_node;
    return new_node;
}
LinkedList_node_t *LinkedList_insert_after(LinkedList_node_t **head, void *data, void *after_data)
{
    if (!head || !*head)
        return NULL;

    LinkedList_node_t *tmp = *head;
    while (tmp)
    {
        if (LinkedList_data_matches(tmp->data, after_data))
        {
            LinkedList_node_t *new_node = LinkedList_malloc_node(data);
            if (!new_node)
                return NULL;
            new_node->next = tmp->next;
            tmp->next = new_node;
            return new_node;
        }
        tmp = tmp->next;
    }

    return NULL;
}
LinkedList_node_t *LinkedList_insert_before(LinkedList_node_t **head, void *data, void *before_data)
{
    if (!head || !*head)
        return NULL;

    if (LinkedList_data_matches((*head)->data, before_data))
        return LinkedList_prepend(head, data);

    LinkedList_node_t *tmp = *head;
    while (tmp->next)
    {
        if (LinkedList_data_matches(tmp->next->data, before_data))
        {
            LinkedList_node_t *new_node = LinkedList_malloc_node(data);
            if (!new_node)
                return NULL;
            new_node->next = tmp->next;
            tmp->next = new_node;
            return new_node;
        }
        tmp = tmp->next;
    }

    return NULL;
}
LinkedList_node_t *LinkedList_insert(LinkedList_node_t **head, void *data, int index)
{
    if (!head || !*head)
        return NULL;

    int length = LinkedList_length(head);
    if (index < 0)
        index += length - 1;

    if (index < 0 || index >= length)
        return NULL;

    if (index == 0)
        return LinkedList_prepend(head, data);

    LinkedList_node_t *tmp = *head;
    for (int i = 0; i < index - 1 && tmp; i++)
        tmp = tmp->next;

    if (tmp == NULL)
        return NULL;

    LinkedList_node_t *new_node = LinkedList_malloc_node(data);
    if (new_node == NULL)
        return NULL;

    new_node->next = tmp->next;
    tmp->next = new_node;
    return tmp->next;
}

LinkedList_node_t *LinkedList_get_by_index(LinkedList_node_t **head, int index)
{
    if (!head || !*head)
        return NULL;

    int length = LinkedList_length(head);
    if (index < 0)
        index += length - 1;

    if (index < 0 || index >= length)
        return NULL;

    LinkedList_node_t *tmp = *head;
    for (int i = 0; i < index && tmp; i++)
        tmp = tmp->next;

    return tmp;
}
int LinkedList_get_index(LinkedList_node_t **head, void *data)
{
    if (!head || !*head)
        return -1;

    LinkedList_node_t *tmp = *head;
    for (int i = 0; tmp; i++)
    {
        if (LinkedList_data_matches(tmp->data, data))
            return i;
        tmp = tmp->next;
    }

    return -1;
}
LinkedList_node_t *LinkedList_get_after(LinkedList_node_t **head, void *data)
{
    if (!head || !*head)
        return NULL;

    LinkedList_node_t *tmp = *head;
    while (tmp)
    {
        if (LinkedList_data_matches(tmp->data, data))
            return tmp->next;
        tmp = tmp->next;
    }

    return NULL;
}
LinkedList_node_t *LinkedList_get_before(LinkedList_node_t **head, void *data)
{
    if (!head || !*head)
        return NULL;

    LinkedList_node_t *tmp = *head;
    while (tmp->next)
    {
        if (LinkedList_data_matches(tmp->next->data, data))
            return tmp;
        tmp = tmp->next;
    }

    return NULL;
}
LinkedList_node_t *LinkedList_get_tail(LinkedList_node_t **head)
{
    if (!head || !*head)
        return NULL;

    LinkedList_node_t *tmp = *head;
    while (tmp->next)
        tmp = tmp->next;

    return tmp;
}

void *LinkedList_pop_head(LinkedList_node_t **head)
{
    if (!head || !*head)
        return NULL;

    LinkedList_node_t *tmp = *head;
    *head = (*head)->next;
    void *retrieve = tmp->data;
    free(tmp);
    return retrieve;
}
void *LinkedList_pop_tail(LinkedList_node_t **head)
{
    if (!head || !*head)
        return NULL;

    LinkedList_node_t *prev = NULL;
    LinkedList_node_t *tmp = *head;

    while (tmp->next)
    {
        prev = tmp;
        tmp = tmp->next;
    }

    void *retrieve = tmp->data;
    if (prev)
        prev->next = NULL;
    else
        *head = NULL;

    free(tmp);
    return retrieve;
}
void *LinkedList_pop_after(LinkedList_node_t **head, void *data)
{
    if (!head || !*head)
        return NULL;

    LinkedList_node_t *tmp = *head;
    while (tmp)
    {
        if (LinkedList_data_matches(tmp->data, data))
        {
            if (tmp->next)
            {
                void *retrieve = tmp->next->data;
                LinkedList_node_t *delete = tmp->next;
                tmp->next = tmp->next->next;
                free(delete);
                return retrieve;
            }
            return NULL;
        }
        tmp = tmp->next;
    }

    return NULL;
}
void *LinkedList_pop_before(LinkedList_node_t **head, void *data)
{
    if (!head || !*head || !(*head)->next)
        return NULL;

    if (LinkedList_data_matches((*head)->next->data, data))
    {
        void *retrieve = (*head)->data;
        LinkedList_node_t *delete = *head;
        *head = (*head)->next;
        free(delete);
        return retrieve;
    }

    LinkedList_node_t *tmp = *head;
    while (tmp->next)
    {
        if (LinkedList_data_matches(tmp->next->next->data, data))
        {

            void *retrieve = tmp->next->data;
            LinkedList_node_t *delete = tmp->next;
            tmp->next = tmp->next->next;
            free(delete);
            return retrieve;
        }
        tmp = tmp->next;
    }

    return NULL;
}
void *LinkedList_pop_index(LinkedList_node_t **head, int index)
{
    if (!head || !*head)
        return NULL;

    int length = LinkedList_length(head);
    if (index < 0)
        index += length - 1;

    if (index < 0 || index >= length)
        return NULL;

    if (index == 0)
        return LinkedList_pop_head(head);

    LinkedList_node_t *tmp = *head;
    for (int i = 0; i < index - 1 && tmp->next; i++)
        tmp = tmp->next;

    if (!tmp->next)
        return NULL;

    LinkedList_node_t *delete = tmp->next;
    void *retrieve = delete->data;
    tmp->next = delete->next;
    free(delete);

    return retrieve;
}
void *LinkedList_pop_data(LinkedList_node_t **head, void *data)
{
    if (!head || !*head)
        return NULL;

    LinkedList_node_t *tmp = *head;
    LinkedList_node_t *prev = NULL;
    while (tmp)
    {
        if (LinkedList_data_matches(tmp->data, data))
        {
            if (prev)
                prev->next = tmp->next;
            else
                *head = tmp->next;
            void *retrieve = tmp->data;
            free(tmp);
            return retrieve;
        }
        prev = tmp;
        tmp = tmp->next;
    }

    return NULL;
}


LinkedList_node_t *LinkedList_delete_list(LinkedList_node_t **head)
{
    if (!head || !*head)
        return NULL;

    LinkedList_node_t *tmp;
    while (*head)
    {
        tmp = *head;
        *head = (*head)->next;
        free(tmp->data);
        free(tmp);
    }
    return NULL;
}
void LinkedList_delete_head(LinkedList_node_t **head)
{
    if (!head || !*head)
        return;

    LinkedList_node_t *delete = *head;
    *head = (*head)->next;
    free(delete->data);
    free(delete);
}
void LinkedList_delete_by_data(LinkedList_node_t **head, void *data)
{
    if (!head || !*head)
        return;

    LinkedList_node_t *tmp = *head;
    LinkedList_node_t *prev = NULL;
    while (tmp)
    {
        if (LinkedList_data_matches(tmp->data, data))
        {
            if (prev)
                prev->next = tmp->next;
            else
                *head = tmp->next;
            free(tmp->data);
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}
void LinkedList_delete_after(LinkedList_node_t **head, void *data)
{
    if (!head || !*head)
        return;

    LinkedList_node_t *tmp = *head;
    while (tmp)
    {
        if (LinkedList_data_matches(tmp->data, data) && tmp->next)
        {
            LinkedList_node_t *delete = tmp->next;
            tmp->next = delete->next;
            free(delete->data);
            free(delete);
            return;
        }
        tmp = tmp->next;
    }
}
void LinkedList_delete_before(LinkedList_node_t **head, void *data)
{
    if (!head || !*head || !(*head)->next)
        return;

    if (LinkedList_data_matches((*head)->next->data, data))
        return LinkedList_delete_head(head);

    LinkedList_node_t *tmp = *head;
    while (tmp->next && tmp->next->next)
    {
        if (LinkedList_data_matches(tmp->next->next->data, data))
        {
            LinkedList_node_t *delete = tmp->next;
            tmp->next = tmp->next->next;
            free(delete->data);
            free(delete);
            return;
        }
        tmp = tmp->next;
    }
}
void LinkedList_delete_index(LinkedList_node_t **head, int index)
{
    if (!head || !*head)
        return;

    int length = LinkedList_length(head);
    if (index < 0)
        index += length - 1;

    if (index < 0 || index >= length)
        return;

    if (index == 0)
        return LinkedList_delete_head(head);

    LinkedList_node_t *tmp = *head;
    for (int i = 0; i < index - 1 && tmp->next; i++)
        tmp = tmp->next;

    if (!tmp->next)
        return;

    LinkedList_node_t *delete = tmp->next;
    tmp->next = delete->next;
    free(delete->data);
    free(delete);
}
