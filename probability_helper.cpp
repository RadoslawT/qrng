#include "probability_helper"

float eventAtAttendProbability(int length, int matches, int attend){
  return 1 - pow(1 - eventProbability(length, matches), attend);
};

float eventProbability(int length, int matches){
  return sumAmountOfEvents(length, matches) / pow(2, length);
};

int sumAmountOfEvents(int length, int matches){
  int elementIndex = length - matches + 1;
  int sum = 0;

  while(elementIndex > 0){
    sum += amountOfEvents(length, elementIndex);
    --elementIndex;
  }

  return sum;
};

int amountOfEvents(int length, int n){
  return factorial(l) / (factorial(length + 1 - n) * factorial(n-1))
};

int factorial(int n){
  if(n == 0)
    return 1;
  if(n == 1 || n == 2)
    return n;
  return factorial(n-1) * n;
}
