#include "app.h"
#include <math.h>
static void s0_init(app_t *app)
{
    for (int i = 0; i < 4; i++) {
        app->s0.orbit[i].x = app->center.x + rnd_ranged(&app->rnd, -80.0f, 80.0f);
        app->s0.orbit[i].y = app->center.y + rnd_ranged(&app->rnd, -60.0f, 60.0f);
        app->s0.phase[i] = rnd_f(&app->rnd) * 6.2831855f;
        app->s0.speed[i] = rnd_ranged(&app->rnd, 0.9f, 2.2f);
    }
}
static void s0_update(app_t *app)
{
    for (int i = 0; i < 4; i++) {
        app->s0.phase[i] += app->s0.speed[i] * app->dt;
        if (app->s0.phase[i] > 6.2831855f) {
            app->s0.phase[i] -= 6.2831855f;
        }
    }
}
static void s0_render(app_t *app)
{
    for (int i = 0; i < 4; i++) {
        float phase = app->s0.phase[i];
        float px = app->s0.orbit[i].x + cosf(phase) * 38.0f;
        float py = app->s0.orbit[i].y + sinf(phase * 1.31f) * 22.0f;
        float strength = 0.32f + 0.14f * sinf(phase * 1.27f);
        int xi = (int)px;
        int yi = (int)py;
        for (int dy = -4; dy <= 4; dy++) {
            for (int dx = -4; dx <= 4; dx++) {
                float d = sqrtf((float)(dx * dx + dy * dy));
                float w = clampf(1.0f - d * 0.18f, 0.0f, 1.0f);
                float value = w * strength * (0.8f + 0.2f * sinf(phase * 2.3f));
                app_blend(app, xi + dx, yi + dy, value, fractf(phase * 0.16f));
            }
        }
    }
}
sys_t s0_system = { s0_init, s0_update, s0_render };
