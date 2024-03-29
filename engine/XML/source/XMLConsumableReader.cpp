#include "XMLConsumableReader.hpp"
#include "ItemProperties.hpp"

XMLConsumableReader::XMLConsumableReader()
{
}

XMLConsumableReader::~XMLConsumableReader()
{
}

// Methods for parsing a Consumable based on a provided XML node
// conformant to the "Consumable" type in the schema.
void XMLConsumableReader::parse(ConsumablePtr consumable, GenerationValues& gv, const XMLNode& node)
{
  if (consumable && !node.is_null())
  {
    XMLItemReader::parse(consumable, gv, node);
    uint nutrition = static_cast<uint>(XMLUtils::get_child_node_int_value(node, "Nutrition", 0));
    consumable->set_nutrition(nutrition);

    float standard_drinks = XMLUtils::get_child_node_float_value(node, "StandardDrinks", consumable->get_standard_drinks());
    consumable->set_standard_drinks(standard_drinks);

    XMLNode food_type_node = XMLUtils::get_next_element_by_local_name(node, "FoodType");
    if (!food_type_node.is_null())
    {
      FoodType food_type = static_cast<FoodType>(XMLUtils::get_node_int_value(food_type_node, static_cast<int>(FoodType::FOOD_TYPE_OTHER)));
      consumable->set_food_type(food_type);
    }

    XMLNode metabolizes_alcohol_node = XMLUtils::get_next_element_by_local_name(node, "MetabolizesAlcohol");
    if (!metabolizes_alcohol_node.is_null())
    {
      bool metabolizes = XMLUtils::get_node_bool_value(metabolizes_alcohol_node, false);
      consumable->set_additional_property(ItemProperties::ITEM_PROPERTIES_METABOLIZES_ALCOHOL, std::to_string(metabolizes));
    }

    bool poisoned = XMLUtils::get_child_node_bool_value(node, "Poisoned", consumable->get_poisoned());
    consumable->set_poisoned(poisoned);

    EffectType effect_type = static_cast<EffectType>(XMLUtils::get_child_node_int_value(node, "Effect", static_cast<int>(EffectType::EFFECT_TYPE_NULL)));
    consumable->set_effect_type(effect_type);
  }
}
