#include "app.h"
#include "sys.h"
void sys_register(app_t *app, sys_t system)
{
    app->systems[app->sys_count++] = system;
}
