#include "app.h"
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
static float distortion_curve(float sample, float drive)
{
    float shaped = sample * drive;
    return tanhf(shaped) * (1.0f / tanhf(drive));
}
static void audio_callback(void *userdata, SDL_AudioStream *stream, int additional_amount, int total_amount)
{
    (void)total_amount;
    if (!userdata) {
        SDL_Log("audio_callback: missing userdata\n");
        return;
    }
    audio_t *audio = userdata;
    int frames = additional_amount / sizeof(float);
    if (frames <= 0) {
        return;
    }
    if (frames > 1024) {
        frames = 1024;
    }
    float buffer[1024];
    for (int i = 0; i < frames; i++) {
        float carrier = sinf(audio->phase * (0.78f + rnd_f(&audio->rnd) * 0.62f) + rnd_f(&audio->rnd) * 3.4f);
        float grain = (rnd_f(&audio->rnd) * 2.0f - 1.0f) * (0.18f + rnd_f(&audio->rnd) * 0.34f);
        float glitch = (rnd_f(&audio->rnd) < 0.14f) ? (rnd_f(&audio->rnd) * 2.0f - 1.0f) * (0.34f + rnd_f(&audio->rnd) * 1.1f) : 0.0f;
        float pulse = sinf(audio->phase * (0.18f + rnd_f(&audio->rnd) * 0.22f)) * 0.42f + 0.58f;
        float crunch = floor((grain + glitch + carrier * 0.4f) * (3.8f + rnd_f(&audio->rnd) * 4.2f)) * 0.25f;
        float raw = crunch * (0.28f + rnd_f(&audio->rnd) * 0.58f) + pulse * 0.12f;
        float drive = 1.6f + rnd_f(&audio->rnd) * 3.2f + pulse * 0.5f;
        float shaped = distortion_curve(raw + audio->feedback * 0.16f, drive);
        audio->feedback = shaped * (0.04f + rnd_f(&audio->rnd) * 0.26f) * (rnd_f(&audio->rnd) < 0.4f ? 1.0f : 0.72f);
        buffer[i] = shaped * (0.018f + rnd_f(&audio->rnd) * 0.042f + pulse * 0.14f);
        if (rnd_f(&audio->rnd) < 0.12f) {
            buffer[i] += (rnd_f(&audio->rnd) * 2.0f - 1.0f) * 0.12f;
        }
        if (rnd_f(&audio->rnd) < 0.05f) {
            buffer[i] = -buffer[i];
        }
        float phase_delta = 2.0f * 3.14159265f * (20.0f + rnd_f(&audio->rnd) * 980.0f) / audio->sample_rate;
        audio->phase += phase_delta;
        if (audio->phase >= 2.0f * 3.14159265f) {
            audio->phase -= 2.0f * 3.14159265f;
        }
    }
    SDL_PutAudioStreamData(stream, buffer, frames * sizeof(float));
}
void audio_init(audio_t *audio, const rnd_t *rnd)
{
    memset(audio, 0, sizeof(*audio));
    audio->rnd = *rnd;
    audio->phase = rnd_f(&audio->rnd) * 2.0f * 3.14159265f;
    audio->frequency = 120.0f + rnd_f(&audio->rnd) * 140.0f;
    audio->amplitude = 0.12f + rnd_f(&audio->rnd) * 0.18f;
    audio->energy = 0.0f;
    audio->distortion = 0.28f;
    audio->feedback = 0.0f;
    audio->sample_rate = 48000.0f;
    SDL_AudioSpec spec;
    SDL_zero(spec);
    spec.format = SDL_AUDIO_F32;
    spec.channels = 1;
    spec.freq = (int)audio->sample_rate;
    audio->stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, audio_callback, audio);
    SDL_Log("audio_init: app.audio=%p stream=%p rnd_state=0x%016llx\n", (void *)audio, (void *)audio->stream, (unsigned long long)audio->rnd.state);
    if (audio->stream) {
        SDL_ResumeAudioStreamDevice(audio->stream);
    }
}

void audio_update(audio_t *audio, float activity, float dt)
{
    const float target = clampf_nz(activity, 0.0f, 1.0f);
    audio->energy = clampf_nz(target + (rnd_f(&audio->rnd) - 0.5f) * 0.8f, 0.0f, 1.0f);
    audio->frequency = clampf_nz(60.0f + rnd_f(&audio->rnd) * 1740.0f, 40.0f, 1900.0f);
    audio->distortion = clampf_nz(0.18f + rnd_f(&audio->rnd) * 2.2f, 0.18f, 3.1f);
    audio->amplitude = clampf_nz(0.02f + rnd_f(&audio->rnd) * 0.5f, 0.02f, 1.0f);
    audio->feedback = clampf_nz(rnd_f(&audio->rnd) * 0.98f, 0.0f, 1.0f);
}
float audio_energy(const audio_t *audio)
{
    return audio->energy;
}
void audio_cleanup(audio_t *audio)
{
    if (audio->stream) {
        SDL_DestroyAudioStream(audio->stream);
        audio->stream = NULL;
    }
}
