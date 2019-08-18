#include <simple2d.h>
#include <iostream>
#include "helpers/qrng.h"
#include "models/qrng_logger.h"
#include "helpers/probability_helper.h"
#include "models/quantum_measurements_set.h"

using namespace std;

S2D_Window *window;

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

QrngLogger logger;

int         bytesAmount = 6;
vector<int> patternSequence = { 36, 17, 153, 19, 238, 87 };
float       probabilityThreshold = 0.001;

QuantumMeasurementsSet measurements(bytesAmount, patternSequence, probabilityThreshold);

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
    "Screen", windowWidth, windowHeight, update, render, S2D_FULLSCREEN
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
    measurements.measure();
    float  compoundProbability = measurements.lastMeasurement().compoundProbability;

    if(bgValue != WHITE_BG)
      bgValue = calculateBgValue(compoundProbability);

    printf("compoundProbability: %f\n", compoundProbability);
  }
}

float calculateBgValue(float probability){
  if(inRange(probability, 0.0, probabilityThreshold))
    return WHITE_BG;
  else
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
