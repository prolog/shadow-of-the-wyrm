#pragma once
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/unordered_map.hpp>

typedef boost::unordered_map<std::string, std::string> StringTableMap;

class StringTable
{
  public:
    static void load(const std::string& filename);
    static std::string get(const std::string& key);

  protected:
    friend class SL_Engine_StringConstants;
    
    static StringTableMap string_table;
};

typedef const boost::iterator_range<std::string::const_iterator> StringRange;