#include "app.h"
#include <math.h>
static void sC_init(app_t *app)
{
    for (int i = 0; i < 10; i++) {
        app->sC.node[i].x = rnd_ranged(&app->rnd, 0.0f, (float)BACK_W);
        app->sC.node[i].y = rnd_ranged(&app->rnd, 0.0f, (float)BACK_H);
    }
    app->sC.edge_count = 0;
    for (int i = 0; i < 18; i++) {
        app->sC.edge[i][0] = rnd_int(&app->rnd, 10);
        app->sC.edge[i][1] = rnd_int(&app->rnd, 10);
        if (app->sC.edge[i][0] != app->sC.edge[i][1]) {
            app->sC.edge_count += 1;
        }
    }
}
static void sC_update(app_t *app)
{
    if (((int)(app->time * 0.6f) & 31) == 0) {
        int index = rnd_int(&app->rnd, 10);
        app->sC.node[index].x = rnd_ranged(&app->rnd, 0.0f, (float)BACK_W);
        app->sC.node[index].y = rnd_ranged(&app->rnd, 0.0f, (float)BACK_H);
    }
}
static void sC_render(app_t *app)
{
    for (int e = 0; e < app->sC.edge_count; e++) {
        int a = app->sC.edge[e][0];
        int b = app->sC.edge[e][1];
        vec2 p0 = app->sC.node[a];
        vec2 p1 = app->sC.node[b];
        float dx = p1.x - p0.x;
        float dy = p1.y - p0.y;
        float len = vec2_len((vec2){dx, dy}) + 0.0001f;
        int steps = (int)clampf(len / 4.0f, 4.0f, 24.0f);
        for (int i = 0; i <= steps; i++) {
            float t = (float)i / (float)steps;
            int x = (int)(p0.x + dx * t + sinf(t * 6.2831855f + app->time * 0.3f) * 3.0f);
            int y = (int)(p0.y + dy * t + cosf(t * 6.2831855f + app->time * 0.4f) * 3.0f);
            app_blend(app, x, y, 0.12f + 0.08f * sinf(t * 12.0f), fractf(app->time * 0.02f + t));
        }
    }
}
sys_t sC_system = { sC_init, sC_update, sC_render };
