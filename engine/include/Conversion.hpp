#pragma once
#include <map>
#include <sstream>
#include <string>
#include "common.hpp"

class Convert
{
  public:
    friend class String;
    friend class Integer;

  protected:
    Convert();
    template <class T> static T from_string(const std::string& str);
    template <class T> static std::string to_string(const T& convert);
};

class String
{
  public:
    static bool to_bool(const std::string& str);
    static int to_int(const std::string& str);
    static float to_float(const std::string& str);
    static std::string add_trailing_spaces(const std::string& str, const uint max_size);
  protected:
    String();
};

class Integer
{
  public:
    static std::string to_string(const int integer);
    template <class T> inline static std::string to_string_key_at_given_position_in_map(const std::map<std::string, T>& map, const int pos)
    {
      int cur = 0;
      std::string key;

      if (!map.empty())
      {
        typename std::map<std::string, T>::const_iterator map_it = map.begin();

        while (map_it != map.end() && cur <= pos)
        {
          if (cur == pos)
          {
            key = map_it->first;
            break;
          }

          map_it++;
          cur++;
        }

      }

      return key;
    }

  protected:
    Integer();
};

