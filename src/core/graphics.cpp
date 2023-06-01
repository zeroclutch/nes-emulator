// Copyright 2011 The Emscripten Authors.  All rights reserved.
// Emscripten is available under two separate licenses, the MIT license and the
// University of Illinois/NCSA Open Source License.  Both these licenses can be
// found in the LICENSE file.
#include <emscripten.h>
#include "graphics.h"

NES_COLOR_RGB* getColor(int color) {

  switch(color) {
    case 0: return &(RGB_MAP[NES_COLOR::BLACK]);
    case 1: return &(RGB_MAP[NES_COLOR::WHITE]);
    case 2: case 9:  return &(RGB_MAP[NES_COLOR::GRAY]);
    case 3: case 10: return &(RGB_MAP[NES_COLOR::RED]);
    case 4: case 11: return &(RGB_MAP[NES_COLOR::GREEN]);
    case 5: case 12: return &(RGB_MAP[NES_COLOR::BLUE]);
    case 6: case 13: return &(RGB_MAP[NES_COLOR::MAGENTA]);
    case 7: case 14: return &(RGB_MAP[NES_COLOR::YELLOW]);
    default: return &(RGB_MAP[NES_COLOR::CYAN]);
  }
}

int render(uint8_t *pixels, int width, int height) {
  emscripten_log(EM_LOG_CONSOLE, "rendered frame");

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode(32, 32, 32, SDL_SWSURFACE);

#ifdef TEST_SDL_LOCK_OPTS
  EM_ASM("SDL.defaults.copyOnLock = false; SDL.defaults.discardOnLock = true; SDL.defaults.opaqueFrontBuffer = false;");
#endif

  if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 32; j++) {
      // Read pixel
      NES_COLOR_RGB *color = getColor(pixels[i * 32 + j]);

      *((Uint32*)screen->pixels + i * 32 + j) = SDL_MapRGBA(screen->format, color->r, color->g, color->b, 255);
    }
  }
  if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
  SDL_Flip(screen); 

  return 0;
}

