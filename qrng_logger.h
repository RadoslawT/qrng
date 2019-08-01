#pragma once

#include <iostream>
#include <chrono>
#include <ctime>
#include <bitset>

class QrngLogger{
  public:

  QrngLogger();
  void log(std::string result);
};
