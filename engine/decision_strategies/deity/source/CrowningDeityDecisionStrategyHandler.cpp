#include "DeityTextKeys.hpp"
#include "CrowningDeityDecisionStrategyHandler.hpp"
#include "ItemManager.hpp"
#include "ReligionConstants.hpp"
#include "ReligionManager.hpp"

using namespace std;

CrowningDeityDecisionStrategyHandler::CrowningDeityDecisionStrategyHandler(const string& deity_id)
: DeityDecisionStrategyHandler(deity_id)
{
}

bool CrowningDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  ReligionManager rm;

  DeityPtr active_deity = rm.get_active_deity(creature);

  if (active_deity && (active_deity->get_id() == deity_id))
  {
    DeityStatus status = rm.get_active_deity_status(creature);

    // Only uncrowned creatures can become crowned - fallen champions
    // cannot return to their deity's grace.
    if (status.get_champion_type() == ChampionType::CHAMPION_TYPE_UNCROWNED &&
      (status.get_piety() >= ReligionConstants::PIETY_CROWNING))
    {
      return true;
    }
  }

  return false;
}

DeityDecisionImplications CrowningDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  crown_champion(creature);
  fortify_champion(creature);
  add_crowning_gift(creature, tile);

  return get_deity_decision_implications(creature, tile);
}

// Set the creature to be the champion of this deity.
void CrowningDeityDecisionStrategyHandler::crown_champion(CreaturePtr creature)
{
  ReligionManager rm;
  Religion& religion = creature->get_religion_ref();
  DeityStatus status = rm.get_active_deity_status(creature);

  status.set_champion_type(ChampionType::CHAMPION_TYPE_CROWNED);
  religion.set_deity_status(deity_id, status);
}

// Champions get a 10% damage reduction for all damage types.
void CrowningDeityDecisionStrategyHandler::fortify_champion(CreaturePtr creature)
{
  Resistances& intrinsics = creature->get_intrinsic_resistances_ref();

  for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
  {
    DamageType dt = static_cast<DamageType>(d);

    ResistancePtr cur_res = intrinsics.get_resistance(dt);

    if (cur_res)
    {
      cur_res->set_value(cur_res->get_value() + 0.1);
    }
  }
}

// A gift is customary when crowning - either a nice artifact, or (in the
// rare event that all of the deity's artifacts have already been generated)
// a pile of cash.
void CrowningDeityDecisionStrategyHandler::add_crowning_gift(CreaturePtr creature, TilePtr tile)
{
  // A gift is customary.  First, try to generate an artifact.
  ReligionManager rm;
  DeityPtr deity = rm.get_deity(deity_id);
  ItemPtr crowning_gift;
  bool added_gift = false;

  if (deity && tile)
  {
    vector<string> gifts = deity->get_crowning_gifts();
    random_shuffle(gifts.begin(), gifts.end());

    for (const string& gift : gifts)
    {
      crowning_gift = ItemManager::create_item(gift);

      if (crowning_gift)
      {
        added_gift = true;
        break;
      }
    }
  }

  // This should never happen, but if none of the gifts can be generated,
  // create a big pile of money.
  if (!added_gift)
  {
    crowning_gift = ItemManager::create_item(ItemIdKeys::ITEM_ID_CURRENCY, 10000);
  }

  if (crowning_gift != nullptr)
  {
    IInventoryPtr inv = tile->get_items();
    inv->add_front(crowning_gift);
  }
}

int CrowningDeityDecisionStrategyHandler::get_piety_loss() const
{
  return (ReligionConstants::PIETY_CROWNING / 4);
}

string CrowningDeityDecisionStrategyHandler::get_message_sid() const
{
  string message_sid = DeityTextKeys::PRAYER_CROWNING;
  return message_sid;
}

