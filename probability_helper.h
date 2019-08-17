#pragma once

#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

namespace ProbabilityHelper{
  double compoundEventProbability(int length, int matches, int attends);
  double simpleEventProbability(int length, int matches);
  uint1024_t sumAmountOfEvents(int length, int matches);
  uint1024_t amountOfEvents(int length, int n);
  uint1024_t factorial(int n);
}