#include "SoakCalculator.hpp"
#include "Wearable.hpp"

using namespace std;

SoakCalculator::SoakCalculator()
{
}

SoakCalculator::~SoakCalculator()
{
}

// A creature gets 1 point of Soak for every 4 Health over 10,
// plus any bonuses or penalties from equipment.
int SoakCalculator::calculate_soak(const CreaturePtr& c)
{
  int soak = 0;

  if (c)
  {
    soak = c->get_base_soak().get_current();

    soak += get_equipment_bonus(c);
    soak += get_modifier_bonus(c);
    soak += get_health_bonus(c);
    soak += get_rage_bonus(c);
  }

  return soak;
}

int SoakCalculator::get_equipment_bonus(const CreaturePtr& c)
{
  int equipment_soak_bonus = 0;

  Equipment& eq = c->get_equipment();
  EquipmentMap equipment = eq.get_equipment();

  for (const EquipmentMap::value_type& item : equipment)
  {
    WearablePtr equipped = dynamic_pointer_cast<Wearable>(item.second);

    if (equipped)
    {
      // The player can equip a lot of things in the ammunition slot.
      // Prevent the use of anything but ammunition when calculating
      // soak.
      if (item.first == EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION)
      {
        if (equipped->get_type() == ItemType::ITEM_TYPE_AMMUNITION)
        {
          equipment_soak_bonus += equipped->get_evade();
        }
      }
      else
      {
        equipment_soak_bonus += equipped->get_soak();
      }
    }
  }

  return equipment_soak_bonus;
}

int SoakCalculator::get_modifier_bonus(const CreaturePtr& c)
{
  int mod_bonus = 0;

  if (c)
  {
    const map<double, vector<pair<string, Modifier>>> modifiers = c->get_active_modifiers();

    for (const auto& mod_pair : modifiers)
    {
      for (const auto& current_mod_pair : mod_pair.second)
      {
        mod_bonus += current_mod_pair.second.get_soak_modifier();
      }
    }
  }

  return mod_bonus;
}

int SoakCalculator::get_health_bonus(const CreaturePtr& c)
{
  int health_bonus = 0;

  if (c != nullptr)
  {
    int health = c->get_health().get_current();

    if (health > 10)
    {
      health_bonus = (health - 10) / 4;
    }
  }

  return health_bonus;
}

int SoakCalculator::get_rage_bonus(const CreaturePtr& c)
{
  int rage_bonus = 0;

  if (c != nullptr)
  {
    if (c->has_status(StatusIdentifiers::STATUS_ID_RAGE))
    {
      rage_bonus = c->get_level().get_current();
    }
  }

  return rage_bonus;
}


#ifdef UNIT_TESTS
#include "unit_tests/SoakCalculator_test.cpp"
#endif
