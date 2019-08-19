#include "quantum_measurement.h"

QuantumMeasurement::QuantumMeasurement(int index, QuantumMeasurementsSet* measurementsSet) : index(index), measurementsSet(measurementsSet) {}

void QuantumMeasurement::measure(){
  auto now =  chrono::system_clock::now();
  createdAt = chrono::system_clock::to_time_t(now);

  generatedSequence    = getMeasurement();
  sharedElementsAmount = getSharedElementsAmount(generatedSequence);
  simpleProbability    = ProbabilityHelper::simpleEventProbability(bytesAmount()*8, sharedElementsAmount);
  compoundProbability  = ProbabilityHelper::compoundEventProbability(bytesAmount()*8, sharedElementsAmount, index+1);
}


vector<int> QuantumMeasurement::getMeasurement(){
  QuantisDeviceType deviceType = QUANTIS_DEVICE_USB;
  int deviceNumber = 0;
  Quantis quantis(deviceType, deviceNumber);

  return CastHelper::unsignedCharsToIntBytes(quantis.Read(bytesAmount()));
}

int QuantumMeasurement::getSharedElementsAmount(vector<int> sequence){
  unsigned char b;
  unsigned char c;
  int sharedElementsAmount = 0;

  vector<int>::iterator sequenceIt = sequence.begin(), patternIt = patternSequence().begin();

  while (sequenceIt != sequence.end())
  {
    c = ~*sequenceIt++^*patternIt++;
    sharedElementsAmount += __builtin_popcount(c);
  }

  return sharedElementsAmount;
}

int QuantumMeasurement::bytesAmount(){
  return measurementsSet->bytesAmount;
}

vector<int> QuantumMeasurement::patternSequence(){
  return measurementsSet->patternSequence;
}

float QuantumMeasurement::probabilityThreshold(){
  return measurementsSet->probabilityThreshold;
}

string QuantumMeasurement::patternSequenceBinaryString(){
  return CastHelper::intBytesToBinaryString(patternSequence());
}

string QuantumMeasurement::generatedSequenceBinaryString(){
  return CastHelper::intBytesToBinaryString(generatedSequence);
}