#include <ctype.h>
#include <iomanip>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "CarryingCapacityCalculator.hpp"
#include "CommandKeys.hpp"
#include "Conversion.hpp"
#include "Log.hpp"
#include "TextFormatSpecifiers.hpp"

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

string Float::to_string(const float f, const int precision)
{
  std::ostringstream ss;
  ss << std::setprecision(precision) << f;
  return ss.str();
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
        clean << c;
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

vector<int> String::create_int_vector_from_csv_string(const string& csv_str)
{
  vector<string> str_vec;
  vector<int> ints;

  boost::split(str_vec, csv_str, boost::is_any_of(","));

  for (const string& s : str_vec)
  {
    try
    {
      ints.push_back(std::stoi(s));
    }
    catch (...)
    {
      continue;
    }
  }

  return ints;
}

vector<Colour> String::create_colour_vector_from_csv_string(const string& csv_str)
{
  vector<string> str_vec;
  vector<Colour> colours;

  boost::split(str_vec, csv_str, boost::is_any_of(","));

  for (const string& s : str_vec)
  {
    try
    {
      colours.push_back(static_cast<Colour>(std::stoi(s)));
    }
    catch (...)
    {
      // Might not be a number - that's fine.  Ignore and try the next.
      continue;
    }
  }

  return colours;
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

Colour String::to_colour(const string& str_colour, const Colour default_colour)
{
  Colour c = default_colour;

  if (!str_colour.empty())
  {
    c = static_cast<Colour>(String::to_int(str_colour));
  }

  return c;
}

vector<string> String::tokenize(const string& tok_str, const string& delim, const bool include_delims)
{
  vector<string> output;
  
  string drop_delim = delim;
  string keep_delim;
  boost::empty_token_policy token_policy = boost::drop_empty_tokens;

  if (include_delims)
  {
    drop_delim = "";
    keep_delim = delim;
    token_policy = boost::keep_empty_tokens;
  }

  boost::char_separator<char> separator(drop_delim.c_str(), keep_delim.c_str(), token_policy);
  boost::tokenizer<boost::char_separator<char>> tokens(tok_str, separator);

  for (const auto& t : tokens) {
    output.push_back(t);
  }

  return output;
}

Bool::Bool()
{
}

Bool::~Bool()
{
}

string Bool::to_string(const bool b)
{
  ostringstream ss;
  ss << b;
  return ss.str();
}

Char::Char()
{
}

Char::~Char()
{
}

string Char::to_string(const char c)
{
  ostringstream ss;
  ss << c;
  return ss.str();
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

HandednessEnum::HandednessEnum()
{
}

HandednessEnum::~HandednessEnum()
{
}

RotationDirection HandednessEnum::to_rotation_direction(const Handedness h)
{
  RotationDirection rd = RotationDirection::ROTATION_DIRECTION_NULL;

  switch (h)
  {
    case Handedness::LEFT_HANDED:
      rd = RotationDirection::ROTATION_DIRECTION_CLOCKWISE;
      break;
    case Handedness::RIGHT_HANDED:
    default:
      rd = RotationDirection::ROTATION_DIRECTION_COUNTERCLOCKWISE;
      break;
  }

  return rd;
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

uint String::to_uint(const string& convert)
{
  uint converted_string = Convert::from_string<uint>(convert);
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
  boost::replace_all(str, "\n", " ");
  str = update_text_format_specifiers(str);

  return str;
}

// Update the resource string so any occurrence of a text format specifier
// within the string is always followed by a space.  This ensures that the
// tokenization functions used for resource strings works properly.
string File::update_text_format_specifiers(const string& unproc_res_str)
{
  string proc_res_str = unproc_res_str;

  vector<string> text_format_specifiers = { TextFormatSpecifiers::LINE_BREAK, TextFormatSpecifiers::NEW_PARAGRAPH, TextFormatSpecifiers::NEW_PAGE };

  for (const string& specifier : text_format_specifiers)
  {
    // Add a space at the end so that the resource string tokenizer will work
    // properly.
    boost::replace_all(proc_res_str, specifier, specifier + " ");
  }

  return proc_res_str;
}

Integer::Integer()
{
}

Integer::~Integer()
{
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

BurdenLevelConverter::BurdenLevelConverter()
{
}

BurdenLevelConverter::~BurdenLevelConverter()
{
}

BurdenLevel BurdenLevelConverter::to_burden_level(CreaturePtr c)
{
  BurdenLevel bl = BurdenLevel::BURDEN_LEVEL_UNBURDENED;

  if (c != nullptr)
  {
    CarryingCapacityCalculator ccc;
    uint weight_carried = c->get_weight_carried();

    if (weight_carried >= ccc.calculate_overburdened_weight(c))
    {
      bl = BurdenLevel::BURDEN_LEVEL_OVERBURDENED;
    }
    else if (weight_carried >= ccc.calculate_strained_weight(c))
    {
      bl = BurdenLevel::BURDEN_LEVEL_STRAINED;
    }
    else if (weight_carried >= ccc.calculate_burdened_weight(c))
    {
      bl = BurdenLevel::BURDEN_LEVEL_BURDENED;
    }
  }

  return bl;
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

// Tile and Map Type Conversions
MapTileTypes::MapTileTypes()
{
}

MapTileTypes::~MapTileTypes()
{
}

TileType MapTileTypes::map_type_to_default_tile_type(const MapType mt)
{
  static_assert(MapType::MAP_TYPE_LAST_INC == MapType(3), "Unrecognized MAP_TYPE_LAST_INC");
  TileType tt = TileType::TILE_TYPE_UNDEFINED;

  switch (mt)
  {
    case MapType::MAP_TYPE_WORLD:
    case MapType::MAP_TYPE_OVERWORLD:
      tt = TileType::TILE_TYPE_FIELD;
      break;
    case MapType::MAP_TYPE_UNDERWORLD:
      tt = TileType::TILE_TYPE_DUNGEON;
      break;
    case MapType::MAP_TYPE_UNDERWATER:
      tt = TileType::TILE_TYPE_SEA;
    default:
      break;
  }

  return tt;
}

#ifdef UNIT_TESTS
#include "unit_tests/Conversion_test.cpp"
#endif
