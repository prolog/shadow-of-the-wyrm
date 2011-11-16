#pragma once
#include <string>
#include <map>
#include "StringConstants.hpp"

class StringTable
{
  public:
    static void load(const std::string& filename);
    static std::string get(const std::string& key);

  protected:
    static std::map<std::string, std::string> string_table;
};
