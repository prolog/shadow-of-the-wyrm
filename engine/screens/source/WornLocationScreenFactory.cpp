#include "WornLocationScreenFactory.hpp"
#include "TextKeys.hpp"

using namespace std;

WornLocationSelectionScreen WornLocationScreenFactory::create_skin_screen(DisplayPtr display)
{
  vector<EquipmentWornLocation> skin_locs = { EQUIPMENT_WORN_HEAD, EQUIPMENT_WORN_BODY, EQUIPMENT_WORN_AROUND_BODY, EQUIPMENT_WORN_FEET };
  WornLocationSelectionScreen scr(display, skin_locs, TextKeys::SKIN_PROMPT);

  return scr;
}

WornLocationSelectionScreen WornLocationScreenFactory::create_weaving_screen(DisplayPtr display)
{
  vector<EquipmentWornLocation> weave_locs = { EQUIPMENT_WORN_BODY, EQUIPMENT_WORN_AROUND_BODY };
  WornLocationSelectionScreen scr(display, weave_locs, TextKeys::WEAVE_PROMPT);

  return scr;
}

