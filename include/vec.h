#pragma once
typedef struct { float x; float y; } vec2;
vec2 vec2f(float x, float y);
vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_mul(vec2 v, float s);
float vec2_dot(vec2 a, vec2 b);
float vec2_len(vec2 v);
