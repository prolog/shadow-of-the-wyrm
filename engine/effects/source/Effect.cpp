#include "Effect.hpp"

// Call the correct item effect function based on the item status.  Blessed effects can often be
// much better than uncursed, and cursed are often more hurtful than helpful.
bool Effect::effect(boost::shared_ptr<Creature> creature, const ItemStatus item_status) const
{
  bool effect_identified = false;

  switch(item_status)
  {
    case ITEM_STATUS_BLESSED:
      effect_identified = effect_blessed(creature);
      break;
    case ITEM_STATUS_CURSED:
      effect_identified = effect_cursed(creature);
      break;
    case ITEM_STATUS_UNCURSED:
    default:
      effect_identified = effect_uncursed(creature);
      break;
  }

  return effect_identified;
}

