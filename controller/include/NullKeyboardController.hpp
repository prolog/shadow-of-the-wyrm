#pragma once
#include "Controller.hpp"

// Because non-player-controlled creatures shouldn't need to get keyboard input, a simple
// class is defined that returns default values.
class NullKeyboardController : public Controller
{
  public:
    virtual ~NullKeyboardController() = default;

    virtual Controller* clone() override;

  protected:
    int read_char_as_int() override;
    std::pair<bool, int> read_char_as_int_nb() override;

    int translate_kb_input(const int input) override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
