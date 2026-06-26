#include "app.h"
#include "sys.h"
void sys_register(app_t *app, sys_t system)
{
    if (app->sys_count < SYS_MAX) {
        app->systems[app->sys_count++] = system;
    }
}
