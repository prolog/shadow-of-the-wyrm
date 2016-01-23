#include "DeityTextKeys.hpp"
#include "CombatManager.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "UncurseDeityDecisionStrategyHandler.hpp"

using namespace std;

UncurseDeityDecisionStrategyHandler::UncurseDeityDecisionStrategyHandler(const string& new_deity_id)
: DeityDecisionStrategyHandler(new_deity_id)
{
}

bool UncurseDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  bool uncurse_creature = false;

  if (creature != nullptr)
  {
    Equipment& eq = creature->get_equipment();
    EquipmentMap em = eq.get_equipment();

    for (const auto& eq_pair : em)
    {
      if (eq_pair.second != nullptr && eq_pair.second->get_status() == ItemStatus::ITEM_STATUS_CURSED)
      {
        uncurse_creature = true;
        break;
      }
    }
  }

  return uncurse_creature;
}

// When a deity lifts a curse, they set all the cursed worn equipment to
// uncursed and identified.
DeityDecisionImplications UncurseDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  if (creature != nullptr)
  {
    EquipmentMap& em = creature->get_equipment().get_equipment();

    for (auto& em_pair : em)
    {
      if (em_pair.second && em_pair.second->get_status() == ItemStatus::ITEM_STATUS_CURSED)
      {
        em_pair.second->set_status(ItemStatus::ITEM_STATUS_UNCURSED);
        em_pair.second->set_status_identified(true);
      }
    }
  }

  return get_deity_decision_implications(creature, tile);
}

int UncurseDeityDecisionStrategyHandler::get_piety_loss() const
{
  return 800;
}

string UncurseDeityDecisionStrategyHandler::get_message_sid() const
{
  string message_sid = DeityTextKeys::PRAYER_UNCURSE;
  return message_sid;
}
