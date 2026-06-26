#pragma once
#include <stdint.h>
typedef struct { uint64_t state; } rnd_t;
void rnd_init(rnd_t *rnd, uint64_t seed);
uint32_t rnd_u32(rnd_t *rnd);
float rnd_f(rnd_t *rnd);
float rnd_ranged(rnd_t *rnd, float min, float max);
int rnd_int(rnd_t *rnd, int max);
