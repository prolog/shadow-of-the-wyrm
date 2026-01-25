#pragma once
#include "curses.hpp"
#include "Controller.hpp"

class CursesKeyboardController : public Controller
{
  public:
    virtual Controller* clone() override;
    virtual ~CursesKeyboardController() = default;

  protected:
    std::pair<int, std::set<KeyModifierType>> read_char_as_int() override;
    std::pair<bool, int> read_char_as_int_nb() override;

    int translate_kb_input(const int input, const std::set<KeyModifierType>& key_modifiers) override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
