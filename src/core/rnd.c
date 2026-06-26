#include "rnd.h"
#include <stdint.h>
void rnd_init(rnd_t *rnd, uint64_t seed)
{
    rnd->state = seed ? seed : 0xA3B195354A39B70Dull;
}
uint32_t rnd_u32(rnd_t *rnd)
{
    uint64_t x = rnd->state;
    x ^= x >> 12;
    x ^= x << 25;
    x ^= x >> 27;
    rnd->state = x * 0x2545F4914F6CDD1Dull;
    return (uint32_t)(x >> 32);
}
float rnd_f(rnd_t *rnd)
{
    return rnd_u32(rnd) * (1.0f / 4294967295.0f);
}
float rnd_ranged(rnd_t *rnd, float min, float max)
{
    return min + (max - min) * rnd_f(rnd);
}
int rnd_int(rnd_t *rnd, int max)
{
    return (int)(rnd_f(rnd) * (float)max);
}
