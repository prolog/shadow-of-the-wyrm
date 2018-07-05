#pragma once
#include "Screen.hpp"

// In general, most screens in SotW are named and their classes
// encapsulate a lot of the functionality.  OptionScreen is generically
// named and meant to be called from contexts that need a generic menu,
// such as from Lua code, etc.
class OptionScreen : public Screen
{
  public:
    OptionScreen(DisplayPtr display, const std::string& new_title_sid, const std::vector<std::string>& new_options);
    std::string get_option(const char selection);

  protected:
    void initialize() override;

    std::string title_sid;

    // Use a vector of properties (<"a=b", "c=d", etc>) to ensure ordering of
    // the options is preserved.
    std::vector<std::string> options;
    std::vector<std::map<char, std::string>> screen_selection_to_id_map;
};
