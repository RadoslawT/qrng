#pragma once

#include <vector>
#include "quantum_measurement.h"

class QuantumMeasurement;
class QuantumMeasurementsSet {
  public:

  int bytesAmount;
  vector<int> patternSequence;
  float probabilityThreshold;
  vector<QuantumMeasurement> measurements;

  QuantumMeasurementsSet(int bytesAmount, std::vector<int> patternSequence, float probabilityThreshold);

  void measure();

  vector<int>::size_type size();
  QuantumMeasurement lastMeasurement();
};
