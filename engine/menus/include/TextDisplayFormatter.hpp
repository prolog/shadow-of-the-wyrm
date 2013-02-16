#pragma once
#include <string>
#include <vector>

// A class for breaking up text into lines of a particular length.  Its
// implementation gets the display information off the game object, queries
// that for the display width, and then formats the incoming text.
class TextDisplayFormatter
{
  public:
    std::vector<std::string> format_text(const std::string& text) const;
};

