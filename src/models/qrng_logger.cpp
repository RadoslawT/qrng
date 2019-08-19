#include "qrng_logger.h"

using namespace std;

QrngLogger::QrngLogger(){
  string fileName;
  auto start =  chrono::system_clock::now();
  time_t startTime = chrono::system_clock::to_time_t(start);
  fileName = ctime(&startTime);
}

void QrngLogger::log(QuantumMeasurement m){
  float similarity =  m.sharedElementsAmount / (m.bytesAmount() * 8.0);
  cout  << m.index << "," << m.createdAt << "," << m.simpleProbability << "," << similarity << "," << m.compoundProbability << 
    "," << m.generatedSequenceBinaryString() << "," << m.probabilityThreshold() << "," << m.patternSequenceBinaryString() << "\n";
}
