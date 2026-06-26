#pragma once
#include <stdint.h>
#include "rnd.h"
typedef struct {
    float phase;
    float amplitude;
    float frequency;
    float energy;
    rnd_t *rnd;
} audio_t;
void audio_init(audio_t *audio, rnd_t *rnd);
void audio_update(audio_t *audio, float activity, float dt);
float audio_energy(const audio_t *audio);
void audio_cleanup(audio_t *audio);
