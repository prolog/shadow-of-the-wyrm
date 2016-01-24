#pragma once
#include <string>
#include <boost/algorithm/string.hpp>
#include <unordered_map>

using StringTableMap = std::unordered_map<std::string, std::string>;

class StringTable
{
  public:
    static void load(const std::string& filename);
    static std::string get(const std::string& key);

  protected:
    friend class SW_Engine_StringConstants;
    friend class SW_Engine_Strings_StringTable;

    static bool is_external_file(const std::string& value);
    static std::string parse_file_name(const std::string& file_ref_value);
    
    static StringTableMap string_table;
};

using StringRange = const boost::iterator_range<std::string::const_iterator>;