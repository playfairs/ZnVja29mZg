#include "app.h"
static void s4_init(app_t *app)
{
    app->s4.scale = rnd_ranged(&app->rnd, 0.8f, 1.6f);
    app->s4.offset = rnd_ranged(&app->rnd, 0.0f, 6.28f);
}
static void s4_update(app_t *app)
{
    app->s4.scale += sinf(app->time * 0.3f) * 0.003f;
    app->s4.offset += app->dt * 0.13f;
}
static void s4_render(app_t *app)
{
    for (int y = 0; y < BACK_H; y++) {
        for (int x = 0; x < BACK_W; x++) {
            float fx = ((float)x - app->center.x) * 0.018f;
            float fy = ((float)y - app->center.y) * 0.022f;
            float wave = sinf(fx * app->s4.scale + app->s4.offset) * cosf(fy * app->s4.scale - app->s4.offset);
            app_blend(app, x, y, wave * 0.04f, fractf(app->time * 0.041f + wave));
        }
    }
}
sys_t s4_system = { s4_init, s4_update, s4_render };
