#include <ctype.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "CommandKeys.hpp"
#include "Conversion.hpp"
#include "Log.hpp"

using namespace std;

Convert::Convert()
{
}

template<class T> T Convert::from_string(const string& convert)
{
  T converted_string;
  istringstream buffer(convert);
  buffer >> converted_string;
  return converted_string;
}

template<class T> string Convert::to_string(const T& convert)
{
  ostringstream buffer;
  buffer << convert;
  return buffer.str();
}

// A cleaned string should have alphanumeric characters and spaces only - no backspace, no control characters, etc.
string String::clean(const string& to_clean)
{
  ostringstream clean;
  
  const char* c_str = to_clean.c_str();
  
  for (uint i = 0; i < to_clean.size(); i++)
  {
    char c = c_str[i];
    
    if (c > -1 && c < 255)
    {
      if (isalpha(c) || isdigit(c) || c >= ' ')
      {
        clean << Char::to_string(c);
      }
    }
    else
    {
      clean << '?';
    }
  }
  
  return clean.str();
}

vector<string> String::create_string_vector_from_csv_string(const string& csv_str)
{
  vector<string> str_vec;

  boost::split(str_vec, csv_str, boost::is_any_of(","));

  return str_vec;
}

string String::create_csv_from_string_vector(const vector<string>& str_vec)
{
  ostringstream ss;
  size_t str_vec_size = str_vec.size();
  for (uint i = 0; i < str_vec_size; i++)
  {
    ss << str_vec.at(i);

    if (i != (str_vec_size - 1))
    {
      ss << ",";
    }
  }

  return ss.str();
}

bool String::to_bool(const string& convert)
{
  if (convert == "1" || convert == "true")
  {
    return true;
  }

  return false;
}

Char::Char()
{
}

Char::~Char()
{
}

string Char::to_string(const char character)
{
  string converted_string = Convert::to_string(character);
  return converted_string;
}

EquipmentWornLocation Char::to_equipment_worn_location(const char character)
{
  int worn_location = -1; // EQUIPMENT_WORN_NONE
  
  if (character >= 'a' && character <= 'i')
  {
    worn_location = character - 'a';
  }
  else if (character >= 'A' && character <= 'I')
  {
    worn_location = character - 'A';
  }
  
  return static_cast<EquipmentWornLocation>(worn_location);
}

int Char::keyboard_selection_char_to_int(const char character)
{
  return static_cast<int>(character - 'a');
}

Bool::Bool()
{
}

Bool::~Bool()
{
}

string Bool::to_string(const bool b)
{
  string converted_string = Convert::to_string(b);
  return converted_string;
}

DirectionEnum::DirectionEnum()
{
}

DirectionEnum::~DirectionEnum()
{
}

string DirectionEnum::to_string(const Direction d)
{
  string command_key_direction;

  switch(d)
  {
    case Direction::DIRECTION_NULL:
      command_key_direction = CommandKeys::SEARCH;
      break;
    case Direction::DIRECTION_SOUTH_WEST:
      command_key_direction = CommandKeys::MOVE_SOUTHWEST;
      break;
    case Direction::DIRECTION_SOUTH:
      command_key_direction = CommandKeys::MOVE_SOUTH;
      break;
    case Direction::DIRECTION_SOUTH_EAST:
      command_key_direction = CommandKeys::MOVE_SOUTHEAST;
      break;
    case Direction::DIRECTION_WEST:
      command_key_direction = CommandKeys::MOVE_WEST;
      break;
    case Direction::DIRECTION_EAST:
      command_key_direction = CommandKeys::MOVE_EAST;
      break;
    case Direction::DIRECTION_NORTH_WEST:
      command_key_direction = CommandKeys::MOVE_NORTHWEST;
      break;
    case Direction::DIRECTION_NORTH:
      command_key_direction = CommandKeys::MOVE_NORTH;
      break;
    case Direction::DIRECTION_NORTH_EAST:
      command_key_direction = CommandKeys::MOVE_NORTHEAST;
      break;
    case Direction::DIRECTION_UP:
    case Direction::DIRECTION_DOWN:
    default:
      break;
  }

  return command_key_direction;
}

