#include "app.h"
static void s8_init(app_t *app)
{
    app->s8.decay = rnd_ranged(&app->rnd, 0.82f, 0.92f);
    app->s8.radius = rnd_ranged(&app->rnd, 6.0f, 12.0f);
}
static void s8_update(app_t *app)
{
    app->s8.decay += (0.88f - app->s8.decay) * 0.003f * app->dt * 60.0f;
    app->s8.radius += sinf(app->time * 0.23f) * 0.02f;
}
static void s8_render(app_t *app)
{
    for (int y = 0; y < BACK_H; y += 9) {
        for (int x = 0; x < BACK_W; x += 9) {
            float value = app_sample(app, x, y);
            float effect = value * (0.35f + 0.22f * sinf(app->time * 0.19f + x * 0.03f));
            for (int offset = -(int)app->s8.radius; offset <= (int)app->s8.radius; offset++) {
                app_blend(app, x + offset, y, effect * app->s8.decay, fractf(app->time * 0.027f + (float)offset * 0.12f));
            }
        }
    }
}
sys_t s8_system = { s8_init, s8_update, s8_render };
