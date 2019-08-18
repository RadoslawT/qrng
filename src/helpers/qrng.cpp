#include "qrng.h"

void printQrngInfo(){
  int devicesCount = Quantis::Count(QUANTIS_DEVICE_USB);
  printf("Found %i card(s)", devicesCount);
}