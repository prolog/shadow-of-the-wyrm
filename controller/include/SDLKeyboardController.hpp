#pragma once
#include "Controller.hpp"

class SDLKeyboardController : public Controller
{
  public:
    std::string get_line() override;

    virtual Controller* clone() override;

  protected:
    int read_char_as_int() override;
    virtual std::pair<bool, int> read_char_as_int_nb() override;

    int translate_kb_input(const int input) override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
