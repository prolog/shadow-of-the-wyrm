#include "ActionTextKeys.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "SearchAction.hpp"
#include "SkillManager.hpp"

using namespace std;

SearchAction::SearchAction()
{
}

ActionCostValue SearchAction::search(CreaturePtr creature)
{
  if (creature && creature->get_is_player())
  {
    MapPtr current_map = Game::instance().get_current_map();
    IMessageManager& manager = MM::instance();
    CurrentCreatureAbilities cca;
    SkillManager sm;

    string search_message;
    int found_hidden_cnt = 0;

    if (cca.can_see(creature))
    {
      search_message = StringTable::get(ActionTextKeys::ACTION_SEARCH);

      vector<TilePtr> adjacent_tiles = MapUtils::get_adjacent_tiles_to_creature_unsorted(current_map, creature);

      for (TilePtr a_tile : adjacent_tiles)
      {
        if (a_tile != nullptr)
        {
          if (a_tile->has_feature())
          {
            FeaturePtr feature = a_tile->get_feature();

            if (feature->get_is_hidden() && sm.check_skill(creature, SkillType::SKILL_GENERAL_DETECTION))
            {
              feature->set_is_hidden(false);
              found_hidden_cnt++;
            }
          }
        }
      }
    }
    else
    {
      search_message = StringTable::get(ActionTextKeys::ACTION_SEARCH_BLIND);
    }

    manager.add_new_message(search_message);
    manager.send();

    if (found_hidden_cnt == 1)
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SEARCH_FOUND));
      manager.send();
    }
    else if (found_hidden_cnt > 1)
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SEARCH_FOUND_MULTIPLE));
      manager.send();
    }
  }
  
  return get_action_cost_value(creature);
}

ActionCostValue SearchAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}
