#pragma once
#include <string>
#include <boost/shared_ptr.hpp>

// Abstract base class capable of getting a character or a line
class Controller
{
  public:
    virtual std::string get_line() = 0;
    virtual int get_char_as_int() = 0;
};

typedef boost::shared_ptr<Controller> ControllerPtr;
