#include "WornLocationScreenFactory.hpp"
#include "TextKeys.hpp"

using namespace std;

WornLocationSelectionScreenPtr WornLocationScreenFactory::create_skin_screen(DisplayPtr display)
{
  vector<EquipmentWornLocation> skin_locs = { EquipmentWornLocation::EQUIPMENT_WORN_HEAD, EquipmentWornLocation::EQUIPMENT_WORN_BODY, EquipmentWornLocation::EQUIPMENT_WORN_AROUND_BODY, EquipmentWornLocation::EQUIPMENT_WORN_FEET, EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON };
  WornLocationSelectionScreenPtr scr = make_shared<WornLocationSelectionScreen>(display, skin_locs, TextKeys::SKIN_PROMPT);

  return scr;
}

WornLocationSelectionScreenPtr WornLocationScreenFactory::create_weaving_screen(DisplayPtr display)
{
  vector<EquipmentWornLocation> weave_locs = { EquipmentWornLocation::EQUIPMENT_WORN_BODY, EquipmentWornLocation::EQUIPMENT_WORN_AROUND_BODY };
  WornLocationSelectionScreenPtr scr = make_shared<WornLocationSelectionScreen>(display, weave_locs, TextKeys::WEAVE_PROMPT);

  return scr;
}

