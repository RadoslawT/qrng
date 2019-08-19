#include "probability_helper.h"
#include <iostream> //todo remove


namespace ProbabilityHelper{
  double compoundEventProbability(int length, int matches, int attends){
    // std::cout << "pa: " << double(1.0 - simpleEventProbability(length, matches)) << " pb: " << attends << "pc: " << simpleEventProbability(length, matches) << "\n";
    return 1 - pow(double(1.0 - simpleEventProbability(length, matches)), attends);
  };

  double simpleEventProbability(int length, int matches){
    // std::cout << "sumAmountOfEvents: " << ((double)sumAmountOfEvents(length, matches)) << " length: " << length << " matches: " << matches << "\n";
    return ((double)sumAmountOfEvents(length, matches)) / pow(2, length);
  };

  uint1024_t sumAmountOfEvents(int length, int matches){
    int elementIndex = length - matches + 1;
    uint1024_t sum = 0;

    while(elementIndex > 0){
      sum += amountOfEvents(length, elementIndex);
      // std::cout << "elementIndex: " << elementIndex << " amountOfEvents: " << amountOfEvents(length, elementIndex) << "\n";
      --elementIndex;
    }

    return sum;
  };

  uint1024_t amountOfEvents(int length, int n){
// std::cout << " 1: " << factorial(length) << " 2: " <<  factorial(length + 1 - n) << " 3: " <<  factorial(n-1) << "\n";
// std::cout << "l: " << length << " l2: " << length + 1 - n << " l3: " << n-1 << "\n";

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