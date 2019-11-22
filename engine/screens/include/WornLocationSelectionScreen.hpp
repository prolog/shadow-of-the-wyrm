#pragma once
#include "Screen.hpp"
#include "Display.hpp"

class WornLocationSelectionScreen : public Screen
{
  public:
    WornLocationSelectionScreen(DisplayPtr display, const std::vector<EquipmentWornLocation>& new_worn_locs, const std::string& new_prompt_text_sid);
    std::vector<EquipmentWornLocation> get_worn_locs();

  protected:
    void initialize() override;

    std::vector<EquipmentWornLocation> worn_locs;
    std::string prompt_text_sid;
};

// The shared_ptr is needed so that it can be passed around without actually
// calling the destructor, which triggers the removal/freeing of the underlying
// texture in SDL.
using WornLocationSelectionScreenPtr = std::shared_ptr<WornLocationSelectionScreen>;