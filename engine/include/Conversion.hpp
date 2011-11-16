#pragma once
#include <sstream>
#include <string>

class String
{
  public:
    static bool to_bool(const std::string& str);
    static int to_int(const std::string& str);
    static float to_float(const std::string& str);
};

class Integer
{
  public:
    static std::string to_string(const int integer);
};

