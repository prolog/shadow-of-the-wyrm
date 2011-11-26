#include "Conversion.hpp"

using namespace std;

template<class T> T Convert::from_string(const string& convert)
{
  T converted_string;
  istringstream buffer(convert);
  buffer >> converted_string;
  return converted_string;
}

template<class T> string Convert::to_string(const T& convert)
{
  ostringstream buffer;
  buffer << convert;
  return buffer.str();
}

bool String::to_bool(const string& convert)
{
  if (convert == "1" || convert == "true")
  {
    return true;
  }

  return false;
}

int String::to_int(const string& convert)
{
  int converted_string = Convert::from_string<int>(convert);
  return converted_string;
}

float String::to_float(const string& convert)
{
  float converted_string = Convert::from_string<float>(convert);
  return converted_string;
}

string Integer::to_string(const int convert)
{
  string converted_int = Convert::to_string(convert);
  return converted_int;
}

#ifdef UNIT_TESTS
#include "unit_tests/Conversion_test.cpp"
#endif
