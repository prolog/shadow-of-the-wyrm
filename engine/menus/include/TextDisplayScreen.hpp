#pragma once
#include "Menu.hpp"
#include "Colours.hpp"

typedef std::pair<Colour, std::string> TextDisplayPair;

// A generic menu that can be used to display text (help files, etc).
class TextDisplayScreen : public Menu
{
  public:
   TextDisplayScreen(DisplayPtr display, const std::string& new_title_text_sid, const std::vector<TextDisplayPair>& display_text);

  protected:
    void initialize(const std::string& new_title_text_sid);

    // Each string in the vector represents a line to be displayed on
    // screen.
    std::vector<TextDisplayPair> text;
};
