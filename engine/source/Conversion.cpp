#include "Conversion.hpp"

using namespace std;

Convert::Convert()
{
}

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

Char::Char()
{
}

string Char::to_string(const char character)
{
  string converted_string = Convert::to_string(character);
  return converted_string;
}

String::String()
{
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

string String::add_trailing_spaces(const string& str, const uint max_size)
{
  string result = str;

  size_t str_size = str.size();

  if (max_size > str_size)
  {
    size_t size_diff = max_size - str_size;

    for (uint i = 0; i < size_diff; i++)
    {
      result = result + " ";
    }
  }

  return result;
}

Integer::Integer()
{
}

string Integer::to_string(const int convert)
{
  string converted_int = Convert::to_string(convert);
  return converted_int;
}

#ifdef UNIT_TESTS
#include "unit_tests/Conversion_test.cpp"
#endif
