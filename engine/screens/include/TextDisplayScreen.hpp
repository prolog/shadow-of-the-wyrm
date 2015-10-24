#pragma once
#include "Screen.hpp"
#include "Colours.hpp"

using TextDisplayPair = std::pair<Colour, std::string>;

// A generic screen that can be used to display text (help files, etc).
class TextDisplayScreen : public Screen
{
  public:
   TextDisplayScreen(DisplayPtr display, const std::string& new_title_text_sid, const std::vector<TextDisplayPair>& display_text, const bool preserve_formatting = false);

  protected:
    void initialize(const std::string& new_title_text_sid, const bool preserve_formatting);

    // Each string in the vector represents a line to be displayed on
    // screen.
    std::vector<TextDisplayPair> text;
};
