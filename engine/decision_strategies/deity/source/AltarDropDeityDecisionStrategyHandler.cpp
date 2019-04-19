#include "AltarDropDeityDecisionStrategyHandler.hpp"
#include "DeityTextKeys.hpp"
#include "DislikeDeityDecisionStrategyHandler.hpp"
#include "EffectTextKeys.hpp"
#include "ItemIdentifier.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

const int AltarDropDeityDecisionStrategyHandler::PIETY_LOSS_COALIGN = 200;
const int AltarDropDeityDecisionStrategyHandler::PIETY_LOSS_CROSSALIGN = 0;

AltarDropDeityDecisionStrategyHandler::AltarDropDeityDecisionStrategyHandler(const string& new_deity_id)
: DeityDecisionStrategyHandler(new_deity_id)
{
}

AltarDropDeityDecisionStrategyHandler::AltarDropDeityDecisionStrategyHandler(const string& new_deity_id, CreaturePtr dropping_creature, FeaturePtr cur_altar, ItemPtr dropped_item)
: DeityDecisionStrategyHandler(new_deity_id), creature(dropping_creature), altar(cur_altar), drop_item(dropped_item)
{
}

bool AltarDropDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  // Decision is true if:
  // - Coaligned and creature is pious
  // - Crossaligned
  bool decision = false;

  if (altar != nullptr)
  {
    AlignmentRange creature_range = creature->get_alignment().get_alignment_range();
    AlignmentRange altar_range = altar->get_alignment_range();

    if (creature_range == altar_range)
    {
      DislikeDeityDecisionStrategyHandler ddsh(deity_id);

      // If the deity doesn't dislike the creature, carry on with the
      // blessing of altar items.
      if (ddsh.decide(creature) == false)
      {
        decision = true;
      }
    }
    else
    {
      decision = true;
    }
  }

  return decision;
}

DeityDecisionImplications AltarDropDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  string decision_msg;
  AlignmentRange creature_range = creature->get_alignment().get_alignment_range();
  AlignmentRange altar_range = altar->get_alignment_range();
  bool cross_aligned = (creature_range != altar_range);

  // Bless/curse the item as necessary
  if (drop_item)
  {
    ItemStatus status = ItemStatus::ITEM_STATUS_BLESSED;
    ItemIdentifier iid;
    string item_desc = iid.get_appropriate_usage_description(drop_item);

    decision_msg = EffectTextKeys::get_bless_effect_message(item_desc, false);

    if (cross_aligned)
    {
      status = ItemStatus::ITEM_STATUS_CURSED;
      decision_msg = EffectTextKeys::get_cursed_enchant_message(item_desc);
    }

    drop_item->set_status(status);
    drop_item->set_status_identified(true);
  }

  // Add a message?
  if (!decision_msg.empty())
  {
    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());

    // Are we at the wrong altar?
    if (cross_aligned)
    {
      manager.add_new_message(StringTable::get(DeityTextKeys::ALTAR_SENSE_CROSSALIGNED));
    }

    manager.add_new_message(decision_msg);
    manager.send();
  }

  return get_deity_decision_implications(creature, tile);
}

// If the altar is the same alignment as the creature, and the creature is
// pious, there is piety loss as the item becomes blessed.
//
// If the altar is not the same alignment as the creature, the item is
// cursed - no piety loss.
int AltarDropDeityDecisionStrategyHandler::get_piety_loss() const
{
  int piety_loss = PIETY_LOSS_CROSSALIGN;

  if (creature != nullptr && altar != nullptr && drop_item != nullptr)
  {
    AlignmentRange altar_range = altar->get_alignment_range();
    AlignmentRange creature_range = creature->get_alignment().get_alignment_range();

    if (creature_range == altar_range)
    {
      piety_loss = PIETY_LOSS_COALIGN;
    }
  }

  return piety_loss;
}

string AltarDropDeityDecisionStrategyHandler::get_message_sid() const
{
  string message_sid;

  return message_sid;
}

