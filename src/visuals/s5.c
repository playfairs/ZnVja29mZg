#include "app.h"
static void s5_init(app_t *app)
{
    for (int y = 0; y < 12; y++) {
        for (int x = 0; x < 18; x++) {
            app->s5.grid[y][x] = rnd_int(&app->rnd, 3);
        }
    }
    app->s5.drawer = rnd_int(&app->rnd, 3);
}
static void s5_update(app_t *app)
{
    if (((int)app->time & 31) == 0) {
        int x = rnd_int(&app->rnd, 18);
        int y = rnd_int(&app->rnd, 12);
        app->s5.grid[y][x] = (app->s5.grid[y][x] + 1) % 3;
    }
}
static void s5_render(app_t *app)
{
    for (int y = 0; y < 12; y++) {
        for (int x = 0; x < 18; x++) {
            int mode = app->s5.grid[y][x];
            float cx = x * 35.0f + 18.0f + sinf(app->time * 0.5f + (float)y) * 6.0f;
            float cy = y * 25.0f + 20.0f + cosf(app->time * 0.4f + (float)x) * 4.0f;
            float strength = 0.1f + mode * 0.06f;
            int ix = (int)cx;
            int iy = (int)cy;
            for (int dy = -3; dy <= 3; dy++) {
                for (int dx = -6; dx <= 6; dx++) {
                    float d = fabsf((float)dx) * 0.18f + fabsf((float)dy) * 0.22f;
                    float w = clampf(1.0f - d, 0.0f, 1.0f);
                    app_blend(app, ix + dx, iy + dy, w * strength * 0.9f, fractf(app->time * 0.05f + mode * 0.11f));
                }
            }
        }
    }
}
sys_t s5_system = { s5_init, s5_update, s5_render };
