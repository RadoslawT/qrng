#pragma once

#include <vector>
#include <iostream>
#include <chrono>
#include "Quantis.hpp"
#include "../helpers/cast_helper.h"
#include "../helpers/probability_helper.h"
#include "quantum_measurements_set.h"

using namespace idQ;

class QuantumMeasurementsSet;

class QuantumMeasurement{
  public:
  int index;
  QuantumMeasurementsSet* measurementsSet;
  time_t createdAt;
  float simpleProbability;
  float compoundProbability;
  int sharedElementsAmount;
  vector<int> generatedSequence;

  QuantumMeasurement(int index, QuantumMeasurementsSet* measurementsSet);

  void measure();

  private:

  vector<int> getMeasurement();

  int getSharedElementsAmount(vector<int> sequence);
  int bytesAmount();
  vector<int> patternSequence();
};
