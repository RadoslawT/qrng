#pragma once

#include <vector>
#include <iostream>

using namespace std;

namespace CastHelper{
  vector<int> unsignedCharsToIntBytes(string stringResults);

  string intBytesToBinaryString(vector<int> intBytes);

  string unsignedCharsToBinaryString(string stringResults);
}