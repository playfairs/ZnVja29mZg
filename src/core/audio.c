#include "audio.h"
#include "util_math.h"
#include <math.h>
#include <string.h>
static float clampf_nz(float value, float min, float max)
{
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}
void audio_init(audio_t *audio, rnd_t *rnd)
{
    memset(audio, 0, sizeof(*audio));
    audio->rnd = rnd;
    audio->phase = rnd_f(rnd) * 6.2831855f;
    audio->frequency = 110.0f + rnd_f(rnd) * 120.0f;
    audio->amplitude = 0.18f + rnd_f(rnd) * 0.22f;
    audio->energy = 0.0f;
}
void audio_update(audio_t *audio, float activity, float dt)
{
    const float target = clampf_nz(activity, 0.0f, 1.0f);
    const float smooth = 0.96f;
    audio->energy = mixf(audio->energy, target, 1.0f - smooth);
    audio->frequency += (0.5f - rnd_f(audio->rnd)) * 6.0f * dt;
    audio->frequency = clampf_nz(audio->frequency, 80.0f, 480.0f);
    audio->phase += audio->frequency * dt * (1.0f + audio->energy * 2.0f);
    audio->phase = fmodf(audio->phase, 6.2831855f);
    audio->amplitude = mixf(audio->amplitude, 0.24f + audio->energy * 0.34f, 0.08f);
}
float audio_energy(const audio_t *audio)
{
    return audio->energy;
}
void audio_cleanup(audio_t *audio)
{
    (void)audio;
}
