#pragma once
#include "Screen.hpp"
#include "Display.hpp"

class WornLocationSelectionScreen : public Screen
{
  public:
    WornLocationSelectionScreen(DisplayPtr display, const std::vector<EquipmentWornLocation>& new_worn_locs, const std::string& new_prompt_text_sid);

  protected:
    void initialize() override;

    std::vector<EquipmentWornLocation> worn_locs;
    std::string prompt_text_sid;
};
