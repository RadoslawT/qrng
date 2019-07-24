#include <simple2d.h>
#include "qrng.h"

S2D_Window *window;

const float WHITE_BG      = 1.0;
const float LIGHT_GRAY_BG = 0.75;
const float GRAY_BG       = 0.5;
const float DARK_GRAY_BG  = 0.25;
const float BLACK_BG      = 0.0;

int windowWidth = 1920;
int windowHeight = 1200;
int screenWidth;
int screenHeight;

float bgValue = 0.0;

void render();
void update();
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
float calculateBgValue(float similarity);
bool inRange(float x, float low, float high);

int main() {
  S2D_Diagnostics(true);
  printQrngInfo();

  window = S2D_CreateWindow(
    "Hello Triangle", windowWidth, windowHeight, update, render, S2D_FULLSCREEN
  );

  window->on_key = onKey;
  window->fps_cap = 2;

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
  if (window->frames % 1 == 0){
    float similarity;
    similarity = getSimilarityRate(6);

    if(bgValue != WHITE_BG)
      bgValue = calculateBgValue(similarity);

    printf("similarity: %f\n", similarity);
  }
}

float calculateBgValue(float similarity){
  if(inRange(similarity, 0.0, 0.1) || inRange(similarity, 0.9, 1.0))
    return WHITE_BG;

  if(inRange(similarity, 0.1, 0.2) || inRange(similarity, 0.8, 0.9))
    return LIGHT_GRAY_BG;

  if(inRange(similarity, 0.2, 0.3) || inRange(similarity, 0.7, 0.8))
    return GRAY_BG;

  if(inRange(similarity, 0.3, 0.4) || inRange(similarity, 0.6, 0.7))
    return DARK_GRAY_BG;

  if(inRange(similarity, 0.4, 0.6))
    return BLACK_BG;
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

bool inRange(float x, float low, float high)
{
  return ((x-high)*(x-low) <= 0.0);
}