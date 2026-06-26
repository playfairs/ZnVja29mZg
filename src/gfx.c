#include "gfx.h"
#include <SDL3/SDL.h>
#include <stdlib.h>
int gfx_init(gfx_t *gfx, int w, int h)
{
    gfx->back_w = w;
    gfx->back_h = h;
    if (!SDL_CreateWindowAndRenderer("ZnVja29mZg", w * 2, h * 2, SDL_WINDOW_BORDERLESS, &gfx->window, &gfx->renderer)) {
        return 0;
    }
    gfx->texture = SDL_CreateTexture(gfx->renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, w, h);
    if (!gfx->texture) {
        SDL_DestroyRenderer(gfx->renderer);
        SDL_DestroyWindow(gfx->window);
        gfx->window = NULL;
        gfx->renderer = NULL;
        return 0;
    }
    SDL_SetRenderScale(gfx->renderer, 2.0f, 2.0f);
    return 1;
}
void gfx_present(gfx_t *gfx, uint32_t *pixels, int w, int h)
{
    SDL_UpdateTexture(gfx->texture, NULL, pixels, w * sizeof(uint32_t));
    SDL_SetRenderDrawColor(gfx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(gfx->renderer);
    SDL_RenderTexture(gfx->renderer, gfx->texture, NULL, NULL);
    SDL_RenderPresent(gfx->renderer);
}
void gfx_cleanup(gfx_t *gfx)
{
    if (gfx->texture) {
        SDL_DestroyTexture(gfx->texture);
    }
    if (gfx->renderer) {
        SDL_DestroyRenderer(gfx->renderer);
    }
    if (gfx->window) {
        SDL_DestroyWindow(gfx->window);
    }
}
