#pragma once
#include <stdint.h>
#include <SDL3/SDL.h>
#include "rnd.h"
typedef struct {
    float phase;
    float amplitude;
    float frequency;
    float energy;
    float distortion;
    float feedback;
    float sample_rate;
    SDL_AudioStream *stream;
    rnd_t rnd;
} audio_t;
void audio_init(audio_t *audio, const rnd_t *rnd);
void audio_update(audio_t *audio, float activity, float dt);
float audio_energy(const audio_t *audio);
void audio_cleanup(audio_t *audio);
