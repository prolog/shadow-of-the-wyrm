#pragma once
#include <string>
#include <vector>

// Class that parses keybindings from the ini file.
// Keybindings are separated by ||
// So:
//
// key_SEARCH=s||S
//
// would return a vector {"s", "S"} 
class SettingKeybindings
{
  public:
    std::vector<std::string> get_keybindings(const std::string& setting) const;
};

