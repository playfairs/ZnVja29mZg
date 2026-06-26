#include "util_math.h"
#include <math.h>
float clampf(float value, float min, float max)
{
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}
float mixf(float a, float b, float t)
{
    return a + (b - a) * t;
}
float smoothstepf(float edge0, float edge1, float x)
{
    float t = clampf((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return t * t * (3.0f - 2.0f * t);
}
float fractf(float value)
{
    return value - floorf(value);
}
float pulse(float value, float width)
{
    float d = fractf(value);
    return clampf(1.0f - fabsf((d - 0.5f) / (width * 0.5f)), 0.0f, 1.0f);
}
