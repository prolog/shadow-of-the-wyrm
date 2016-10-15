#include "WandcraftSkillProcessor.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "ItemManager.hpp"
#include "ItemTypes.hpp"

using namespace std;

WandcraftSkillProcessor::WandcraftSkillProcessor()
{
}

ActionCostValue WandcraftSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = -1;

  if (creature && map)
  {
    if (check_for_components(creature) &&
        check_for_spells(creature))
    {
      // ...
      acv = get_default_skill_action_cost_value(creature);
    }
  }

  return acv;
}

bool WandcraftSkillProcessor::check_for_components(CreaturePtr creature)
{
  bool has_comp = false;

  if (creature != nullptr)
  {
    IInventoryPtr inv = creature->get_inventory();

    if (inv &&
        ItemManager::has_item(creature, ItemIdKeys::ITEM_ID_BRANCH) &&
        ItemManager::has_item(creature, ItemIdKeys::ITEM_ID_MAGICI_SHARD))
    {
      has_comp = true;
    }
  }

  if (!has_comp && creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_WANDCRAFT_INSUFFICIENT_COMPONENTS));

    manager.send();
  }

  return has_comp;
}

// Only external magics can go into wands.
// External spells are beams, cones, storms, balls.  Ie, not self-targetting
// spells.
bool WandcraftSkillProcessor::check_for_spells(CreaturePtr creature)
{
  bool has_spells = false;

  if (creature != nullptr)
  {
    Game& game = Game::instance();
    const SpellMap& sm = game.get_spells_ref();
    SpellKnowledge& sk = creature->get_spell_knowledge_ref();
    SpellKnowledgeMap skm = sk.get_known_spells();

    for (const auto& skm_pair : skm)
    {
      string spell_id = skm_pair.first;

      const auto sm_it = sm.find(spell_id);
      if (sm_it != sm.end())
      {
        SpellShape ss = sm_it->second.get_shape();

        if (ss.get_is_external())
        {
          has_spells = true;
          break;
        }
      }
    }
  }

  if (!has_spells && creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_WANDCRAFT_NO_SPELLS));

    manager.send();
  }

  return has_spells;
}
ActionCostValue WandcraftSkillProcessor::get_default_skill_action_cost_value(CreaturePtr creature) const
{
  return 200;
}

