#include <math.h>
#include <stdbool.h>

typedef struct
{
    float x, y;
} Vector2;

bool Vector2_match(Vector2 a, Vector2 b);
Vector2 Vector2_subtract(Vector2 vector, Vector2 by);
float Vector2_get_magnitude(Vector2 vector);
float Vector2_get_distance(Vector2 from, Vector2 to);
