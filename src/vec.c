#include "vec.h"
#include <math.h>
vec2 vec2f(float x, float y)
{
    return (vec2){x, y};
}
vec2 vec2_add(vec2 a, vec2 b)
{
    return (vec2){a.x + b.x, a.y + b.y};
}
vec2 vec2_sub(vec2 a, vec2 b)
{
    return (vec2){a.x - b.x, a.y - b.y};
}
vec2 vec2_mul(vec2 v, float s)
{
    return (vec2){v.x * s, v.y * s};
}
float vec2_dot(vec2 a, vec2 b)
{
    return a.x * b.x + a.y * b.y;
}
float vec2_len(vec2 v)
{
    return sqrtf(vec2_dot(v, v));
}
