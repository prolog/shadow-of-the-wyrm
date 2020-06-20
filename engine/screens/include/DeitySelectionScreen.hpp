#pragma once
#include <map>
#include <string>
#include "Screen.hpp"
#include "Display.hpp"
#include "Race.hpp"

class DeitySelectionScreen : public Screen
{
  public:
    DeitySelectionScreen(DisplayPtr new_display, Race* selected_race, const std::string& synopsis);

  protected:
    void initialize() override;

    Race* race;
    std::map<int, std::string> screen_selection_to_deity_id;
    std::string creature_synopsis;
};