string DirectionEnum::to_attack_string(const Direction d)
{
  string command_key_direction;

  switch(d)
  {
    case Direction::DIRECTION_NULL:
      command_key_direction = CommandKeys::SEARCH;
      break;
    case Direction::DIRECTION_SOUTH_WEST:
      command_key_direction = CommandKeys::ATTACK_SOUTHWEST;
      break;
    case Direction::DIRECTION_SOUTH:
      command_key_direction = CommandKeys::ATTACK_SOUTH;
      break;
    case Direction::DIRECTION_SOUTH_EAST:
      command_key_direction = CommandKeys::ATTACK_SOUTHEAST;
      break;
    case Direction::DIRECTION_WEST:
      command_key_direction = CommandKeys::ATTACK_WEST;
      break;
    case Direction::DIRECTION_EAST:
      command_key_direction = CommandKeys::ATTACK_EAST;
      break;
    case Direction::DIRECTION_NORTH_WEST:
      command_key_direction = CommandKeys::ATTACK_NORTHWEST;
      break;
    case Direction::DIRECTION_NORTH:
      command_key_direction = CommandKeys::ATTACK_NORTH;
      break;
    case Direction::DIRECTION_NORTH_EAST:
      command_key_direction = CommandKeys::ATTACK_NORTHEAST;
      break;
    case Direction::DIRECTION_UP:
    case Direction::DIRECTION_DOWN:
    default:
      break;
  }

  return command_key_direction;  
}

String::String()
{
}

String::~String()
{
}

int String::to_int(const string& convert)
{
  int converted_string = Convert::from_string<int>(convert);
  return converted_string;
}

float String::to_float(const string& convert)
{
  float converted_string = Convert::from_string<float>(convert);
  return converted_string;
}

double String::to_double(const string& convert)
{
  double converted_string = Convert::from_string<double>(convert);
  return converted_string;
}

string String::add_trailing_spaces(const string& str, const uint max_size)
{
  string result = str;

  size_t str_size = str.size();

  if (max_size > str_size)
  {
    size_t size_diff = max_size - str_size;

    for (uint i = 0; i < size_diff; i++)
    {
      result = result + " ";
    }
  }

  return result;
}

void String::reset_and_pad(string& s, const uint num_cols)
{
  s = "";
  s = String::add_trailing_spaces(s, num_cols);
}

// Centre the string on the number of columns stored on the object instance
string String::centre(const std::string& justify_str, const uint num_cols)
{
  ostringstream ss;
  
  for (uint i = 0; i < (num_cols/2) - (justify_str.size()/2); i++)
  {
    ss << " ";
  }
  
  ss << justify_str;
  
  return ss.str();
}

// Right-justify the string using the number of columns stored on the object instance to add left padding.
string String::right(const std::string& justify_str, const uint num_cols)
{
  ostringstream ss;
  
  for (uint i = 0; i < (num_cols - justify_str.size()); i++)
  {
    ss << " "; 
  }
  
  ss << justify_str;
  
  return ss.str();
}

// Check to see if the string consists entirely of whitespace characters.
bool String::is_whitespace(const std::string& str)
{
  bool is_space = true;

  size_t str_size = str.size();
  for (uint i = 0; i < str_size; i++)
  {
    if (!isspace(str.at(i)))
    {
      is_space = false;
      break;
    }
  }

  return is_space;
}

File::File()
{
}

File::~File()
{
}

string File::to_string(const string& filename)
{
  try
  {
    ifstream t(filename);
    string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

    return str;
  }
  catch (...)
  {
    Log::instance().error("Could not write contents of file to str: " + filename);
  }

  return "";
}

string File::to_resource_string(const string& filename)
{
  string str = to_string(filename);
  str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

  return str;
}

Integer::Integer()
{
}

Integer::~Integer()
{
}

string Integer::to_string(const uint convert_uint)
{
  string converted_int = Convert::to_string(convert_uint);
  return converted_int;  
}

string Integer::to_string(const int convert)
{
  string converted_int = Convert::to_string(convert);
  return converted_int;
}

// Boost uuid
Uuid::Uuid()
{
}

