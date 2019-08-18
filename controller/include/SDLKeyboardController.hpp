#pragma once
#include "Controller.hpp"

class SDLKeyboardController : public Controller
{
  public:
    std::string get_line() override;
    int get_char_as_int() override;

    // Non-blocking version.  Returns true when input is present, false
    // otherwise.  When pair.first is false, pair.second will always be
    // -1.
    virtual std::pair<bool, int> get_char_as_int_nb() override;

    virtual Controller* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
