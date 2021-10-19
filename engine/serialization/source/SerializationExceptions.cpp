#include "SerializationExceptions.hpp"

using std::string;

SerializationException::SerializationException()
: msg("Serialization Exception")
{
}

SerializationException::SerializationException(const std::string& addl_details)
: additional_desc(addl_details)
{
}


// Serialization exception
const char* SerializationException::what() const throw()
{
  if (!additional_desc.empty())
  {
    return additional_desc.c_str();
  }

  return msg.c_str();
}

