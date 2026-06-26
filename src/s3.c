#include "app.h"
static void s3_init(app_t *app)
{
    app->s3.blend = rnd_ranged(&app->rnd, 0.18f, 0.42f);
}
static void s3_update(app_t *app)
{
    app->s3.blend = 0.24f + 0.18f * sinf(app->time * 0.7f);
}
static void s3_render(app_t *app)
{
    for (int y = 0; y < BACK_H; y += 12) {
        for (int x = 0; x < BACK_W; x += 12) {
            float value = 0.2f + 0.14f * sinf((float)x * 0.08f + app->time * 0.6f) * cosf((float)y * 0.07f + app->time * 0.9f);
            int xi = x + ((int)(sinf(app->time * 0.33f + y * 0.12f) * 3.0f));
            int yi = y + ((int)(cosf(app->time * 0.27f + x * 0.14f) * 3.0f));
            app_blend(app, xi, yi, value * app->s3.blend, fractf((float)x / BACK_W + (float)y / BACK_H));
        }
    }
}
sys_t s3_system = { s3_init, s3_update, s3_render };
