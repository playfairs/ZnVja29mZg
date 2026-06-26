#include "app.h"
#include <math.h>
static void s2_init(app_t *app)
{
    app->s2.feed = 0.036f;
    app->s2.kill = 0.065f;
}
static void s2_update(app_t *app)
{
    float target = 0.05f + 0.02f * sinf(app->time * 0.8f);
    app->s2.feed += (target - app->s2.feed) * 0.01f * app->dt * 60.0f;
    app->s2.kill += ((0.065f + 0.01f * cosf(app->time * 0.9f)) - app->s2.kill) * 0.01f * app->dt * 60.0f;
}
static void s2_render(app_t *app)
{
    for (int y = 1; y < BACK_H - 1; y++) {
        for (int x = 1; x < BACK_W - 1; x++) {
            int i = y * BACK_W + x;
            float a = app->cell[i];
            float b = app->field_prev[i];
            float lap = app_sample(app, x - 1, y) + app_sample(app, x + 1, y) + app_sample(app, x, y - 1) + app_sample(app, x, y + 1) - 4.0f * a;
            float da = a + (0.16f * lap - a * b * b + app->s2.feed * (1.0f - a)) * app->dt;
            float db = b + (0.08f * lap + a * b * b - (app->s2.kill + 0.05f) * b) * app->dt;
            app->cell[i] = clampf(da, 0.0f, 1.0f);
            app->field_prev[i] = clampf(db, 0.0f, 1.0f);
            app_blend(app, x, y, (da - db) * 0.34f, fractf((float)y / BACK_H + (float)x / BACK_W + app->time * 0.02f));
        }
    }
}
sys_t s2_system = { s2_init, s2_update, s2_render };
