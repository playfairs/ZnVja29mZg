#include "app.h"
#include <math.h>
static void s7_init(app_t *app)
{
    for (int i = 0; i < 3; i++) {
        app->s7.attract[i].x = rnd_ranged(&app->rnd, 0.0f, (float)BACK_W);
        app->s7.attract[i].y = rnd_ranged(&app->rnd, 0.0f, (float)BACK_H);
        app->s7.mass[i] = rnd_ranged(&app->rnd, 18.0f, 42.0f);
    }
}
static void s7_update(app_t *app)
{
    for (int i = 0; i < 3; i++) {
        app->s7.attract[i].x += sinf(app->time * (0.3f + i * 0.12f)) * 0.3f;
        app->s7.attract[i].y += cosf(app->time * (0.4f + i * 0.13f)) * 0.2f;
    }
}
static void s7_render(app_t *app)
{
    for (int i = 0; i < 3; i++) {
        vec2 p = app->s7.attract[i];
        float mass = app->s7.mass[i] * (0.9f + 0.1f * sinf(app->time * 0.5f + i));
        int ri = (int)mass;
        for (int dy = -ri; dy <= ri; dy++) {
            for (int dx = -ri; dx <= ri; dx++) {
                float d = sqrtf((float)(dx * dx + dy * dy));
                if (d > mass) {
                    continue;
                }
                float cur = app_sample(app, (int)p.x + dx, (int)p.y + dy);
                float value = (mass - d) * 0.002f + cur * 0.06f;
                app_blend(app, (int)p.x + dx, (int)p.y + dy, value, fractf(app->time * 0.025f + i * 0.16f));
            }
        }
    }
}
sys_t s7_system = { s7_init, s7_update, s7_render };
