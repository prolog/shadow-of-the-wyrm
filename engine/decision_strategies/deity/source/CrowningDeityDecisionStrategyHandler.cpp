#include "ClassManager.hpp"
#include "CreatureFeatures.hpp"
#include "CrowningDeityDecisionStrategyHandler.hpp"
#include "DeityTextKeys.hpp"
#include "Game.hpp"
#include "ItemManager.hpp"
#include "Memberships.hpp"
#include "MusicEvent.hpp"
#include "ReligionConstants.hpp"
#include "ReligionManager.hpp"
#include "RNG.hpp"

using namespace std;

const int CrowningDeityDecisionStrategyHandler::PIETY_LOSS_CROWNING_UNSTABLE_GROUND = 500;

CrowningDeityDecisionStrategyHandler::CrowningDeityDecisionStrategyHandler(const string& deity_id)
: DeityDecisionStrategyHandler(deity_id),
  alignment_crowning_events{{AlignmentRange::ALIGNMENT_RANGE_GOOD, MusicEvent::MUSIC_EVENT_CROWNING_GOOD},
                            {AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, MusicEvent::MUSIC_EVENT_CROWNING_NEUTRAL},
                            {AlignmentRange::ALIGNMENT_RANGE_EVIL, MusicEvent::MUSIC_EVENT_CROWNING_EVIL} }
{
}

std::unique_ptr<DeityDecisionStrategyHandler> CrowningDeityDecisionStrategyHandler::clone()
{
  std::unique_ptr<DeityDecisionStrategyHandler> handler = std::make_unique<CrowningDeityDecisionStrategyHandler>(*this);
  return handler;
}

bool CrowningDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  ReligionManager rm;
  Deity* active_deity = rm.get_active_deity(creature);

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
  DeityDecisionImplications implications = get_deity_decision_implications(creature, tile);

  if (tile != nullptr && tile->get_items()->get_allows_items() == AllowsItemsType::ALLOWS_ITEMS)
  {
    crown_champion(creature);
    fortify_champion(creature);
    add_crowning_gift(creature, tile);
  }
  else
  {
    implications = DeityDecisionImplications(PIETY_LOSS_CROWNING_UNSTABLE_GROUND, DeityTextKeys::PRAYER_CROWNING_SOLID_GROUND, false, false);
  }

  return implications;
}

// Set the creature to be the champion of this deity.
void CrowningDeityDecisionStrategyHandler::crown_champion(CreaturePtr creature)
{
  if (creature != nullptr)
  {
    ReligionManager rm;
    Religion& religion = creature->get_religion_ref();
    DeityStatus status = rm.get_active_deity_status(creature);
    Deity* deity = rm.get_deity(deity_id);

    status.set_champion_type(ChampionType::CHAMPION_TYPE_CROWNED);
    religion.set_deity_status(deity_id, status);

    MembershipFactory mf;
    Membership champion = mf.create_holy_champion();
    creature->get_memberships_ref().add_membership(champion.get_membership_id(), champion);

    Game::instance().get_sound(creature)->play_music_for_event(alignment_crowning_events[deity->get_alignment_range()], false);
  }
}

// Champions get a 10% damage reduction for all damage types.
void CrowningDeityDecisionStrategyHandler::fortify_champion(CreaturePtr creature)
{
  Resistances& intrinsics = creature->get_intrinsic_resistances_ref();

  for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
  {
    DamageType dt = static_cast<DamageType>(d);
    Resistance& cur_res = intrinsics.get_resistance_ref(dt);
    cur_res.set_value(cur_res.get_value() + 0.1);
  }
}

// A gift is customary when crowning - either a nice artifact, or (in the
// rare event that all of the deity's artifacts have already been generated)
// a pile of cash.
void CrowningDeityDecisionStrategyHandler::add_crowning_gift(CreaturePtr creature, TilePtr tile)
{
  // A gift is customary.  First, try to generate an artifact.
  ReligionManager rm;
  Deity* deity = rm.get_deity(deity_id);
  ItemPtr crowning_gift;
  bool added_gift = false;

  if (deity != nullptr && tile != nullptr && creature != nullptr)
  {
    vector<string> gifts = select_crowning_gifts(creature, deity);
    shuffle(gifts.begin(), gifts.end(), RNG::get_engine());

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
    crowning_gift->set_status(ItemStatus::ITEM_STATUS_BLESSED);
    IInventoryPtr inv = tile->get_items();
    inv->add_front(crowning_gift);
  }
}

int CrowningDeityDecisionStrategyHandler::get_piety_amount() const
{
  return (ReligionConstants::PIETY_CROWNING / 4);
}

string CrowningDeityDecisionStrategyHandler::get_message_sid() const
{
  string message_sid = DeityTextKeys::PRAYER_CROWNING;
  return message_sid;
}

bool CrowningDeityDecisionStrategyHandler::get_add_message_with_pause() const
{
  return true;
}

bool CrowningDeityDecisionStrategyHandler::get_reload_map_music() const
{
  return true;
}

vector<string> CrowningDeityDecisionStrategyHandler::select_crowning_gifts(CreaturePtr creature, Deity* deity)
{
  vector<string> gifts;

  if (creature != nullptr && deity != nullptr)
  {
    if (RNG::percent_chance(deity->get_pct_chance_class_crowning()))
    {
      ClassManager cm;
      Class* cur_class = cm.get_class(creature->get_class_id());

      if (cur_class != nullptr)
      {
        gifts = cur_class->get_crowning_gifts();
      }
    }
    else
    {
      gifts = deity->get_crowning_gifts();
    }
  }

  return gifts;
}