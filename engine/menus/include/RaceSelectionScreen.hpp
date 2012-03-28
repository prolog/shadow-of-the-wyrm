#pragma once
#include <map>
#include <string>
#include "Menu.hpp"
#include "Display.hpp"

class RaceSelectionScreen : public Menu
{
  public:
    RaceSelectionScreen(DisplayPtr new_display);

  protected:
    void initialize();

    std::map<int, std::string> menu_selection_to_race_id_map;
};
