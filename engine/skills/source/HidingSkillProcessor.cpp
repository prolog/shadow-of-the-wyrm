#include "ActionTextKeys.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HidingSkillProcessor.hpp"
#include "HidingCalculator.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "SkillManager.hpp"
#include "StatusEffectFactory.hpp"

using std::string;

ActionCostValue HidingSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION_MENU;

  if (creature != nullptr)
  {
    // Using hiding when hidden reveals the creature.
    if (creature->has_status(StatusIdentifiers::STATUS_ID_HIDE))
    {
      StatusEffectPtr hide = StatusEffectFactory::create_status_effect(creature, StatusIdentifiers::STATUS_ID_HIDE, creature->get_id());

      if (hide != nullptr)
      {
        hide->undo_change(creature);
      }
    }
    else
    {
      HidingCalculator hc;
      bool is_player = creature->get_is_player();
      TimeOfDayType tod = TimeOfDayType::TIME_OF_DAY_UNDEFINED; 
      World* world = Game::instance().get_current_world();
      int hide_chance = hc.calculate_pct_chance_hide(creature, map, tod);
      CurrentCreatureAbilities cca;

      TilePtr tile = map->at(map->get_location(creature->get_id()));
      IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, is_player);

      if (tile != nullptr && tile->has_been_dug() && hc.gets_hole_bonus(creature))
      {
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_HIDE_HOLE));
      }

      if (world != nullptr)
      {
        tod = world->get_calendar().get_date().get_time_of_day();
      }

      if (!cca.can_see(creature, true))
      {
        // Do nothing, a message will already have been added by cca.
      }
      else if (RNG::percent_chance(hide_chance))
      {
        StatusEffectPtr hide = StatusEffectFactory::create_status_effect(creature, StatusIdentifiers::STATUS_ID_HIDE, creature->get_id());

        if (hide != nullptr)
        {
          hide->apply_change(creature, creature->get_level().get_current());
        }
      }
      else
      {
        string message = ActionTextKeys::get_hide_failure_message(creature->get_description_sid(), is_player);
        manager.add_new_message(message);
        manager.send();
      }

      if (hide_chance < 100)
      {
        SkillManager sm;
        sm.mark_skill_with_probability(25, creature, SkillType::SKILL_GENERAL_HIDING, true);
      }

      acv = get_default_skill_action_cost_value(creature);
    }
  }

  return acv;
}

SkillProcessorPtr HidingSkillProcessor::clone()
{
  SkillProcessorPtr proc = std::make_unique<HidingSkillProcessor>();
  return proc;
}
