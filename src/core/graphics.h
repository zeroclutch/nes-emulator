#pragma once

#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_rect.h>
#include <SDL/SDL_opengles2.h>

enum NES_COLOR {
    WHITE,
    BLACK,
    GRAY,
    RED,
    GREEN,
    BLUE,
    MAGENTA,
    YELLOW,
    CYAN,
};

typedef struct NES_COLOR_RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} NES_COLOR_RGB;

static NES_COLOR_RGB RGB_MAP[9] = {
  { .r = 0xFF, .g = 0xFF, .b = 0xFF },
  { .r = 0x00, .g = 0x00, .b = 0x00 },
  { .r = 0xAA, .g = 0xAA, .b = 0xAA },
  { .r = 0xFF, .g = 0x00, .b = 0x00 },
  { .r = 0x00, .g = 0xFF, .b = 0x00 },
  { .r = 0x00, .g = 0x00, .b = 0xFF },
  { .r = 0xFF, .g = 0x00, .b = 0xFF },
  { .r = 0xFF, .g = 0xFF, .b = 0x00 },
  { .r = 0x00, .g = 0xFF, .b = 0xFF },
};

int render(uint8_t *pixels, int width, int height);