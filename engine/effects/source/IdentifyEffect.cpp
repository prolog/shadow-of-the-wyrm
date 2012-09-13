#include <boost/foreach.hpp>
#include "Creature.hpp"
#include "IdentifyEffect.hpp"
#include "ItemIdentifier.hpp"
#include "StringConstants.hpp"

using boost::shared_ptr;
using namespace std;

string IdentifyEffect::get_effect_identification_message(shared_ptr<Creature> creature) const
{
  return identification_msg;
}

Effect* IdentifyEffect::clone()
{
  return new IdentifyEffect(*this);
}

// A blessed identify effect identifies everything in the character's inventory, as well as its
// worn equipment.
bool IdentifyEffect::effect_blessed(shared_ptr<Creature> creature) 
{
  if (creature)
  {
    ItemIdentifier item_id;
    item_id.set_possessions_identified(creature);    
    identification_msg = StringTable::get(EffectTextKeys::EFFECT_IDENTIFY_ALL_ITEMS);
  }
  
  return true;
}

bool IdentifyEffect::effect_uncursed(shared_ptr<Creature> creature)
{
  if (creature)
  {
    ItemIdentifier item_id;

    // Pick an item.  Identify all possessions of that type.
  }
  
  return true;
}

bool IdentifyEffect::effect_cursed(shared_ptr<Creature> creature)
{
  if (creature)
  {
    ItemIdentifier item_id;
    
    // Pick an item.  Identify that item.
  }
  
  return true;
}

