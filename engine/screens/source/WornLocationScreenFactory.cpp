#include "WornLocationScreenFactory.hpp"
#include "PromptTextKeys.hpp"

using namespace std;

WornLocationSelectionScreenPtr WornLocationScreenFactory::create_skin_screen(DisplayPtr display)
{
  vector<EquipmentWornLocation> skin_locs = { EquipmentWornLocation::EQUIPMENT_WORN_HEAD, EquipmentWornLocation::EQUIPMENT_WORN_BODY, EquipmentWornLocation::EQUIPMENT_WORN_AROUND_BODY, EquipmentWornLocation::EQUIPMENT_WORN_FEET, EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON };
  WornLocationSelectionScreenPtr scr = make_unique<WornLocationSelectionScreen>(display, skin_locs, PromptTextKeys::PROMPT_SKIN);

  return scr;
}

WornLocationSelectionScreenPtr WornLocationScreenFactory::create_weaving_screen(DisplayPtr display)
{
  vector<EquipmentWornLocation> weave_locs = { EquipmentWornLocation::EQUIPMENT_WORN_BODY, EquipmentWornLocation::EQUIPMENT_WORN_AROUND_BODY };
  WornLocationSelectionScreenPtr scr = make_unique<WornLocationSelectionScreen>(display, weave_locs, PromptTextKeys::PROMPT_WEAVE);

  return scr;
}

