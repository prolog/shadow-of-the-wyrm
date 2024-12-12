#include <boost/scoped_array.hpp>
#include "Serialize.hpp"
#include "Log.hpp"

using namespace std;

const string Serialize::BINARY_PROPERTY_PREFIX = "__BIN__";

// Write the class identifier.  This is used by factory classes to determine which type of object to 
// default construct.
void Serialize::write_class_id(ostream& stream, const ClassIdentifier val)
{
  if (stream.good())
  {
    stream.write(reinterpret_cast<const char*>(&val), sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not write class id");
    throw stream_error;
  }
}

// Read the class identifier.
void Serialize::read_class_id(istream& stream, ClassIdentifier& val)
{
  if (stream.good())
  {
    stream.read((char*)&val, sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not read class_id");
    throw stream_error;
  }

  if (stream.fail())
  {
    SerializationException stream_error("Could not read full class_id");
    throw stream_error;
  }
}

// Write a size_t, usually used to capture stl container size.
void Serialize::write_size_t(ostream& stream, const size_t val)
{
  if (stream.good())
  {
    stream.write(reinterpret_cast<const char*>(&val), sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not write size_t");
    throw stream_error;
  }
}

// Read a size_t
void Serialize::read_size_t(istream& stream, size_t& val)
{
  if (stream.good())
  {
    stream.read((char*)&val, sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not read size_t");
    throw stream_error;
  }

  if (stream.fail())
  {
    SerializationException stream_error("Could not read full class_id");
    throw stream_error;
  }
}

// Write a boolean value
void Serialize::write_bool(ostream& stream, const bool val)
{
  if (stream.good())
  {
    stream.write(reinterpret_cast<const char*>(&val), sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not write boolean");
    throw stream_error;
  }
}

// Read a boolean value
void Serialize::read_bool(istream& stream, bool& val)
{
  if (stream.good())
  {
    stream.read((char*)&val, sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not read bool");
    throw stream_error;
  }

  if (stream.fail())
  {
    SerializationException stream_error("Could not read full bool");
    throw stream_error;
  }
}

// Write an unsigned char value
void Serialize::write_uchar(ostream& stream, const unsigned char val)
{
  if (stream.good())
  {
    stream.write(reinterpret_cast<const char*>(&val), sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not write unsigned char");
    throw stream_error;
  }
}

// Read an unsigned char value
void Serialize::read_uchar(istream& stream, unsigned char& val)
{
  if (stream.good())
  {
    stream.read((char*)&val, sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not read unsigned char");
    throw stream_error;
  }

  if (stream.fail())
  {
    SerializationException stream_error("Could not read full unsigned char");
    throw stream_error;
  }
}

// Write an unsigned int value.
void Serialize::write_uint(ostream& stream, const unsigned int val)
{
  if (stream.good())
  {
    stream.write(reinterpret_cast<const char*>(&val), sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not write unsigned int");
    throw stream_error;
  }
}

// Read an unsigned int value.
void Serialize::read_uint(istream& stream, unsigned int& val)
{
  if (stream.good())
  {
    stream.read((char*)&val, sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not read unsigned int");
    throw stream_error;
  }

  if (stream.fail())
  {
    SerializationException stream_error("Could not read full unsigned int");
    throw stream_error;
  }
}

// Write a (signed) int value.
void Serialize::write_int(ostream& stream, const signed int val)
{
  if (stream.good())
  {
    stream.write(reinterpret_cast<const char*>(&val), sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not write signed int");
    throw stream_error;
  }
}

// Read a (signed) int value.
void Serialize::read_int(istream& stream, signed int& val)
{
  if (stream.good())
  {
    stream.read((char*)&val, sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not read signed int");
    throw stream_error;
  }

  if (stream.fail())
  {
    SerializationException stream_error("Could not read full signed int");
    throw stream_error;
  }
}

// Write an unsigned long
void Serialize::write_ulong(ostream& stream, const unsigned long val)
{
  if (stream.good())
  {
    stream.write(reinterpret_cast<const char*>(&val), sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not write ulong");
    throw stream_error;
  }
}

// Read an unsigned long.
void Serialize::read_ulong(istream& stream, unsigned long& val)
{
  if (stream.good())
  {
    stream.read((char*)&val, sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not read unsigned long");
    throw stream_error;
  }

  if (stream.fail())
  {
    SerializationException stream_error("Could not read full unsigned long");
    throw stream_error;
  }
}

// Write a long long
void Serialize::write_longlong(ostream& stream, const long long val)
{
  if (stream.good())
  {
    stream.write(reinterpret_cast<const char*>(&val), sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not write ulonglong");
    throw stream_error;
  }
}

// Read a long long
void Serialize::read_longlong(istream& stream, long long& val)
{
  if (stream.good())
  {
    stream.read((char*)&val, sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not read long long");
    throw stream_error;
  }

  if (stream.fail())
  {
    SerializationException stream_error("Could not read full long long");
    throw stream_error;
  }
}

// Write an unsigned long long
void Serialize::write_ulonglong(ostream& stream, const unsigned long long val)
{
  if (stream.good())
  {
    stream.write(reinterpret_cast<const char*>(&val), sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not write ulonglong");
    throw stream_error;
  }
}

// Read an unsigned long long
void Serialize::read_ulonglong(istream& stream, unsigned long long& val)
{
  if (stream.good())
  {
    stream.read((char*)&val, sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not read unsigned long long");
    throw stream_error;
  }

  if (stream.fail())
  {
    SerializationException stream_error("Could not read full unsigned long long");
    throw stream_error;
  }
}

// Write/read floating point values.
void Serialize::write_float(ostream& stream, const float val)
{
  if (stream.good())
  {
    stream.write(reinterpret_cast<const char*>(&val), sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not write double");
    throw stream_error;
  }
}

void Serialize::read_float(istream& stream, float& val)
{
  if (stream.good())
  {
    stream.read((char*)&val, sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not read float");
    throw stream_error;
  }

  if (stream.fail())
  {
    SerializationException stream_error("Could not read float");
    throw stream_error;
  }
}


// Write a double value.
void Serialize::write_double(ostream& stream, const double val)
{
  if (stream.good())
  {
    stream.write(reinterpret_cast<const char*>(&val), sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not write double");
    throw stream_error;
  }
}

// Read a double value.
void Serialize::read_double(istream& stream, double& val)
{
  if (stream.good())
  {
    stream.read((char*)&val, sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not read double");
    throw stream_error;
  }

  if (stream.fail())
  {
    SerializationException stream_error("Could not read double");
    throw stream_error;
  }
}

// Write a std::string
void Serialize::write_string(ostream& stream, const string& val, const bool binary_str)
{
  if (stream.good())
  {
    size_t val_size = val.size();
    Serialize::write_size_t(stream, val_size);
    Serialize::write_bool(stream, binary_str);

    const char* val_cstr = val.c_str();
    stream.write(val_cstr, val_size);
  }
  else
  {
    SerializationException stream_error("Could not write std::string");
    throw stream_error;
  }
}

// Read a std::string
void Serialize::read_string(istream& stream, string& val)
{
  if (stream.good())
  {
    size_t string_size = 0;
    bool binary_str = false;

    Serialize::read_size_t(stream, string_size);
    Serialize::read_bool(stream, binary_str);
    size_t stream_size = string_size;

    if (binary_str == false)
    {
      string_size++;
    }

    boost::scoped_array<char> raw_str(new char[string_size]);
    stream.read(raw_str.get(), stream_size);

    if (binary_str == false)
    {
      raw_str.get()[string_size-1] = '\0';
    }

    // Now that we have the actual string, create a copy and assign it to the passed-in
    // reference.  The scoped pointer should take care of deletion afterwards.
    val = string(raw_str.get(), stream_size);
  }
  else
  {
    SerializationException stream_error("Could not read std::string");
    throw stream_error;
  }

  if (stream.fail())
  {
    SerializationException stream_error("Could not read full std::string");
    throw stream_error;
  }
}

// Read a string and return nothing.  Useful for when something has been saved,
// but isn't explicitly needed at a certain point. (e.g., metadata when doing
// the actual read of the game data.)
void Serialize::consume_string(istream& stream)
{
  string ignore_val;
  Serialize::read_string(stream, ignore_val);
}

void Serialize::write_string_vector(ostream& stream, const vector<string>& val)
{
  size_t size = val.size();
  Serialize::write_size_t(stream, size);

  if (size > 0)
  {
    for (const string& str_val : val)
    {
      Serialize::write_string(stream, str_val);
    }
  }
}

void Serialize::read_string_vector(istream& stream, vector<string>& val)
{
 {
   size_t size = 0;
   Serialize::read_size_t(stream, size);

   val.clear();
   val.reserve(size);
 
   for(size_t v_size = 0; v_size < size; v_size++)
   {
      string str_val;
      Serialize::read_string(stream, str_val);

      val.push_back(str_val);
   }
 }
}

void Serialize::write_string_map(ostream& stream, const map<string, string>& val)
{
  size_t size = val.size();
  Serialize::write_size_t(stream, size);

  if (size > 0)
  {
    for (map<string, string>::const_iterator v_it = val.begin(); v_it != val.end(); v_it++)
    {
      string key = v_it->first;
      string value = v_it->second;

      Serialize::write_string(stream, key);

      bool binary_str = (key.rfind(BINARY_PROPERTY_PREFIX, 0) == 0);

      Serialize::write_string(stream, value, binary_str);
    }
  }
}

void Serialize::read_string_map(std::istream& stream, map<string, string>& val)
{
  size_t size = 0;
  Serialize::read_size_t(stream, size);

  val.clear();

  for (size_t i = 0; i < size; i++)
  {
    string key;
    string value;

    Serialize::read_string(stream, key);
    Serialize::read_string(stream, value);

    val.insert(make_pair(key, value));
  }
}

void Serialize::write_string_set(ostream& stream, const set<string>& val)
{
  Serialize::write_size_t(stream, val.size());

  for (const string& str : val)
  {
    Serialize::write_string(stream, str);
  }
}

void Serialize::read_string_set(istream& stream, set<string>& val)
{
  size_t set_size = 0;
  Serialize::read_size_t(stream, set_size);

  val.clear();

  for (size_t i = 0; i < set_size; i++)
  {
    string str;
    Serialize::read_string(stream, str);

    val.insert(str);
  }
}

void Serialize::write_colour_vector(ostream& stream, const vector<Colour>& val)
{
  Serialize::write_size_t(stream, val.size());

  for (const Colour c : val)
  {
    Serialize::write_enum(stream, c);
  }
}

void Serialize::read_colour_vector(istream& stream, vector<Colour>& val)
{
  size_t num_colours = 0;
  Serialize::read_size_t(stream, num_colours);

  for (size_t i = 0; i < num_colours; i++)
  {
    Colour c = Colour::COLOUR_BLACK;
    Serialize::read_enum(stream, c);

    val.push_back(c);
  }
}

void Serialize::write_event_scripts(ostream& stream, const EventScriptsMap& event_scripts)
{
  size_t es_size = event_scripts.size();
  Serialize::write_size_t(stream, es_size);
  for (const auto& es_pair : event_scripts)
  {
    Serialize::write_string(stream, es_pair.first);
    es_pair.second.serialize(stream);
  }
}

void Serialize::read_event_scripts(istream& stream, EventScriptsMap& event_scripts)
{
  size_t es_size = 0;
  Serialize::read_size_t(stream, es_size);

  for (size_t i = 0; i < es_size; i++)
  {
    string event_name;
    ScriptDetails sd;

    Serialize::read_string(stream, event_name);
    sd.deserialize(stream);

    event_scripts.insert(make_pair(event_name, sd));
  }
}

#ifdef ENABLE_SDL
void Serialize::write_uint8(ostream& stream, const Uint8 val)
{
  if (stream.good())
  {
    stream.write(reinterpret_cast<const char*>(&val), sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not write Uint8");
    throw stream_error;
  }
}

void Serialize::read_uint8(istream& stream, Uint8& val)
{
  if (stream.good())
  {
    stream.read((char*)&val, sizeof(val));
  }
  else
  {
    SerializationException stream_error("Could not read Uint8");
    throw stream_error;
  }

  if (stream.fail())
  {
    SerializationException stream_error("Could not read full unsigned int");
    throw stream_error;
  }
}

void Serialize::write_sdl_colour(ostream& stream, const SDL_Color& color)
{
  Serialize::write_uint8(stream, color.r);
  Serialize::write_uint8(stream, color.g);
  Serialize::write_uint8(stream, color.b);
  Serialize::write_uint8(stream, color.a);
}

void Serialize::read_sdl_colour(istream& stream, SDL_Color& color)
{
  Serialize::read_uint8(stream, color.r);
  Serialize::read_uint8(stream, color.g);
  Serialize::read_uint8(stream, color.b);
  Serialize::read_uint8(stream, color.a);
}
#endif

#ifdef UNIT_TESTS
#include "unit_tests/Serialize_test.cpp"
#endif
