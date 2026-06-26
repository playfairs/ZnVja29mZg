#include "app.h"
static void sA_init(app_t *app)
{
    for (int i = 0; i < 4; i++) {
        app->sA.pole[i].x = rnd_ranged(&app->rnd, 0.0f, (float)BACK_W);
        app->sA.pole[i].y = rnd_ranged(&app->rnd, 0.0f, (float)BACK_H);
        app->sA.bias[i] = rnd_ranged(&app->rnd, 0.6f, 1.4f);
    }
}
static void sA_update(app_t *app)
{
    for (int i = 0; i < 4; i++) {
        app->sA.pole[i].x += sinf(app->time * (0.17f + i * 0.048f)) * 0.4f;
        app->sA.pole[i].y += cosf(app->time * (0.13f + i * 0.053f)) * 0.3f;
    }
}
static void sA_render(app_t *app)
{
    for (int y = 0; y < BACK_H; y += 6) {
        for (int x = 0; x < BACK_W; x += 6) {
            float influence = 0.0f;
            float hue = 0.0f;
            for (int i = 0; i < 4; i++) {
                float dx = app->sA.pole[i].x - x;
                float dy = app->sA.pole[i].y - y;
                float d = sqrtf(dx * dx + dy * dy) + 0.1f;
                float part = app->sA.bias[i] / (d * d);
                influence += part;
                hue += part * (0.16f + i * 0.08f);
            }
            app_blend(app, x, y, clampf(influence * 0.0012f, 0.0f, 0.3f), fractf(hue + app->time * 0.04f));
        }
    }
}
sys_t sA_system = { sA_init, sA_update, sA_render };
