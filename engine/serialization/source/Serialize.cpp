#include <boost/scoped_array.hpp>
#include "Serialize.hpp"
#include "SerializationExceptions.hpp"

using namespace std;

// Write the class identifier.  This is used by factory classes to determine which type of object to 
// default construct.
void Serialize::write_class_id(ostream& stream, const ClassIdentifier val)
{
  if (stream.good())
  {
    stream.write((char*)&val, sizeof(val));
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
    stream.write((char*)&val, sizeof(val));
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
    stream.write((char*)&val, sizeof(val));
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

// Write an unsigned int value.
void Serialize::write_uint(ostream& stream, const unsigned int val)
{
  if (stream.good())
  {
    stream.write((char*)&val, sizeof(val));
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
    stream.write((char*)&val, sizeof(val));
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

// Write a double value.
void Serialize::write_double(ostream& stream, const double val)
{
  if (stream.good())
  {
    stream.write((char*)&val, sizeof(val));
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
void Serialize::write_string(ostream& stream, const string& val)
{
  if (stream.good())
  {
    size_t val_size = val.size();
    Serialize::write_size_t(stream, val_size);

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
    size_t string_size;
    Serialize::read_size_t(stream, string_size);
 
    boost::scoped_array<char> raw_str(new char[string_size]);

    stream.read(raw_str.get(), sizeof(string_size));

    // Now that we have the actual string, create a copy and assign it to the passed-in
    // reference.  The scoped pointer should take care of deletion afterwards.
    val = raw_str.get();
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

