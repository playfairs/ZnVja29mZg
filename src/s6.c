#include "app.h"
#include <math.h>
static void s6_init(app_t *app)
{
    for (int i = 0; i < 5; i++) {
        app->s6.phase[i] = rnd_f(&app->rnd) * 6.2831855f;
    }
}
static void s6_update(app_t *app)
{
    for (int i = 0; i < 5; i++) {
        app->s6.phase[i] += app->dt * (0.6f + i * 0.07f);
        if (app->s6.phase[i] > 6.2831855f) {
            app->s6.phase[i] -= 6.2831855f;
        }
    }
}
static void s6_render(app_t *app)
{
    for (int y = 0; y < BACK_H; y += 5) {
        for (int x = 0; x < BACK_W; x += 5) {
            float sum = 0.0f;
            for (int i = 0; i < 5; i++) {
                float angle = app->s6.phase[i] + (float)x * 0.02f + (float)y * 0.03f * (1.0f + i * 0.12f);
                sum += sinf(angle) * cosf(angle * 1.19f);
            }
            float value = smoothstepf(-1.0f, 1.0f, sum * 0.25f);
            app_blend(app, x, y, value * 0.28f, fractf(app->time * 0.033f + sum * 0.08f));
        }
    }
}
sys_t s6_system = { s6_init, s6_update, s6_render };
