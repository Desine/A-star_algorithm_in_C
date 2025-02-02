#include "../data_structures/linked_list/linked_list.h"
#include "../data_structures/vector/vector2/vector2.h"
#include "stdbool.h"
#include <unistd.h>
#include <time.h>

#define ROWS 39
#define COLS 60
#define THRESHOLD .8

/*
задача найти путь

Node {
    Vector2 pos
    g               // cost to get there = parrent.g + 1
    h               // distance to goal
    f = g + h
    Node parent
}


список open - ячейки доступные для смотрения от них
список closed - уже просмотренные, перемешённые из open

Node goal

while open не пуст
    Node current = open.pop(with_least_f_costc)
    closed.add(current)

    if current == goal
        success

    float new_g = current.g + 1

    foreach neighbor нода для current
        if neighbor.is_valid() == false || closed.contains(neighbor)
            continue

        if нода в open
            if new_g < neighbor.g:
                neighbor.g = new_g
                neighbor.f = new_g + neighbor.h
                neighbor.parent = current
        else
            neighbor.g = new_g
            neighbor.h = эвристика(neighbor, goal)
            neighbor.f = neighbor.g + neighbor.h
            neighbor.parent = current
            open.add(neighbor)



if goal.parent != null
    success
else
    fail


*/

typedef struct Node
{
    Vector2 position;
    int g;
    float h, f;
    struct Node *parent;
} Node_t;

int m_matrix[ROWS][COLS];

Node_t *pop_with_least_f(LinkedList_node_t **head)
{
    if (!head || !*head)
        return NULL;

    LinkedList_node_t *tmp = *head;
    Node_t *retrieve = tmp->data;
    while (tmp != NULL)
    {
        if (((Node_t *)tmp->data)->f < retrieve->f)
            retrieve = tmp->data;
        tmp = tmp->next;
    }

    return LinkedList_pop_data(head, retrieve);
}
bool list_contains_by_position(LinkedList_node_t *head, Vector2 position)
{
    if (!head)
        return false;

    LinkedList_node_t *tmp = head;
    while (tmp != NULL)
    {
        if (Vector2_match(((Node_t *)tmp->data)->position, position))
            return true;
        tmp = tmp->next;
    }

    return false;
}
Node_t *list_get_by_position(LinkedList_node_t *head, Vector2 position)
{
    if (!head)
        return NULL;

    LinkedList_node_t *tmp = head;
    while (tmp != NULL)
    {
        if (Vector2_match(((Node_t *)tmp->data)->position, position))
            return tmp->data;
        tmp = tmp->next;
    }

    return NULL;
}

void create()
{
    srand(time(0));
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (rand() / (float)RAND_MAX > THRESHOLD)
            {
                m_matrix[r][c] = -1;
            }
            else
            {
                m_matrix[r][c] = 0;
            }
        }
    }

    // angle
    for (int r = COLS / 4; r < COLS - COLS / 4; r++)
    {
        m_matrix[ROWS / 2 + ROWS / 4][r] = -1;
        printf("\n");
    }
    for (int r = ROWS / 4; r < ROWS - ROWS / 4; r++)
    {
        m_matrix[r][COLS / 2 + COLS / 4] = -1;
        printf("\n");
    }
}
bool is_possition_allowed(Vector2 position)
{
    if (position.x < 0 || position.y < 0)
        return false;
    if (position.x >= COLS || position.y >= ROWS)
        return false;

    if (m_matrix[(int)position.y][(int)position.x] == 0)
        return true;

    return false;
}
void draw()
{
    for (int c = 0; c < COLS; c++)
    {
        printf("##");
    }
    printf("\n");

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (m_matrix[r][c] == 0)
                printf("  ");
            else if (m_matrix[r][c] == -1)
                printf("[]");
            else if (m_matrix[r][c] == 3)
                printf("$$");
            else if (m_matrix[r][c] == 4)
                printf("'.");
            else
                printf("%d", m_matrix[r][c]);
        }
        printf("\n");
    }

    for (int c = 0; c < COLS; c++)
    {
        printf("##");
    }
    printf("\n");
}
int main()
{
    create();

    LinkedList_data_size = sizeof(Node_t);

    Node_t *start = malloc(sizeof(Node_t));
    Vector2 start_position = {3, 3};
    start->position = start_position;
    start->g = 0;
    start->h = 0;
    start->f = 0;
    start->parent = NULL;

    Node_t *goal = malloc(sizeof(Node_t));
    Vector2 goal_position = {COLS - 3, ROWS - 3};
    goal->position = goal_position;
    goal->g = 0;
    goal->h = 0;
    goal->f = 0;
    goal->parent = NULL;

    LinkedList_node_t *open = NULL;
    LinkedList_node_t *closed = NULL;

    LinkedList_prepend(&open, start);

    Vector2 directions[4];
    directions[0].x = 1;
    directions[0].y = 0;

    directions[1].x = -1;
    directions[1].y = 0;

    directions[2].x = 0;
    directions[2].y = 1;

    directions[3].x = 0;
    directions[3].y = -1;

    while (open)
    {
        printf("\nall f costs:");
        LinkedList_node_t *tmp = open;
        while (tmp != NULL)
        {
            printf("\nf: %f", ((Node_t *)tmp->data)->f);
            tmp = tmp->next;
        }

        Node_t *current = pop_with_least_f(&open);
        LinkedList_prepend(&closed, current);

        printf("\ncurrent f cost: %f", current->f);
        printf("\ncurrent position: [%2.0f,%2.0f]", current->position.y, current->position.x);

        if (Vector2_match(current->position, goal->position))
        {
            printf("\n\nfound the goal!!!");
            goal = current;
            break;
        }

        int new_g = current->g + 1;

        for (int i = 0; i < 4; i++)
        {
            Vector2 neighbor_position = {
                current->position.x + directions[i].x,
                current->position.y + directions[i].y};

            printf("\nneighbor, position: [%2.0f,%2.0f]", current->position.y, current->position.x);

            if (!is_possition_allowed(neighbor_position))
            {
                printf(": not allowed");
                continue;
            }
            if (list_contains_by_position(closed, neighbor_position))
            {
                m_matrix[(int)neighbor_position.y][(int)neighbor_position.x] = 4;
                printf(": in closed");
                continue;
            }

            Node_t *from_open_by_positions = list_get_by_position(open, neighbor_position);
            if (from_open_by_positions)
            {
                printf(": in open");
                if (new_g < from_open_by_positions->g)
                {
                    from_open_by_positions->position = neighbor_position;
                    from_open_by_positions->g = new_g;
                    from_open_by_positions->f = new_g + from_open_by_positions->h;
                    from_open_by_positions->parent = current;
                }
            }
            else
            {
                printf(": new");
                Node_t *new_node = malloc(sizeof(Node_t));
                new_node->position = neighbor_position;
                new_node->g = new_g;
                new_node->h = Vector2_get_distance(new_node->position, goal->position);
                new_node->f = new_node->g + new_node->h;
                new_node->parent = current;
                LinkedList_prepend(&open, new_node);
            }
        }

        printf("\nopen length: %d", LinkedList_length(&open));
        printf("\nclosed length: %d", LinkedList_length(&closed));
        printf("\n");
        // sleep(1);
    }

    Node_t *tmp = goal;
    while (tmp != NULL)
    {
        m_matrix[(int)tmp->position.y][(int)tmp->position.x] = 3;
        tmp = tmp->parent;
    }

    printf("\n");

    if (!goal->parent)
        printf("\nNO goal found :(\n");
    printf("\n");
    draw();

    printf("\n");
}
