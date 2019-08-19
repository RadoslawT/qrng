#pragma once

#include <simple2d.h>
#include <iostream>
#include "../helpers/qrng.h"
#include "../models/qrng_logger.h"
#include "../helpers/probability_helper.h"
#include "../models/quantum_measurements_set.h"

using namespace std;

void onKey(S2D_Event e);

namespace RandomImageRenderer{

  void renderRandomScreens();


  void setScreenResolution();
  float calculateBgValue(float similarity);
  bool inRange(float x, float low, float high);
  void render();
  void update();
};
