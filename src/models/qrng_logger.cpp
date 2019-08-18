#include "qrng_logger.h"

using namespace std;

QrngLogger::QrngLogger(){
  string fileName;
  auto start =  chrono::system_clock::now();
  time_t startTime = chrono::system_clock::to_time_t(start);
  fileName = ctime(&startTime);
}

void QrngLogger::log(string result){
  string::iterator it = result.begin();
  int byte;
  string binaryStr = "";

  while (it != result.end())
  {
    byte = (int)static_cast<unsigned char>(*it++);
    binaryStr.append(bitset<8>(byte).to_string());
  }

  cout << binaryStr << ' ';
}
