#pragma once
#include <string>
#include <vector>
#include <utility>
#include "Display.hpp"

// A class for breaking up text into lines of a particular length.  Its
// implementation gets the display information off the game object, queries
// that for the display width, and then formats the incoming text.
class TextDisplayFormatter
{
  public:
    TextDisplayFormatter();
    TextDisplayFormatter(const bool new_keep_leading_whitespace);

    // Break text into lines of the appropriate length.
    std::vector<std::string> format_text(const std::string& text, const int lines_displayable_area = -1) const;

    // Create colour-and-text pairs suitable for passing to a Screen object.
    std::vector<std::pair<Colour, std::string>> format_text_for_screen(const std::vector<std::string>& formatted_text);

  protected:
    void process_token(const std::string& token, std::vector<std::string>& result, std::string& current_str, uint& cur_pos, const uint width, const int lines_displayable_area, int& cur_line) const;
    bool should_process_token(const std::string& token, const uint cur_pos) const;

    bool keep_leading_whitespace;
};

