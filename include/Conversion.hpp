#pragma once
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "common.hpp"
#include "Colours.hpp"
#include "EquipmentTypes.hpp"

// Forward declarations
namespace boost
{
  namespace uuids
  {
    struct uuid;
  }
}

class Convert
{
  protected:
    friend class String;
    friend class Integer;
    friend class Char;
    friend class Bool;

    Convert();
    template <class T> static T from_string(const std::string& str);
};

class String
{
  public:
    static std::string clean(const std::string& str);
    static std::vector<std::string> create_string_vector_from_csv_string(const std::string& csv_str);
    static std::map<std::string,std::string> create_properties_from_string(const std::string& properties_str);
    static std::map<std::string,std::string> create_properties_from_string_vector(const std::vector<std::string>& properties_v);
    static std::vector<Colour> create_colour_vector_from_csv_string(const std::string& csv_str);
    static std::vector<int> create_int_vector_from_csv_string(const std::string& csv_str);
    static std::string create_csv_from_string_vector(const std::vector<std::string>& str_vec);
    static void reset_and_pad(std::string& string_to_reset_and_pad, const uint num_cols);
    static std::string centre(const std::string& string_to_centre, const uint num_cols);
    static std::string right(const std::string& string_to_right_justify, const uint num_cols);
    static std::vector<std::string> tokenize(const std::string& string_to_tokenize, const std::string& delimiters, const bool include_tokens = false);

    static bool to_bool(const std::string& str);
    static int to_int(const std::string& str);
    static uint to_uint(const std::string& str);
    static float to_float(const std::string& str);
    static double to_double(const std::string& str);
    static Colour to_colour(const std::string& str, const Colour default_colour);
    static bool is_whitespace(const std::string& str);
    static std::string add_trailing_spaces(const std::string& str, const uint max_size);

  protected:
    String();
    ~String();
};

class File
{
  public:
    // Converts the contents of a text file to a string, newlines and all.
    static std::string to_string(const std::string& filename);

    // Converts the contents of a text file to a string, removing any newlines.
    static std::string to_resource_string(const std::string& filename);

  protected:
    File();
    ~File();

    static std::string update_text_format_specifiers(const std::string& unprocessed_res_str);
};

class Integer
{
  public:
    template <class T> inline static std::string to_string_key_at_given_position_in_rc_map(const std::map<std::string, T>& map, const int pos)
    {
      int cur = -1;
      std::string key;

      if (!map.empty())
      {
        typename std::map<std::string, T>::const_iterator map_it = map.begin();

        while (map_it != map.end() && cur <= pos)
        {
          auto second_val = map_it->second;

          if (second_val->get_user_playable())
          {
            cur++;
          }

          if (cur == pos)
          {
            key = map_it->first;
            break;
          }

          map_it++;
        }

      }

      return key;
    }

    template <class T> inline static std::string to_string_key_at_given_position_in_map(const std::map<std::string, T>& map, const int pos)
    {
      int cur = -1;
      std::string key;

      if (!map.empty())
      {
        typename std::map<std::string, T>::const_iterator map_it = map.begin();

        while (map_it != map.end() && cur <= pos)
        {
          auto second_val = map_it->second;
          cur++;

          if (cur == pos)
          {
            key = map_it->first;
            break;
          }

          map_it++;
        }

      }

      return key;
    }

  protected:
    Integer();
    ~Integer();
};

class Uuid
{
  public:
    static std::string to_string(const boost::uuids::uuid& uuid);

  protected:
    Uuid();
    ~Uuid();
};

class Bool
{
  public:
    static std::string to_string(const bool b);

  protected:
    Bool();
    ~Bool();
};

class Float
{
  public:
    static std::string to_string(const float f, const int precision = 6);

  protected:
    Float();
};

class Char
{
  public:
    static std::string to_string(const char c);
    static EquipmentWornLocation to_equipment_worn_location(const char character);
    static int keyboard_selection_char_to_int(const char character);

  protected:
    Char();
    ~Char();
};
