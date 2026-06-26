#include "app.h"
static void sE_init(app_t *app)
{
    app->sE.spiral = rnd_ranged(&app->rnd, 0.02f, 0.08f);
    app->sE.drift = rnd_ranged(&app->rnd, 0.04f, 0.1f);
}
static void sE_update(app_t *app)
{
    app->sE.spiral += sinf(app->time * 0.11f) * 0.0008f;
    app->sE.drift += cosf(app->time * 0.09f) * 0.0007f;
}
static void sE_render(app_t *app)
{
    for (int y = 0; y < BACK_H; y += 8) {
        for (int x = 0; x < BACK_W; x += 8) {
            float dx = (x - app->center.x) * 0.012f;
            float dy = (y - app->center.y) * 0.012f;
            float angle = atan2f(dy, dx);
            float radius = sqrtf(dx * dx + dy * dy);
            float spin = sinf(angle * 5.0f + app->time * app->sE.spiral) * cosf(radius * 4.0f + app->time * app->sE.drift);
            float value = clampf(spin * 0.22f + 0.06f, 0.0f, 0.4f);
            app_blend(app, x, y, value, fractf(app->time * 0.05f + radius * 0.18f));
        }
    }
}
sys_t sE_system = { sE_init, sE_update, sE_render };
