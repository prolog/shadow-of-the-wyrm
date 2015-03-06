#include "StringTable.hpp"
#include <boost/tokenizer.hpp>
#include <iostream>
#include <fstream>
#include "Conversion.hpp"

using namespace std;
using namespace boost;

std::unordered_map<string, string> StringTable::string_table;

void StringTable::load(const string& filename)
{
  ifstream string_file(filename.c_str());
  string current_line;
  string key;
  string value;
  char_separator<char> separator("=");

  if (string_file.is_open())
  {
    // Reset the string table
    string_table.clear();

    // Read strings into the table
    while (string_file.good())
    {
      getline(string_file, current_line);

      string::size_type pos;
      pos = current_line.find('=', 0);
      string key, value;
      
      if (pos != string::npos)
      {
        key = current_line.substr(0, pos);
        value = current_line.substr(pos + 1);
      }

      if (!key.empty())
      {
        string_table.insert(make_pair(key, value));
      }
    }
  }
}

// Return a string from the table, returning an empty string if the
// key couldn't be found.
string StringTable::get(const string& key)
{
  string result = "";
  std::unordered_map<string, string>::iterator table_it = string_table.find(key);

  if (table_it != string_table.end())
  {
    result = table_it->second;
  }

  if (is_external_file(result))
  {
    result = File::to_resource_string(parse_file_name(result));
  }

  return result;
}

// Check to see if the result is a file, which it will be if its first
// two characters are '[' and last two are ']' (after trimming).
// This differentiates a file reference from an in-game prompt.
bool StringTable::is_external_file(const string& value)
{
  bool is_file = false;

  string val_trim = value;
  trim(val_trim);
  size_t val_trim_size = val_trim.size();

  if (val_trim_size >= 4)
  {
    char first_char = val_trim.at(0);
    char last_char = val_trim.at(val_trim_size - 1);

    if (val_trim.at(0) == '[' && 
        val_trim.at(1) == '[' &&
        val_trim.at(val_trim_size-1) == ']' &&
        val_trim.at(val_trim_size-2) == ']')
    {
      is_file = true;
    }
  }

  return is_file;
}

// Parse the file name out of a file reference.
string StringTable::parse_file_name(const string& file_ref_value)
{
  string file_name = file_ref_value;
  size_t file_ref_val_size = file_ref_value.size();

  if (is_external_file(file_ref_value))
  {
    if (file_ref_val_size > 4)
    {
      // Parse off the '[' and ']'.
      file_name = file_ref_value.substr(2, file_ref_val_size - 4);
    }
  }

  return file_name;
}

#ifdef UNIT_TESTS
#include "unit_tests/StringTable_test.cpp"
#endif