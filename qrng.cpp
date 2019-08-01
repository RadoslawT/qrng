#include "qrng.h"

string getMeasurement(int bytesCount){
  QuantisDeviceType deviceType = QUANTIS_DEVICE_USB;
  int deviceNumber = 0;
  Quantis quantis(deviceType, deviceNumber);

  return quantis.Read(bytesCount);
}

float getSimilarityRate(string buffer){
  unsigned char pattern[6] = { 53, 90, 147, 189, 137, 102 };
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