#include "app.h"
static void s9_init(app_t *app)
{
    app->s9.phase = rnd_int(&app->rnd, 7);
}
static void s9_update(app_t *app)
{
    app->s9.phase = (app->s9.phase + ((int)(app->time * 0.2f) % 2)) % 7;
}
static void s9_render(app_t *app)
{
    int grid = 7;
    for (int y = 0; y < grid; y++) {
        for (int x = 0; x < grid; x++) {
            int px = BACK_W / 2 + (x - grid / 2) * 14;
            int py = BACK_H / 2 + (y - grid / 2) * 14;
            float offset = sinf(app->time * 0.16f + (float)x * 0.5f + (float)y * 0.4f);
            for (int dy = -2; dy <= 2; dy++) {
                for (int dx = -2; dx <= 2; dx++) {
                    float d = fabsf((float)dx) + fabsf((float)dy);
                    float w = clampf(1.0f - d * 0.35f, 0.0f, 1.0f);
                    app_blend(app, px + dx + (int)(offset * 3.0f), py + dy, w * 0.08f, fractf(app->time * 0.09f + x * 0.03f + y * 0.04f));
                }
            }
        }
    }
}
sys_t s9_system = { s9_init, s9_update, s9_render };
