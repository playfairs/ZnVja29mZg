#include "app.h"
static void s1_init(app_t *app)
{
    for (int i = 0; i < 6; i++) {
        app->s1.pos[i].x = rnd_ranged(&app->rnd, 0.0f, (float)BACK_W);
        app->s1.pos[i].y = rnd_ranged(&app->rnd, 0.0f, (float)BACK_H);
        app->s1.vel[i].x = rnd_ranged(&app->rnd, -28.0f, 28.0f);
        app->s1.vel[i].y = rnd_ranged(&app->rnd, -18.0f, 18.0f);
        app->s1.radius[i] = rnd_ranged(&app->rnd, 8.0f, 18.0f);
    }
}
static void s1_update(app_t *app)
{
    for (int i = 0; i < 6; i++) {
        vec2 dir = vec2_sub(app->center, app->s1.pos[i]);
        float dist = vec2_len(dir) + 0.001f;
        float force = 5.0f / dist;
        app->s1.vel[i] = vec2_add(app->s1.vel[i], vec2_mul(dir, force * app->dt * 0.12f));
        app->s1.vel[i] = vec2_mul(app->s1.vel[i], 0.997f);
        app->s1.pos[i] = vec2_add(app->s1.pos[i], vec2_mul(app->s1.vel[i], app->dt));
        if (app->s1.pos[i].x < 0.0f || app->s1.pos[i].x > BACK_W) {
            app->s1.vel[i].x *= -1.0f;
        }
        if (app->s1.pos[i].y < 0.0f || app->s1.pos[i].y > BACK_H) {
            app->s1.vel[i].y *= -1.0f;
        }
    }
}
static void s1_render(app_t *app)
{
    for (int i = 0; i < 6; i++) {
        vec2 p = app->s1.pos[i];
        float r = app->s1.radius[i] * (0.85f + 0.15f * sinf(app->time + (float)i));
        int ri = (int)r;
        for (int dy = -ri; dy <= ri; dy++) {
            for (int dx = -ri; dx <= ri; dx++) {
                float d = sqrtf((float)(dx * dx + dy * dy));
                if (d > r) {
                    continue;
                }
                float w = 1.0f - d / r;
                app_blend(app, (int)p.x + dx, (int)p.y + dy, w * 0.16f, fractf(app->time * 0.06f + (float)i * 0.17f));
            }
        }
    }
}
sys_t s1_system = { s1_init, s1_update, s1_render };
