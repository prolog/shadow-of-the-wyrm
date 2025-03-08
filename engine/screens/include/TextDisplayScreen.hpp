#pragma once
#include <deque>
#include "Screen.hpp"
#include "Colours.hpp"
#include "Symbol.hpp"

// A generic screen that can be used to display text (help files, etc).
class TextDisplayScreen : public Screen
{
  public:
    TextDisplayScreen(DisplayPtr display, const std::string& new_title_text_sid, const std::vector<TextDisplayPair>& display_text, const bool preserve_formatting = false, const std::deque<Symbol>& symbols = {});

  protected:
    void initialize_text_screen(const std::string& new_title_text_sid, const bool preserve_formatting);

    // Each string in the vector represents a line to be displayed on
    // screen.
    std::vector<TextDisplayPair> text;  
    std::deque<Symbol> replacement_symbols;
};
