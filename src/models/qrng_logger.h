#pragma once

#include <iostream>
#include <chrono>
#include <ctime>
#include <bitset>
#include "quantum_measurement.h"

class QrngLogger{
  public:

  QrngLogger();
  void log(QuantumMeasurement result);
};
