#include "FeatureGenerator.hpp"
#include "XMLSlotMachineReader.hpp"

using namespace std;

FeaturePtr XMLSlotMachineReader::create(const XMLNode& smachine_node) const
{
  MaterialType material_type = MaterialType::MATERIAL_TYPE_IRON;
  XMLNode material_node = XMLUtils::get_next_element_by_local_name(smachine_node, "Material");
  if (!material_node.is_null())
  {
    material_type = static_cast<MaterialType>(XMLUtils::get_node_int_value(material_node));
  }

  int cost = 0;
  cost = XMLUtils::get_child_node_int_value(smachine_node, "Cost", cost);

  int pct_chance_win = 0;
  pct_chance_win = XMLUtils::get_child_node_int_value(smachine_node, "PctChanceWin", pct_chance_win);

  float payout_multiplier = 0.0f;
  payout_multiplier = XMLUtils::get_child_node_float_value(smachine_node, "PayoutMultiplier", payout_multiplier);

  SlotMachinePtr slot_machine = FeatureGenerator::generate_slot_machine(material_type, cost, pct_chance_win, payout_multiplier);
  return slot_machine;
}

