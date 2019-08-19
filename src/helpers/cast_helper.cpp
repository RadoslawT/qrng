#include <bitset>
#include "cast_helper.h"

namespace CastHelper{
  vector<int> unsignedCharsToIntBytes(string stringResults){
    string::iterator it = stringResults.begin();
    vector<int> bytes;

    while (it != stringResults.end())
      bytes.push_back((int)static_cast<unsigned char>(*it++));

    return bytes;
  }

  string intBytesToBinaryString(vector<int> intBytes){
    vector<int>::iterator it = intBytes.begin();
    string binaryStr = "";

    while (it != intBytes.end())
      binaryStr.append(bitset<8>(*it++).to_string());

    return binaryStr;
  }

  string unsignedCharsToBinaryString(string stringResults){
    vector<int> bytes = unsignedCharsToIntBytes(stringResults);
    return intBytesToBinaryString(bytes);
  }
}
