#include "quantum_measurements_set.h"

QuantumMeasurementsSet::QuantumMeasurementsSet(int bytesAmount, std::vector<int> patternSequence, float probabilityThreshold) 
  : bytesAmount(bytesAmount), patternSequence(patternSequence), probabilityThreshold(probabilityThreshold), measurements({}) {}

void QuantumMeasurementsSet::measure(){
  QuantumMeasurement measurement(size(), this);
  measurement.measure();
  measurements.push_back(measurement);
}

vector<int>::size_type QuantumMeasurementsSet::size(){
  return measurements.size();
}

QuantumMeasurement QuantumMeasurementsSet::lastMeasurement(){
  return measurements.back();
}
