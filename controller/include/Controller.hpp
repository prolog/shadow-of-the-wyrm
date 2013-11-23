#pragma once
#include <string>
#include <memory>
#include "ISerializable.hpp"

// Abstract base class capable of getting a character or a line
class Controller : public ISerializable
{
  public:
    virtual bool operator==(const Controller& controller) const;

    virtual std::string get_line() = 0;
    virtual int get_char_as_int() = 0;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

    virtual Controller* clone() = 0;

  private:
    ClassIdentifier internal_class_identifier() const = 0;
};

typedef std::shared_ptr<Controller> ControllerPtr;