Uuid::~Uuid()
{
}

string Uuid::to_string(const boost::uuids::uuid& convert)
{
  string converted_uuid = boost::lexical_cast<string>(convert);
  return converted_uuid;
}

double ActionCostConverter::to_seconds(const ActionCostValue action_cost_value, const MapType map_type)
{
  double seconds = 0.0;
  
  if (map_type == MapType::MAP_TYPE_WORLD)
  {
    seconds = ActionCostConverter::to_seconds_on_world_map(action_cost_value);
  }
  else
  {
    seconds = ActionCostConverter::to_seconds_on_submap(action_cost_value);
  }
  
  return seconds;
}

// Each action on the world map takes the action cost in minutes, times 1.5.  So moving at a base speed
// of 50 would take 75 minutes.
double ActionCostConverter::to_seconds_on_world_map(const ActionCostValue action_cost_value)
{
  return (action_cost_value * 60 * 1.5);
}

// Each action on a submap takes half the amount of action cost in seconds.  So moving at a base,
// default speed of 50ish would take about 25 seconds.
double ActionCostConverter::to_seconds_on_submap(const ActionCostValue action_cost_value)
{
  return (action_cost_value / 2);
}

// Convert raw hunger values to general levels
const int HungerLevelConverter::INT_HUNGER_LEVEL_STUFFED = 10000;
const int HungerLevelConverter::INT_HUNGER_LEVEL_FULL = 7500;
const int HungerLevelConverter::INT_HUNGER_LEVEL_NORMAL = 4000;
const int HungerLevelConverter::INT_HUNGER_LEVEL_HUNGRY = 2000;
const int HungerLevelConverter::INT_HUNGER_LEVEL_STARVING = 1000;
const int HungerLevelConverter::INT_HUNGER_LEVEL_DYING = 0;

HungerLevelConverter::HungerLevelConverter()
{
}

HungerLevelConverter::~HungerLevelConverter()
{
}

HungerLevel HungerLevelConverter::to_hunger_level(const int hunger)
{
  HungerLevel hunger_level = HungerLevel::HUNGER_LEVEL_NORMAL;

  if (hunger > INT_HUNGER_LEVEL_FULL)
  {
    hunger_level = HungerLevel::HUNGER_LEVEL_STUFFED;
  }
  else if (hunger <= INT_HUNGER_LEVEL_FULL && hunger > INT_HUNGER_LEVEL_NORMAL)
  {
    hunger_level = HungerLevel::HUNGER_LEVEL_FULL;
  }
  else if (hunger <= INT_HUNGER_LEVEL_HUNGRY && hunger > INT_HUNGER_LEVEL_STARVING)
  {
    hunger_level = HungerLevel::HUNGER_LEVEL_HUNGRY;
  }
  else if (hunger <= INT_HUNGER_LEVEL_STARVING && hunger > INT_HUNGER_LEVEL_DYING)
  {
    hunger_level = HungerLevel::HUNGER_LEVEL_STARVING;
  }
  else if (hunger <= INT_HUNGER_LEVEL_DYING)
  {
    hunger_level = HungerLevel::HUNGER_LEVEL_DYING;
  }

  return hunger_level;
}

// Alcohol conversion routines!  The sign that my roguelike has gone off
// the rails.
//
// Using the Canadian/US standard drink of 13.6g/std_drink
const float AlcoholConverter::GRAMS_PER_STANDARD_DRINK = 13.6f;

AlcoholConverter::AlcoholConverter()
{
}

AlcoholConverter::~AlcoholConverter()
{
}

float AlcoholConverter::standard_drinks_to_absorbable_grams(const float std_drinks)
{
  float grams = standard_drinks_to_grams(std_drinks);

  // A standard drink should produce about 2g of absorbable alcohol.
  float absorbable_grams = grams * 0.14706f;
  return absorbable_grams;
}

float AlcoholConverter::standard_drinks_to_grams(const float std_drinks)
{
  return std_drinks * GRAMS_PER_STANDARD_DRINK;
}

#ifdef UNIT_TESTS
#include "unit_tests/Conversion_test.cpp"
#endif
