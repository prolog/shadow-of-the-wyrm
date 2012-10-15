#include <boost/foreach.hpp>
#include "ActionManager.hpp"
#include "Creature.hpp"
#include "IdentifyEffect.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemIdentifier.hpp"
#include "Serialize.hpp"
#include "StringConstants.hpp"

using namespace std;

string IdentifyEffect::get_effect_identification_message(boost::shared_ptr<Creature> creature) const
{
  return identification_msg;
}

Effect* IdentifyEffect::clone()
{
  return new IdentifyEffect(*this);
}

// A blessed identify effect identifies everything in the character's inventory, as well as its
// worn equipment.
bool IdentifyEffect::effect_blessed(boost::shared_ptr<Creature> creature, ActionManager * const am) 
{
  if (creature)
  {
    ItemIdentifier item_id;
    item_id.set_possessions_identified(creature);    
    identification_msg = StringTable::get(EffectTextKeys::EFFECT_IDENTIFY_ALL_ITEMS);
  }
  
  return true;
}

// Uncursed identify identifies all items of a particular type.
bool IdentifyEffect::effect_uncursed(boost::shared_ptr<Creature> creature, ActionManager * const am)
{
  if (creature)
  {
    ItemIdentifier item_id;

    // Pick an item.  Identify all possessions of that type.
    list<IItemFilterPtr> empty_filter = ItemFilterFactory::create_empty_filter();
    ItemPtr item = am->inventory(creature, creature->get_inventory(), empty_filter, false);
    
    if (item)
    {
      ItemType item_type = item->get_type();
      item_id.set_possessions_identified_by_type(creature, item_type);
      return true;
    }
  }
  
  return false;
}

// Cursed identify still helps, but not as much as the other statuses.  It only identifies the
// item selected by the player.
bool IdentifyEffect::effect_cursed(boost::shared_ptr<Creature> creature, ActionManager * const am)
{
  if (creature)
  {
    ItemIdentifier item_id;
    
    // Pick an item.  Identify that item.
    list<IItemFilterPtr> empty_filter = ItemFilterFactory::create_empty_filter();
    ItemPtr item = am->inventory(creature, creature->get_inventory(), empty_filter, false);
    
    if (item)
    {
      item_id.set_item_identified(item, item->get_base_id(), true);
      return true;
    }
  }
  
  return false;
}

bool IdentifyEffect::serialize(ostream& stream)
{
  Effect::serialize(stream);
  Serialize::write_string(stream, identification_msg);

  return true;
}

bool IdentifyEffect::deserialize(istream& stream)
{
  Effect::deserialize(stream);
  Serialize::read_string(stream, identification_msg);

  return true;
}

ClassIdentifier IdentifyEffect::internal_class_identifier() const
{
  return CLASS_ID_IDENTIFY_EFFECT;
}