#pragma once
#include <map>
#include <string>
#include "Screen.hpp"
#include "Display.hpp"

class RaceSelectionScreen : public Screen
{
  public:
    RaceSelectionScreen(DisplayPtr new_display, const std::string& synopsis);

  protected:
    void initialize() override;

    std::map<int, std::string> screen_selection_to_race_id_map;
    std::string creature_synopsis;
};
