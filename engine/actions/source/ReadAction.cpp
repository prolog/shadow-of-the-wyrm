#include "ActionManager.hpp"
#include "ActionTextKeys.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "EffectFactory.hpp"
#include "Game.hpp"
#include "HostilityManager.hpp"
#include "ItemFilterFactory.hpp"
#include "MessageManagerFactory.hpp"
#include "ReadStrategyFactory.hpp"
#include "SpellcastingTextKeys.hpp"
#include "ItemIdentifier.hpp"
#include "MapUtils.hpp"
#include "MessageManager.hpp"
#include "ReadAction.hpp"

using namespace std;
using std::dynamic_pointer_cast;

// Read a scroll or spellbook.  Scrolls cast a single spell, while
// spellbooks contain spells, and can be used to learn an individual
// spell (the ADOM/nethack model, rather than Angband's/DCSS's).
ActionCostValue ReadAction::read(CreaturePtr creature, ActionManager * const am)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  CurrentCreatureAbilities cca;

  if (!cca.can_see(creature, true) ||
      !cca.can_read(creature, true) ||
      !cca.can_focus(creature, true) ||
      check_on_world_map(creature))
  {
    return action_cost_value;
  }

  if (creature && am)
  {
    list<IItemFilterPtr> display_list = ItemFilterFactory::create_readable_filter();
    ItemPtr selected_readable_item = am->inventory(creature, creature->get_inventory(), display_list, {}, false, true);
    
    if (selected_readable_item)
    {
      ReadablePtr readable = std::dynamic_pointer_cast<Readable>(selected_readable_item);
      return read(creature, readable);
    }    
  }

  return action_cost_value;
}

ActionCostValue ReadAction::read(CreaturePtr creature, const string& item_id)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr)
  {
    Game& game = Game::instance();
    ActionManager& am = game.get_action_manager_ref();
    ItemPtr item = creature->get_inventory()->get_from_id(item_id);
    ReadablePtr readable = std::dynamic_pointer_cast<Readable>(item);
    acv = read(creature, readable);
  }

  return acv;
}

ActionCostValue ReadAction::read(CreaturePtr creature, ReadablePtr readable)
{
  ActionCostValue action_cost_value = ActionCostConstants::DEFAULT;

  if (readable)
  {
    string text_sid = readable->get_text_sid();
    ReadStrategyPtr read_strategy = ReadStrategyFactory::create_read_strategy(readable->get_type(), text_sid);

    if (read_strategy)
    {
      Game& game = Game::instance();
      MapPtr map = game.get_current_map();

      // Cast or learn the spell from the scroll/spellbook/etc.
      action_cost_value = read_strategy->read(creature, readable);

      // Break the illiterate conduct.
      creature->get_conducts_ref().break_conduct(ConductType::CONDUCT_TYPE_ILLITERATE);

      // If we're in a shop, anger the shopkeeper.
      // Shops aren't libraries!
      if (readable->get_unpaid())
      {
        MapUtils::anger_shopkeeper_if_necessary(map->get_location(creature->get_id()), map, creature);
      }

      creature->get_skills().mark(SkillType::SKILL_GENERAL_LITERACY);
    }
  }

  return action_cost_value;
}

bool ReadAction::check_on_world_map(CreaturePtr creature)
{
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();

  if (creature && map && map->get_map_type() == MapType::MAP_TYPE_WORLD)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_READ_WORLD_MAP));
    manager.send();

    return true;
  }

  return false;
}

ActionCostValue ReadAction::get_action_cost_value(CreaturePtr /* creature */) const
{
  return 1;
}
