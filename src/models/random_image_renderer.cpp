#include "random_image_renderer.h"

namespace RandomImageRenderer{
  const float WHITE_BG      = 1.0;
  const float LIGHT_GRAY_BG = 0.75;
  const float GRAY_BG       = 0.5;
  const float DARK_GRAY_BG  = 0.07;
  const float BLACK_BG      = 0.0;

  int windowWidth = 1920;
  int windowHeight = 1200;
  int screenWidth;
  int screenHeight;

  float bgValue = 0.0;

  int         bytesAmount = 6;
  vector<int> patternSequence = { 36, 17, 153, 19, 238, 87 };
  float       probabilityThreshold = 0.20;

  QuantumMeasurementsSet measurements(bytesAmount, patternSequence, probabilityThreshold);

  S2D_Window *window;
  QrngLogger* logger;
}

void RandomImageRenderer::renderRandomScreens(){
  S2D_Diagnostics(true);

  RandomImageRenderer::window = S2D_CreateWindow(
    "Screen", windowWidth, windowHeight, update, render, S2D_FULLSCREEN
  );

  window->on_key = onKey;
  window->fps_cap = 2;

  setScreenResolution();
  S2D_Show(window);
  S2D_FreeWindow(window);
}

void RandomImageRenderer::render(){
  S2D_DrawQuad(
    0,           0,            bgValue, bgValue, bgValue, 1,
    0,           screenHeight, bgValue, bgValue, bgValue, 1,
    screenWidth, screenHeight, bgValue, bgValue, bgValue, 1,
    screenWidth, 0,            bgValue, bgValue, bgValue, 1
  );
}

void RandomImageRenderer::update(){
  if (window->frames % 1 == 0){
    measurements.measure();
    QuantumMeasurement m = measurements.lastMeasurement();

    if(bgValue != WHITE_BG)
      bgValue = calculateBgValue(m.compoundProbability);

    logger->log(m);
  }
}

void RandomImageRenderer::setScreenResolution(){
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

float RandomImageRenderer::calculateBgValue(float probability){
  if(inRange(probability, 0.0, probabilityThreshold))
    return WHITE_BG;
  else
    return BLACK_BG;
}

void onKey(S2D_Event e) {
  switch(e.type){
    case S2D_KEY_DOWN:
      if (strcmp(e.key, "Escape") == 0){
        S2D_Close(RandomImageRenderer::window);
      }
      break;
  }
}

bool RandomImageRenderer::inRange(float x, float low, float high)
{
  return ((x-high)*(x-low) <= 0.0);
}
