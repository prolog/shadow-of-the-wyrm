#include "SerializationExceptions.hpp"

using std::string;

SerializationException::SerializationException()
{
}

SerializationException::SerializationException(const std::string& addl_details)
: additional_desc(addl_details)
{
}


// Serialization exception
const char* SerializationException::what() const throw()
{
  string serialize_what = "Serialization Exception. ";

  if (!additional_desc.empty())
  {
    serialize_what += additional_desc;
  }

  return serialize_what.c_str();
}

