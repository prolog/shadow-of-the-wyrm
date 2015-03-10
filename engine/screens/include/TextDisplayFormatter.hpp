#pragma once
#include <string>
#include <vector>
#include "Display.hpp"

// A class for breaking up text into lines of a particular length.  Its
// implementation gets the display information off the game object, queries
// that for the display width, and then formats the incoming text.
class TextDisplayFormatter
{
  public:
    std::vector<std::string> format_text(const std::string& text, const int lines_displayable_area = -1) const;

  protected:
    void process_token(const std::string& token, std::vector<std::string>& result, std::string& current_str, uint& cur_pos, const uint width, const int lines_displayable_area, int& cur_line) const;
};

