#include "ActionTextKeys.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HidingSkillProcessor.hpp"
#include "HidingCalculator.hpp"
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
      TimeOfDayType tod = TimeOfDayType::TIME_OF_DAY_UNDEFINED; 
      World* world = Game::instance().get_current_world();
      int hide_chance = hc.calculate_pct_chance_hide(creature, map, tod);
      CurrentCreatureAbilities cca;

      TilePtr tile = map->at(map->get_location(creature->get_id()));

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
          // Because Hiding is potentially triggered every turn, hide the
          // application message, so this won't be relentlessly spammy to the
          // player.
          hide->set_show_application_message(false);
          hide->apply_change(creature, creature->get_level().get_current());
        }
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
