#pragma once
#include <map>
#include <string>
#include "Screen.hpp"
#include "Display.hpp"
#include "Race.hpp"

class DeitySelectionScreen : public Screen
{
  public:
    DeitySelectionScreen(DisplayPtr new_display, RacePtr selected_race);

  protected:
    void initialize() override;

    RacePtr race;
    std::map<int, std::string> screen_selection_to_deity_id;
};
