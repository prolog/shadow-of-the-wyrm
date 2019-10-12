#include <ctype.h>
#include <iomanip>
#include <iterator>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Conversion.hpp"
#include "CoordUtils.hpp"
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

map<string, string> String::create_properties_from_string(const string& properties_str)
{
  vector<string> properties_v;
  properties_v = create_string_vector_from_csv_string(properties_str);
  return create_properties_from_string_vector(properties_v);
}

map<string, string> String::create_properties_from_string_vector(const vector<string>& properties_v)
{
  map<string, string> properties;

  for (const string& prop_str : properties_v)
  {
    vector<string> p;
    boost::split(p, prop_str, boost::is_any_of("="));

    if (p.size() == 2)
    {
      properties[p[0]] = p[1];
    }
  }

  return properties;
}

vector<int> String::create_int_vector_from_csv_string(const string& csv_str)
{
  vector<string> str_vec;
  vector<int> ints;

  boost::split(str_vec, csv_str, boost::is_any_of(","));

  for (const string& s : str_vec)
  {
    if (!s.empty())
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
    if (!s.empty())
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

string String::create_string_from_coordinate(const Coordinate& c)
{
  ostringstream ss;

  ss << c.first << "," << c.second;

  return ss.str();
}

Coordinate String::create_coordinate_from_string(const std::string& coord_s)
{
  Coordinate c = CoordUtils::end();
  vector<string> parts = tokenize(coord_s, ", ", false);

  if (parts.size() >= 2)
  {
    c.first = String::to_int(parts[0]);
    c.second = String::to_int(parts[1]);
  }

  return c;
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
  return static_cast<int>(std::tolower(character) - 'a');
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

  for (uint i = 0; i < (num_cols / 2) - (justify_str.size() / 2); i++)
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

#ifdef UNIT_TESTS
#include "unit_tests/Conversion_test.cpp"
#endif