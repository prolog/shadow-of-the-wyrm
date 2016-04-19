#include "EffectFactory.hpp"
#include "Game.hpp"
#include "ItemIdentifier.hpp"
#include "MessageManager.hpp"
#include "ScrollReadStrategy.hpp"
#include "SpellcastingTextKeys.hpp"
#include "SpellFactory.hpp"
#include "SpellShapeProcessorFactory.hpp"
#include "SpellcastingProcessor.hpp"

using namespace std;

ActionCostValue ScrollReadStrategy::read(CreaturePtr creature, ActionManager * const am, ReadablePtr readable)
{
  ActionCostValue acv = 0;

  if (creature && readable)
  {
    EffectPtr spell_effect = EffectFactory::create_effect(readable->get_effect_type());
    
    if (spell_effect)
    {
      Game& game = Game::instance();
      MapPtr map = game.get_current_map();
      Coordinate caster_coord = map->get_location(creature->get_id());

      ItemIdentifier item_id;
      string base_id = readable->get_base_id();
      bool readable_originally_identified = item_id.get_item_identified(base_id);
      
      // Add a message about what's being read
      add_read_message(get_player_and_monster_read_sids(), creature, readable, item_id);
      
      // Destroy the item if applicable.
      if (readable->destroy_on_read())
      {
        readable->set_quantity(readable->get_quantity() - 1);
        if (readable->get_quantity() == 0) creature->get_inventory()->remove(readable->get_id());
      }

      Spell scroll_spell = SpellFactory::create_self_targetted_item_spell();
      scroll_spell.set_effect(readable->get_effect_type());

      SpellShapeProcessorPtr spell_processor = SpellShapeProcessorFactory::create_processor(scroll_spell.get_shape().get_spell_shape_type());
      bool effect_identified = false;

      if (spell_processor)
      {
        // Use the generic spell processor, which is also used for "regular"
        // spellcasting.
        SpellcastingProcessor sp;
        effect_identified = sp.process(spell_processor, creature, map, caster_coord, Direction::DIRECTION_NULL, scroll_spell, readable->get_status());
      }

      if (effect_identified && !readable_originally_identified)
      {
        item_id.set_item_identified(readable, base_id, true);
      }

      acv = get_action_cost_value(creature);
    }
  }

  return acv;
}

pair<string, string> ScrollReadStrategy::get_player_and_monster_read_sids() const
{
  pair<string, string> sids(SpellcastingTextKeys::SPELLCASTING_READ_SCROLL_PLAYER, SpellcastingTextKeys::SPELLCASTING_READ_SCROLL_MONSTER);
  return sids;
}

