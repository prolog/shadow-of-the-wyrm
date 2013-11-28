#pragma once
#include <map>
#include <string>
#include "Menu.hpp"
#include "Display.hpp"
#include "Race.hpp"

class DeitySelectionScreen : public Menu
{
  public:
    DeitySelectionScreen(DisplayPtr new_display, RacePtr selected_race);

  protected:
    void initialize() override;

    RacePtr race;
    std::map<int, std::string> menu_selection_to_deity_id;
};
