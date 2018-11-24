#pragma once
#include <map>
#include "Screen.hpp"
#include "Display.hpp"
#include "StartingLocation.hpp"

class StartingLocationSelectionScreen : public Screen
{
  public:
    StartingLocationSelectionScreen(DisplayPtr display, const std::string& creature_synop, const StartingLocationMap& sm);

  protected:
    void initialize() override;

    std::string creature_synopsis;
    StartingLocationMap sm;
    std::map<int, std::string> screen_selection_to_sl_id_map;
};
