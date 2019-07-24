#include "qrng.h"
#include <iostream>
using namespace std;
using namespace idQ;

float getSimilarityRate(int bytesCount){
  QuantisDeviceType deviceType = QUANTIS_DEVICE_USB;
  int deviceNumber = 0;
  Quantis quantis(deviceType, deviceNumber);
  string buffer = quantis.Read(bytesCount);
  unsigned char pattern[6] = { 34, 201, 123, 34, 54, 127 };
  unsigned char b;
  unsigned char c;
  int i = 0;
  int similarityAmount = 0;

  string::iterator it = buffer.begin();

  while (it != buffer.end())
  {
    b = static_cast<unsigned char>(*it++);
    c = ~b^pattern[i];
    similarityAmount += __builtin_popcount(c);

    ++i;
  }

  return similarityAmount / (6 * 8.0);
}

void printQrngInfo(){
  int devicesCount = Quantis::Count(QUANTIS_DEVICE_USB);
  printf("Found %i card(s)", devicesCount);
}