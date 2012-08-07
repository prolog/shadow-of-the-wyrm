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
    friend class SL_Engine_StringConstants;
    
    static std::map<std::string, std::string> string_table;
};
