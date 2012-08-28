#pragma once
#include <map>
#include <sstream>
#include <string>
#include "ActionCost.hpp"
#include "common.hpp"
#include "Directions.hpp"
#include "EquipmentTypes.hpp"
#include "MapTypes.hpp"

// Forward declarations
namespace boost
{
  namespace uuids
  {
    class uuid;
  }
}

class Convert
{

  protected:
    friend class String;
    friend class Integer;
    friend class Char;

    Convert();
    template <class T> static T from_string(const std::string& str);
    template <class T> static std::string to_string(const T& convert);
};

class Char
{
  public:
    static std::string to_string(const char character);
    static EquipmentWornLocation to_equipment_worn_location(const char character);

  protected:
    Char();
    ~Char();
};

class DirectionEnum
{
  public:
    static std::string to_string(const Direction d);
    static std::string to_attack_string(const Direction d);

  protected:
    DirectionEnum();
    ~DirectionEnum();
};

class String
{
  public:
    static std::string clean(const std::string& str);
    static void reset_and_pad(std::string& string_to_reset_and_pad, const uint num_cols);
    static std::string centre(const std::string& string_to_centre, const uint num_cols);
    static std::string right (const std::string& string_to_right_justify, const uint num_cols);

    static bool to_bool(const std::string& str);
    static int to_int(const std::string& str);
    static float to_float(const std::string& str);
    static std::string add_trailing_spaces(const std::string& str, const uint max_size);

  protected:
    String();
    ~String();
};

class Integer
{
  public:
    static std::string to_string(const uint integer);
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

class ActionCostConverter
{
  public:
    static double to_seconds(const ActionCostValue action_cost_value, const MapType map_type);
    static double to_seconds_on_world_map(const ActionCostValue action_cost_value);
    static double to_seconds_on_submap(const ActionCostValue action_cost_value);
  protected:
    ActionCostConverter();
    ~ActionCostConverter();
};
