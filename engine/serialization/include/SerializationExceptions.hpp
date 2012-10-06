#pragma once
#include <string>
#include <exception>

class SerializationException : public std::exception
{
  public:
    SerializationException();
    SerializationException(const std::string& additional_description);

    virtual const char* what() const throw();
  
  private:
    std::string additional_desc;
};
