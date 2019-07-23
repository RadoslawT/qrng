#include <simple2d.h>
#include <random>

S2D_Window *window;

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> dist6(1,10);

int windowWidth = 640;
int windowHeight = 480;
int screenWidth;
int screenHeight;


float bgValue = 0.0;
float bgRed   = 0.0;
float bgGreen = 0.0;
float bgBlue  = 0.0;

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
    int   dist = dist6(rng);
    float similarity = dist / 10.0;
    bgValue = similarity;
    printf("%f\n", bgValue);
    printf("%i\n", dist);
  }
}

void onKey(S2D_Event e) {
  switch(e.type){
    case S2D_KEY_DOWN:
      if (strcmp(e.key, "Up") == 0)
        bgLighter();
      if (strcmp(e.key, "Down") == 0)
        bgDarker();
      if (strcmp(e.key, "Escape") == 0){
        S2D_Close(window);
      }
      break;
  }
}

void bgDarker(){
  if(bgValue < 0.1){
    return;
  }
  puts("darker");
  printf("\nbgValue: %f", bgValue);
  bgValue -= 0.1;
  bgRed = bgGreen = bgBlue = bgValue;
}

void bgLighter(){
  if(bgValue > 0.9){
    return;
  }
  puts("lighter");
  printf("\nbgValue: %f", bgValue);
  bgValue += 0.1;
  bgRed = bgGreen = bgBlue = bgValue;
}