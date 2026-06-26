#pragma once
#include <stdint.h>
#include <SDL3/SDL.h>
typedef struct { SDL_Window *window; SDL_Renderer *renderer; SDL_Texture *texture; int back_w; int back_h; } gfx_t;
int gfx_init(gfx_t *gfx, int w, int h);
void gfx_present(gfx_t *gfx, uint32_t *pixels, int w, int h);
void gfx_cleanup(gfx_t *gfx);
