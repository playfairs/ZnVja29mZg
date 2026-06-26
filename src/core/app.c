#include "app.h"
#include "util_math.h"
#include <SDL3/SDL.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
app_t app;
extern sys_t s0_system;
extern sys_t s1_system;
extern sys_t s2_system;
extern sys_t s3_system;
extern sys_t s4_system;
extern sys_t s5_system;
extern sys_t s6_system;
extern sys_t s7_system;
extern sys_t s8_system;
extern sys_t s9_system;
extern sys_t sA_system;
extern sys_t sB_system;
extern sys_t sC_system;
extern sys_t sD_system;
extern sys_t sE_system;
extern sys_t sF_system;
static void app_fill_palette(void)
{
    float base = fractf(app.time * 0.24f + rnd_f(&app.rnd) * 0.16f);
    float t0 = fractf(base * 4.8f + rnd_f(&app.rnd) * 0.34f);
    float t1 = fractf(base * 6.2f + rnd_f(&app.rnd) * 0.29f);
    float t2 = fractf(base * 5.5f + rnd_f(&app.rnd) * 0.43f);
    float t3 = fractf(base * 3.7f + rnd_f(&app.rnd) * 0.37f);
    app.palette[0] = app_pack((uint8_t)clampf(32.0f + 220.0f * t0, 0.0f, 255.0f), (uint8_t)clampf(16.0f + 160.0f * t1, 0.0f, 255.0f), (uint8_t)clampf(200.0f - 180.0f * t2, 0.0f, 255.0f), 255);
    app.palette[1] = app_pack((uint8_t)clampf(255.0f - 180.0f * t1, 0.0f, 255.0f), (uint8_t)clampf(80.0f + 180.0f * t2, 0.0f, 255.0f), (uint8_t)clampf(120.0f + 120.0f * t3, 0.0f, 255.0f), 255);
    app.palette[2] = app_pack((uint8_t)clampf(64.0f + 200.0f * t3, 0.0f, 255.0f), (uint8_t)clampf(255.0f - 180.0f * t0, 0.0f, 255.0f), (uint8_t)clampf(32.0f + 210.0f * t1, 0.0f, 255.0f), 255);
    app.palette[3] = app_pack((uint8_t)clampf(255.0f - 100.0f * t2, 0.0f, 255.0f), (uint8_t)clampf(40.0f + 220.0f * t3, 0.0f, 255.0f), (uint8_t)clampf(255.0f - 150.0f * t0, 0.0f, 255.0f), 255);
}
static uint32_t app_tint(uint32_t color, float amount)
{
    uint8_t r = (color >> 24) & 0xFF;
    uint8_t g = (color >> 16) & 0xFF;
    uint8_t b = (color >> 8) & 0xFF;
    uint8_t a8 = color & 0xFF;
    float pulse = 0.6f + 0.6f * sinf(app.time * 12.0f + audio_energy(&app.audio) * 4.5f);
    float rr = clampf(r * amount * pulse + 64.0f, 0.0f, 255.0f);
    float gg = clampf(g * amount * (1.0f + 0.6f * cosf(app.time * 8.3f + audio_energy(&app.audio) * 2.0f)) + 28.0f, 0.0f, 255.0f);
    float bb = clampf(b * amount * (0.85f + 0.7f * sinf(app.time * 9.1f + audio_energy(&app.audio) * 3.5f)) + 44.0f, 0.0f, 255.0f);
    return app_pack((uint8_t)rr, (uint8_t)gg, (uint8_t)bb, a8);
}
static uint32_t app_glitch(uint32_t color, int index)
{
    uint8_t r = (color >> 24) & 0xFF;
    uint8_t g = (color >> 16) & 0xFF;
    uint8_t b = (color >> 8) & 0xFF;
    uint8_t a = color & 0xFF;
    if (((index + (int)(app.time * 13.0f)) & 31) < (5 + (int)(audio_energy(&app.audio) * 4.0f))) {
        uint8_t swap = r;
        r = b;
        b = g;
        g = swap;
    }
    if ((index ^ app.frame) & 7u) {
        r = (uint8_t)(r ^ ((index * 113u) & 0x9F));
        g = (uint8_t)(g ^ ((app.frame * 37u) & 0xAF));
        b = (uint8_t)(b ^ ((index * 47u) & 0x7F));
    }
    if ((((app.frame >> 3) + index) & 127) < (6 + (int)(audio_energy(&app.audio) * 4.5f))) {
        g = (uint8_t)clampf((float)g * 1.4f + 52.0f, 0.0f, 255.0f);
        b = (uint8_t)clampf((float)b * 0.9f + 92.0f, 0.0f, 255.0f);
    }
    if (((index * 17u + app.frame) & 63u) < 5u) {
        r = (uint8_t)clampf(255.0f - (float)r * 0.6f, 0.0f, 255.0f);
    }
    return app_pack(r, g, b, a);
}
int app_loop(void)
{
    bool running = true;
    SDL_Event event;
    uint64_t prev = SDL_GetPerformanceCounter();
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
        uint64_t current = SDL_GetPerformanceCounter();
        uint64_t freq = SDL_GetPerformanceFrequency();
        float dt = (float)(current - prev) / (float)freq;
        prev = current;
        if (dt > 0.05f) {
            dt = 0.05f;
        }
        app.dt = dt;
        app.time += dt;
        for (int i = 0; i < app.sys_count; i++) {
            app.systems[i].update(&app);
        }
        memset(app.field, 0, sizeof(app.field));
        for (int i = 0; i < app.sys_count; i++) {
            app.systems[i].render(&app);
        }
        float field_energy = 0.0f;
        int sample_count = 0;
        for (int y = 0; y < BACK_H; y += 36) {
            for (int x = 0; x < BACK_W; x += 40) {
                field_energy += fabsf(app.field[y * BACK_W + x]);
                sample_count += 1;
            }
        }
        field_energy = clampf(field_energy / (float)sample_count * 0.44f, 0.0f, 1.0f);
        audio_update(&app.audio, field_energy, dt);
        app.palette_t = fractf(app.time * 0.07f + audio_energy(&app.audio) * 0.03f);
        app_fill_palette();
        for (int i = 0; i < BACK_N; i++) {
            float value = clampf(app.field[i] * (0.6f + rnd_f(&app.rnd) * 1.0f) + app.field_prev[i] * (0.1f + rnd_f(&app.rnd) * 0.7f) + app.noise[i] * (0.2f + rnd_f(&app.rnd) * 0.6f) + app.cell[i] * (0.16f + rnd_f(&app.rnd) * 0.7f), -1.0f, 1.0f);
            uint32_t base = app.palette[rnd_int(&app.rnd, 4)];
            float adjustment = 1.0f + value * (1.0f + rnd_f(&app.rnd) * 2.8f) + 0.65f * sinf(app.time * (14.0f + rnd_f(&app.rnd) * 24.0f) + (float)(i & 255) * (0.02f + rnd_f(&app.rnd) * 0.16f));
            uint32_t tinted = app_tint(base, adjustment);
            if (rnd_f(&app.rnd) < 0.4f) {
                uint8_t r = (tinted >> 24) & 0xFF;
                uint8_t g = (tinted >> 16) & 0xFF;
                uint8_t b = (tinted >> 8) & 0xFF;
                r = (uint8_t)clampf(r * (1.2f + 0.6f * value) + rnd_f(&app.rnd) * 120.0f, 0.0f, 255.0f);
                g = (uint8_t)clampf(g * (0.95f + 0.8f * value) + rnd_f(&app.rnd) * 110.0f, 0.0f, 255.0f);
                b = (uint8_t)clampf(b * (1.3f - 0.5f * value) + rnd_f(&app.rnd) * 140.0f, 0.0f, 255.0f);
                tinted = app_pack(r, g, b, 255);
            }
            if (rnd_f(&app.rnd) < 0.22f) {
                tinted = app_glitch(tinted, i);
            }
            if (rnd_f(&app.rnd) < 0.1f) {
                uint32_t random_color = app_pack((uint8_t)(clampf(rnd_f(&app.rnd) * 255.0f, 0.0f, 255.0f)), (uint8_t)(clampf(rnd_f(&app.rnd) * 255.0f, 0.0f, 255.0f)), (uint8_t)(clampf(rnd_f(&app.rnd) * 255.0f, 0.0f, 255.0f)), 255);
                tinted = app_glitch(random_color, i);
            }
            app.canvas[i] = tinted;
            app.field_prev[i] = value * (0.3f + rnd_f(&app.rnd) * 0.5f) + app.field_prev[i] * (0.2f + rnd_f(&app.rnd) * 0.5f);
        }
        for (int i = 0; i < BACK_N; i++) {
            if (rnd_f(&app.rnd) < 0.05f) {
                int x = i % BACK_W;
                int y = i / BACK_W;
                int ox = x + (int)(sinf(app.time * 20.0f + y * 0.025f) * 18.0f);
                int oy = y + (int)(cosf(app.time * 14.0f + x * 0.032f) * 16.0f);
                if (ox < 0) {
                    ox += BACK_W;
                } else if (ox >= BACK_W) {
                    ox -= BACK_W;
                }
                if (oy < 0) {
                    oy += BACK_H;
                } else if (oy >= BACK_H) {
                    oy -= BACK_H;
                }
                uint32_t alt = app.canvas[oy * BACK_W + ox];
                app.canvas[i] = app_glitch(alt, i + (int)app.frame);
            }
            if ((i / BACK_W) % 10 == 0 && rnd_f(&app.rnd) < 0.08f) {
                uint8_t r = (app.canvas[i] >> 24) & 0xFF;
                uint8_t g = (app.canvas[i] >> 16) & 0xFF;
                uint8_t b = (app.canvas[i] >> 8) & 0xFF;
                app.canvas[i] = app_pack(r / 2, g / 2, b / 2, 255);
            }
            if (rnd_f(&app.rnd) < 0.02f) {
                uint8_t r = (app.canvas[i] >> 24) & 0xFF;
                uint8_t g = (app.canvas[i] >> 16) & 0xFF;
                uint8_t b = (app.canvas[i] >> 8) & 0xFF;
                app.canvas[i] = app_pack(b, r, g, 255);
            }
        }
        gfx_present(&app.gfx, app.canvas, BACK_W, BACK_H);
        app.frame += 1;
    }
    gfx_cleanup(&app.gfx);
    SDL_Quit();
    return 0;
}
void app_blend(app_t *app, int x, int y, float value, float hue)
{
    if (x < 0 || x >= BACK_W || y < 0 || y >= BACK_H) {
        return;
    }
    int idx = y * BACK_W + x;
    float modulation = sinf(hue * 30.0f + app->time * 8.0f) * cosf(app->time * 5.0f + idx * 0.023f);
    app->field[idx] += value * (1.2f + 0.28f * modulation);
    if (fractf(app->time * 9.0f + idx * 0.009f) > 0.84f) {
        app->field[idx] += (fractf(app->time * 84.0f + idx * 0.21f) - 0.5f) * 0.48f;
    }
    if (((idx + app->frame) & 63) < 11) {
        app->noise[idx] += 0.12f * value * fractf(app->time * 18.0f + idx * 0.073f);
    } else {
        app->noise[idx] += 0.06f * value;
    }
}
float app_sample(const app_t *app, int x, int y)
{
    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }
    if (x >= BACK_W) {
        x = BACK_W - 1;
    }
    if (y >= BACK_H) {
        y = BACK_H - 1;
    }
    return app->field[y * BACK_W + x];
}
float app_samplef(const app_t *app, int x, int y)
{
    int x0 = x < 0 ? 0 : x >= BACK_W ? BACK_W - 1 : x;
    int y0 = y < 0 ? 0 : y >= BACK_H ? BACK_H - 1 : y;
    return app->field[y0 * BACK_W + x0];
}
uint32_t app_pack(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | a;
}
void app_init(void)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    app.width = BACK_W * 2;
    app.height = BACK_H * 2;
    app.center = vec2f((float)BACK_W * 0.5f, (float)BACK_H * 0.5f);
    rnd_init(&app.rnd, (uint64_t)SDL_GetPerformanceCounter() ^ 0x9E3779B97F4A7C15ull);
    audio_init(&app.audio, &app.rnd);
    app.sys_count = 0;
    memset(app.canvas, 0, sizeof(app.canvas));
    memset(app.field, 0, sizeof(app.field));
    memset(app.field_prev, 0, sizeof(app.field_prev));
    memset(app.cell, 0, sizeof(app.cell));
    memset(app.noise, 0, sizeof(app.noise));
    app.frame = 0;
    app.time = 0.0f;
    app.dt = 1.0f / 60.0f;
    app.palette_t = 0.0f;
    app_fill_palette();
    for (int i = 0; i < BACK_N; i++) {
        app.noise[i] = rnd_f(&app.rnd) * 0.18f;
    }
    gfx_init(&app.gfx, BACK_W, BACK_H);
    sys_register(&app, s0_system);
    sys_register(&app, s1_system);
    sys_register(&app, s2_system);
    sys_register(&app, s3_system);
    sys_register(&app, s4_system);
    sys_register(&app, s5_system);
    sys_register(&app, s6_system);
    sys_register(&app, s7_system);
    sys_register(&app, s8_system);
    sys_register(&app, s9_system);
    sys_register(&app, sA_system);
    sys_register(&app, sB_system);
    sys_register(&app, sC_system);
    sys_register(&app, sD_system);
    sys_register(&app, sE_system);
    sys_register(&app, sF_system);
    if (app.gfx.window) {
        for (int i = 0; i < app.sys_count; i++) {
            if (app.systems[i].init) {
                app.systems[i].init(&app);
            }
        }
    }
}
