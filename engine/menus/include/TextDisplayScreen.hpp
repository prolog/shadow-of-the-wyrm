#pragma once
#include "Menu.hpp"

// A generic menu that can be used to display text (help files, etc).
class TextDisplayScreen : public Menu
{
  public:
   TextDisplayScreen(DisplayPtr display, const std::string& new_title_text_sid, const std::vector<std::string>& display_text);

  protected:
    void initialize(const std::string& new_title_text_sid);

    // Each string in the vector represents a line to be displayed on
    // screen.
    std::vector<std::string> text;
};
