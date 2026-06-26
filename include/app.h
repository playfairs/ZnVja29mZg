#pragma once
#include <stdint.h>
#include <math.h>
#include "vec.h"
#include "gfx.h"
#include "rnd.h"
#include "audio.h"
#include "sys.h"
#include "util_math.h"
#define BACK_W 640
#define BACK_H 360
#define BACK_N (BACK_W * BACK_H)
#define SYS_MAX 32
typedef struct s0_t { vec2 orbit[4]; float phase[4]; float speed[4]; } s0_t;
typedef struct s1_t { vec2 pos[6]; vec2 vel[6]; float radius[6]; } s1_t;
typedef struct s2_t { float feed; float kill; } s2_t;
typedef struct s3_t { float blend; } s3_t;
typedef struct s4_t { float scale; float offset; } s4_t;
typedef struct s5_t { int grid[12][18]; int drawer; } s5_t;
typedef struct s6_t { float phase[5]; } s6_t;
typedef struct s7_t { vec2 attract[3]; float mass[3]; } s7_t;
typedef struct s8_t { float decay; float radius; } s8_t;
typedef struct s9_t { int phase; } s9_t;
typedef struct sA_t { vec2 pole[4]; float bias[4]; } sA_t;
typedef struct sB_t { float hue; float velocity; } sB_t;
typedef struct sC_t { vec2 node[10]; int edge[18][2]; int edge_count; } sC_t;
typedef struct sD_t { float energy[6]; float coupling[6]; } sD_t;
typedef struct sE_t { float spiral; float drift; } sE_t;
typedef struct sF_t { float glow; float pulse; } sF_t;
typedef struct app_t {
    gfx_t gfx;
    rnd_t rnd;
    audio_t audio;
    int width;
    int height;
    float time;
    float dt;
    uint64_t frame;
    vec2 center;
    float palette_t;
    uint32_t palette[4];
    uint32_t canvas[BACK_N];
    float field[BACK_N];
    float field_prev[BACK_N];
    float cell[BACK_N];
    float noise[BACK_N];
    s0_t s0;
    s1_t s1;
    s2_t s2;
    s3_t s3;
    s4_t s4;
    s5_t s5;
    s6_t s6;
    s7_t s7;
    s8_t s8;
    s9_t s9;
    sA_t sA;
    sB_t sB;
    sC_t sC;
    sD_t sD;
    sE_t sE;
    sF_t sF;
    sys_t systems[SYS_MAX];
    int sys_count;
} app_t;
extern app_t app;
void app_init(void);
int app_loop(void);
void app_blend(app_t *app, int x, int y, float value, float hue);
float app_sample(const app_t *app, int x, int y);
uint32_t app_pack(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
