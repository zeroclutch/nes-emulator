// Copyright 2011 The Emscripten Authors.  All rights reserved.
// Emscripten is available under two separate licenses, the MIT license and the
// University of Illinois/NCSA Open Source License.  Both these licenses can be
// found in the LICENSE file.
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
  printf("hello, world!\n");

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode(32, 32, 8, SDL_SWSURFACE);

#ifdef TEST_SDL_LOCK_OPTS
  EM_ASM("SDL.defaults.copyOnLock = false; SDL.defaults.discardOnLock = true; SDL.defaults.opaqueFrontBuffer = false;");
#endif

  if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 32 * 3; j+=3) {
#ifdef TEST_SDL_LOCK_OPTS
      // Alpha behaves like in the browser, so write proper opaque pixels.
      int alpha = 255;
#else
      // To emulate native behavior with blitting to screen, alpha component is ignored. Test that it is so by outputting
      // data (and testing that it does get discarded)
      int alpha = (i+j) % 255;
#endif
      // Read pixel
      NES_COLOR_RGB *color = getColor(pixels[i * 32 + j]);

      *((Uint32*)screen->pixels + i * 32 + j) = SDL_MapRGBA(screen->format, color->r, color->g, color->b, alpha);
    }
  }
  if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
  SDL_Flip(screen); 

  printf("you should see a smoothly-colored square - no sharp lines but the square borders!\n");
  printf("and here is some text that should be HTML-friendly: amp: |&| double-quote: |\"| quote: |'| less-than, greater-than, html-like tags: |<cheez></cheez>|\nanother line.\n");

  SDL_Quit();

  return 0;
}

