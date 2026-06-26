#pragma once
#include <stddef.h>
typedef struct app_t app_t;
typedef void (*sys_fn)(app_t *);
typedef struct { sys_fn init; sys_fn update; sys_fn render; } sys_t;
void sys_register(app_t *app, sys_t system);
