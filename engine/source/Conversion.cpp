#include "Conversion.hpp"

using namespace std;

bool String::to_bool(const string& convert)
{
  if (convert == "1" || convert == "true")
  {
    return true;
  }

  return false;
}

// JCD FIXME: TURN THESE INTO TEMPLATE FUNCTIONS AND HOOK THE VARIOUS FNS INTO A COMMON ONE
int String::to_int(const string& convert)
{
  int converted_string;
  istringstream buffer(convert);
  buffer >> converted_string;
  return converted_string;
}

float String::to_float(const string& convert)
{
  float converted_string;
  istringstream buffer(convert);
  buffer >> converted_string;
  return converted_string;
}

string Integer::to_string(const int convert)
{
  string converted_int;
  ostringstream buffer;
  buffer << convert;
  converted_int = buffer.str();
  return converted_int;
}

#ifdef UNIT_TESTS
#include "unit_tests/Conversion_test.cpp"
#endif
