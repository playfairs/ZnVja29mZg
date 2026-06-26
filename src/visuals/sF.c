#include "app.h"
static void sF_init(app_t *app)
{
    app->sF.glow = rnd_ranged(&app->rnd, 0.12f, 0.24f);
    app->sF.pulse = rnd_ranged(&app->rnd, 0.06f, 0.16f);
}
static void sF_update(app_t *app)
{
    app->sF.glow += sinf(app->time * 0.18f) * 0.0009f;
    app->sF.pulse += cosf(app->time * 0.22f) * 0.0008f;
}
static void sF_render(app_t *app)
{
    for (int y = 0; y < BACK_H; y += 5) {
        for (int x = 0; x < BACK_W; x += 5) {
            float dx = ((float)x - app->center.x) * 0.015f;
            float dy = ((float)y - app->center.y) * 0.015f;
            float mag = sqrtf(dx * dx + dy * dy);
            float value = clampf(sinf(mag * 6.0f + app->time * 0.9f) * 0.2f + 0.12f, 0.0f, 0.35f);
            app_blend(app, x, y, value * (0.7f + app->sF.glow), fractf(app->time * 0.035f + mag * 0.15f + app->sF.pulse));
        }
    }
}
sys_t sF_system = { sF_init, sF_update, sF_render };
