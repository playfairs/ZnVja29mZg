#include "app.h"
static void sD_init(app_t *app)
{
    for (int i = 0; i < 6; i++) {
        app->sD.energy[i] = rnd_ranged(&app->rnd, 0.06f, 0.18f);
        app->sD.coupling[i] = rnd_ranged(&app->rnd, 0.2f, 0.8f);
    }
}
static void sD_update(app_t *app)
{
    for (int i = 0; i < 6; i++) {
        float next = app->sD.energy[(i + 1) % 6];
        app->sD.energy[i] += (next - app->sD.energy[i]) * app->sD.coupling[i] * app->dt;
        app->sD.energy[i] = clampf(app->sD.energy[i], 0.0f, 1.0f);
    }
}
static void sD_render(app_t *app)
{
    for (int i = 0; i < 6; i++) {
        float angle = app->time * (0.4f + i * 0.12f);
        float radius = 20.0f + app->sD.energy[i] * 42.0f;
        float cx = app->center.x + cosf(angle * 1.13f) * (40.0f + i * 8.0f);
        float cy = app->center.y + sinf(angle * 0.97f) * (32.0f + i * 6.0f);
        for (int j = 0; j < 8; j++) {
            float sub = j * 0.79f;
            int x = (int)(cx + cosf(angle + sub) * radius);
            int y = (int)(cy + sinf(angle + sub) * radius);
            app_blend(app, x, y, 0.13f + app->sD.energy[i] * 0.06f, fractf(app->time * 0.04f + i * 0.07f + j * 0.09f));
        }
    }
}
sys_t sD_system = { sD_init, sD_update, sD_render };
