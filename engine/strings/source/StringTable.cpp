#include "StringTable.hpp"
#include <boost/tokenizer.hpp>
#include <iostream>
#include <fstream>

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

  return result;
}
