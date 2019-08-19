#include "probability_helper.h"

namespace ProbabilityHelper{
  double compoundEventProbability(int length, int matches, int attends){
    return 1 - pow(double(1.0 - simpleEventProbability(length, matches)), attends);
  };

  double simpleEventProbability(int length, int matches){
    return ((double)sumAmountOfEvents(length, matches)) / pow(2, length);
  };

  uint1024_t sumAmountOfEvents(int length, int matches){
    int elementIndex = length - matches + 1;
    uint1024_t sum = 0;

    while(elementIndex > 0){
      sum += amountOfEvents(length, elementIndex);
      --elementIndex;
    }

    return sum;
  };

  uint1024_t amountOfEvents(int length, int n){
    return factorial(length) / (factorial(length + 1 - n) * factorial(n-1));
  };

  uint1024_t factorial(int n){
    if(n == 0)
      return 1;
    if(n == 1 || n == 2)
      return n;
    return factorial(n-1) * n;
  };
}