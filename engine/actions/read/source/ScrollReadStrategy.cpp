#include "Conversion.hpp"
#include "EffectFactory.hpp"
#include "Game.hpp"
#include "ItemIdentifier.hpp"
#include "ItemProperties.hpp"
#include "MessageManager.hpp"
#include "ScrollReadStrategy.hpp"
#include "SpellcastingTextKeys.hpp"
#include "SpellFactory.hpp"
#include "SpellShapeProcessorFactory.hpp"
#include "SpellcastingProcessor.hpp"
#include "StatisticsMarker.hpp"

using namespace std;

ActionCostValue ScrollReadStrategy::read(CreaturePtr creature, ReadablePtr readable)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature && readable)
  {
    EffectPtr spell_effect = EffectFactory::create_effect(readable->get_effect_type(), {}, {}, "", creature->get_id());
    
    if (spell_effect)
    {
      Game& game = Game::instance();
      MapPtr map = game.get_current_map();
      Coordinate caster_coord = map->get_location(creature->get_id());

      ItemIdentifier item_id;
      string base_id = readable->get_base_id();
      bool readable_originally_identified = item_id.get_item_identified(base_id);
            
      // Destroy the item if applicable.
      if (readable->destroy_on_read())
      {
        readable->set_quantity(readable->get_quantity() - 1);
        if (readable->get_quantity() == 0) creature->get_inventory()->remove(readable->get_id());
      }

      Spell scroll_spell = SpellFactory::create_self_targetted_item_spell();
      scroll_spell.set_effect(readable->get_effect_type());
      scroll_spell.set_modifier(readable->get_modifier());

      SpellShapeProcessorPtr spell_processor = SpellShapeProcessorFactory::create_processor(scroll_spell.get_shape().get_spell_shape_type());
      bool effect_identified = false;

      if (spell_processor != nullptr)
      {
        Game::instance().get_sound()->play(SoundEffectID::SPELL);

        // Use the generic spell processor, which is also used for "regular"
        // spellcasting.
        SpellcastingProcessor sp;
        effect_identified = sp.process(spell_processor.get(), creature, map, caster_coord, Direction::DIRECTION_NULL, scroll_spell, 0, readable->get_status(), AttackType::ATTACK_TYPE_MAGICAL);
      }

      add_read_message(get_player_and_monster_read_sids(), creature, readable, item_id);

      if (effect_identified && !readable_originally_identified)
      {
        item_id.set_item_identified(creature, readable, base_id, true);
      }

      // Reading scrolls trains intelligence.
      StatisticsMarker sm;
      sm.mark_intelligence(creature);

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

