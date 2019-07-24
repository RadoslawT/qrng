#include <simple2d.h>
#include "qrng.h"

S2D_Window *window;

int windowWidth = 640;
int windowHeight = 480;
int screenWidth;
int screenHeight;


float bgValue = 0.0;

void render();
void update();
void bgDarker();
void bgLighter();
void onKey(S2D_Event e);
void setScreenResolution(){
  SDL_DisplayMode dm;

  if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
  {
    printf("FAIL!");
       SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
       return;
  }

  screenWidth = dm.w;
  screenHeight = dm.h;
}

int main() {
  S2D_Diagnostics(true);
  printQrngInfo();

  window = S2D_CreateWindow(
    "Hello Triangle", windowWidth, windowHeight, update, render, S2D_FULLSCREEN
  );

  window->on_key = onKey;
  window->fps_cap = 1;

  setScreenResolution();
  S2D_Show(window);
  S2D_FreeWindow(window);
  exit(EXIT_SUCCESS);
}

void render(){
  S2D_DrawQuad(
    0,           0,            bgValue, bgValue, bgValue, 1,
    0,           screenHeight, bgValue, bgValue, bgValue, 1,
    screenWidth, screenHeight, bgValue, bgValue, bgValue, 1,
    screenWidth, 0,            bgValue, bgValue, bgValue, 1
  );
}

void update(){
  if (window->frames % 5 == 0){
    float similarity;
    similarity = getRandomNumber(6);
    bgValue = similarity;

    printf("%f\n", bgValue);
  }
}

void onKey(S2D_Event e) {
  switch(e.type){
    case S2D_KEY_DOWN:
      if (strcmp(e.key, "Escape") == 0){
        S2D_Close(window);
      }
      break;
  }
}