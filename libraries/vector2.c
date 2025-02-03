#include "vector2.h"

bool Vector2_match(Vector2 a, Vector2 b){
    return a.x == b.x && a.y == b.y;
}

Vector2 Vector2_subtract(Vector2 vector, Vector2 by)
{
    Vector2 retrieve = {vector.x - by.x, vector.y - by.y};
    return retrieve;
}

float Vector2_get_magnitude(Vector2 vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float Vector2_get_distance(Vector2 from, Vector2 to)
{
    Vector2 from_zero = Vector2_subtract(to, from);
    return Vector2_get_magnitude(from_zero);
}
