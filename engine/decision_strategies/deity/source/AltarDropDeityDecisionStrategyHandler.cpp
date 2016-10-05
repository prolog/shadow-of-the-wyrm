#include "AltarDropDeityDecisionStrategyHandler.hpp"
#include "DislikeDeityDecisionStrategyHandler.hpp"

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

  return true;
}

DeityDecisionImplications AltarDropDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  // Bless/curse the item as necessary
  // ...

  // Add a message?
  // ...

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

