#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include "Conversion.hpp"
#include "CreatureGenerationOptions.hpp"

using namespace std;
using namespace boost;

void CreatureGenerationOptions::set_id(const string& new_id)
{
  id = new_id;
}

string CreatureGenerationOptions::get_id() const
{
  return id;
}

void CreatureGenerationOptions::set_hostility(const string& creature_id, const bool val)
{
  hostility[creature_id] = val;
}

void CreatureGenerationOptions::set_hostility(const map<string, bool>& new_hostility)
{
  hostility = new_hostility;
}

map<string, bool> CreatureGenerationOptions::get_hostility_map() const
{
  return hostility;
}

bool CreatureGenerationOptions::get_hostility(const string& creature_id) const
{
  map<string, bool>::const_iterator h_it = hostility.find(creature_id);

  if (h_it != hostility.end())
  {
    return h_it->second;
  }

  return false;
}

bool CreatureGenerationOptions::parse(const string& parse_string)
{
  try
  {
    vector<pair<string, string>> options;

    // If the string doesn't contain "=" or ",", assume it's an ID.
    if (parse_string.find("=") == string::npos && parse_string.find(";") == string::npos)
    {
      id = parse_string;
      trim(id);
    }
    else
    {
      boost::char_separator<char> sep(";");
      boost::tokenizer<boost::char_separator<char>> tokens(parse_string, sep);

      for (const string& token : tokens)
      {
        if (token.find("=") == string::npos)
        {
          string val = token;
          trim(val);

          options.push_back(make_pair("id", val));
        }
        else
        {
          vector<string> key_value;
          boost::split(key_value, token, boost::is_any_of("="));

          if (key_value.size() > 1)
          {
            string key = key_value[0];
            string value = key_value[1];

            trim(key);
            trim(value);

            options.push_back(make_pair(key, value));
          }
        }
      }
    }
    
    process_options(options);

    return true;
  }
  catch (...)
  {
    return false;
  }
}

void CreatureGenerationOptions::process_options(const vector<pair<string, string>>& options)
{
  string key, value;

  for (const pair<string, string>& option : options)
  {
    key = option.first;
    value = option.second;

    if (key == "id")
    {
      set_id(value);
    }
    else if (key == "hostility")
    {
      parse_hostility(value);
    }
  }
}

bool CreatureGenerationOptions::parse_hostility(const string& parse_string)
{
  vector<string> creature_hostility;

  if (parse_string.find(":") != string::npos)
  {
    boost::split(creature_hostility, parse_string, boost::is_any_of(":"));

    if (creature_hostility.size() > 1)
    {
      string creature_id = creature_hostility.at(0);
      string host_s = creature_hostility.at(1);

      trim(creature_id);
      trim(host_s);

      set_hostility(creature_id, String::to_bool(host_s));
    }

    return true;
  }
  else
  {
    return false;
  }
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureGenerationOptions_test.cpp"
#endif
