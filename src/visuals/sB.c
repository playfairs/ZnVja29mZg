#include "app.h"
static void sB_init(app_t *app)
{
    app->sB.hue = rnd_f(&app->rnd);
    app->sB.velocity = rnd_ranged(&app->rnd, 0.04f, 0.12f);
}
static void sB_update(app_t *app)
{
    app->sB.hue = fractf(app->sB.hue + app->sB.velocity * app->dt);
}
static void sB_render(app_t *app)
{
    float angle = app->time * 0.2f;
    for (int y = 0; y < BACK_H; y += 3) {
        for (int x = 0; x < BACK_W; x += 3) {
            float nx = ((float)x - app->center.x) * 0.014f;
            float ny = ((float)y - app->center.y) * 0.014f;
            float field = sinf(nx * cosf(angle) - ny * sinf(angle)) * cosf(nx * sinf(angle) + ny * cosf(angle));
            float value = clampf(field * 0.25f + 0.12f, 0.0f, 0.4f);
            app_blend(app, x, y, value, fractf(app->sB.hue + field * 0.09f));
        }
    }
}
sys_t sB_system = { sB_init, sB_update, sB_render };
