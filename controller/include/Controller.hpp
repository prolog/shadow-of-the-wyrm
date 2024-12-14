#pragma once
#include <string>
#include <memory>
#include "ISerializable.hpp"

// Abstract base class capable of getting a character or a line
class Controller : public ISerializable
{
  public:
    virtual ~Controller();
    bool operator==(const Controller& controller) const;

    // Only needs to be implemented for interfaces like SDL where the
    // event queue has to be delicately handled or else you'll get
    // "Not Responding" errors.
    virtual void poll_event();

    virtual int get_char_as_int();

    // Non-blocking version.  Returns true when input is present, false
    // otherwise.  When pair.first is false, pair.second will always be
    // -1.
    virtual std::pair<bool, int> get_char_as_int_nb();

    virtual bool serialize(std::ostream&) const override;
    virtual bool deserialize(std::istream&) override;

    virtual Controller* clone() = 0;

  protected:
    virtual int read_char_as_int() = 0;
    virtual std::pair<bool, int> read_char_as_int_nb() = 0;

    virtual int translate_kb_input(const int input) = 0;

  private:
    ClassIdentifier internal_class_identifier() const = 0;
};

using ControllerPtr = std::shared_ptr<Controller>;
