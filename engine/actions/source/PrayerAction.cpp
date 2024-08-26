#include "ClassManager.hpp"
#include "Conversion.hpp"
#include "DeityDecisionStrategyFactory.hpp"
#include "DeityTextKeys.hpp"
#include "Game.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "PrayerAction.hpp"
#include "ReligionManager.hpp"
#include "StatisticsMarker.hpp"

using std::string;

PrayerAction::PrayerAction()
{
}

// Create the decision strategies surrounding prayer, based on the
// creature's chosen deity.
ActionCostValue PrayerAction::pray(CreaturePtr creature)
{
  if (creature)
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();
    MapType mt = MapType::MAP_TYPE_WORLD;

    if (map)
    {
      mt = map->get_map_type();
      IMessageManager& manager = MM::instance();

      if (mt == MapType::MAP_TYPE_WORLD)
      {
        manager.add_new_message(StringTable::get(DeityTextKeys::PRAYER_WORLD_MAP));
        manager.send();

        return 0;
      }
      else
      {
        // Is this a general map, but so far removed from the Nine that they cannot hear?
        if (map->has_property(MapProperties::MAP_PROPERTIES_CANNOT_PRAY))
        {
          if (String::to_bool(map->get_property(MapProperties::MAP_PROPERTIES_CANNOT_PRAY)))
          {
            manager.add_new_message(StringTable::get(DeityTextKeys::DEITY_CANNOT_PRAY));
            manager.send();
            
            return get_action_cost_value(creature);
          }
        }
      }
    }

    // Say the prayer.
    bool prayer_said = say_prayer(creature);
    
    if (prayer_said)
    {
      TilePtr creature_tile = MapUtils::get_tile_for_creature(game.get_current_map(), creature);

      ReligionManager rm;
      Deity* deity = rm.get_active_deity(creature);

      if (deity != nullptr)
      {
        // Decide on a course of action.
        IDeityDecisionStrategyPtr deity_decision_strategy = DeityDecisionStrategyFactory::create_deity_decision_strategy(deity->get_id());
        DeityDecisionStrategyHandlerPtr deity_decision_handler = deity_decision_strategy->get_decision(creature);

        // Act on that decision.
        DeityDecisionImplications decision_implications = deity_decision_handler->handle_decision(creature, creature_tile);

        // Reduce the piety and update the player on the result.
        finish_prayer(creature, decision_implications);

        // Break the Agnostic conduct.
        creature->get_conducts_ref().break_conduct(ConductType::CONDUCT_TYPE_AGNOSTIC);
      }
    }
  }

  return get_action_cost_value(creature);
}

// If the creature is the player, say a prayer (add a message).
bool PrayerAction::say_prayer(CreaturePtr creature)
{
  bool prayer_said = false;;

  if (creature && creature->get_is_player())
  {
    Game& game = Game::instance();
    IMessageManager& manager = MM::instance();

    if (game.do_deities_exist())
    {
      string prayer_message = StringTable::get(DeityTextKeys::PRAYER_GODLESS);

      if (!creature->is_godless())
      {
        ReligionManager rm;
        string deity_name_sid = rm.get_deity_name_sid(creature->get_religion().get_active_deity_id());
        prayer_message = DeityTextKeys::get_prayer_message(deity_name_sid);
        
        prayer_said = true;
      }

      manager.add_new_message(prayer_message);
      manager.send();
    }
    else
    {
      // Add a message about there being no gods.
      manager.add_new_message(StringTable::get(DeityTextKeys::PRAYER_NO_DEITIES));
      manager.send();
    }
  }

  return prayer_said;
}

// Reduce the piety by the given amount, and update the player on the result
void PrayerAction::finish_prayer(CreaturePtr creature, const DeityDecisionImplications& decision_implications)
{
  int piety_loss = decision_implications.get_piety_amount();

  // Get the deity and the creature's status with that deity.
  ReligionManager rm;
  ClassManager cm;
  
  Religion& religion = creature->get_religion_ref();
  string deity_id = religion.get_active_deity_id();
  DeityStatus status = religion.get_deity_status(deity_id);

  Class* cur_class = cm.get_class(creature->get_class_id());
  float piety_cost_multiplier = cur_class->get_piety_cost_multiplier();
  int piety_cost = static_cast<int>(piety_loss * piety_cost_multiplier);
  int initial_piety = status.get_piety();
  Game& game = Game::instance();

  status.decrement_piety(piety_cost);
  religion.set_deity_status(deity_id, status);
  
  if (creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();    
    string prayer_message = StringTable::get(decision_implications.get_message_sid());
    bool add_new_message_with_pause = decision_implications.get_add_message_with_pause();
    bool reload_map_music = decision_implications.get_reload_map_music();

    if (add_new_message_with_pause)
    {
      manager.add_new_message_with_pause(prayer_message);
      game.get_current_player()->get_decision_strategy()->get_confirmation();
    }
    else
    {
      manager.add_new_message(prayer_message);
    }

    manager.send();

    if (reload_map_music)
    {
      MapPtr map = game.get_current_map();
      SoundPtr sound = game.get_sound();
      sound->play_music(map);
    }
  }

  // If in the deity's good books, praying can increase charisma.
  if (initial_piety > 0)
  {
    StatisticsMarker sm;
    sm.mark_charisma(creature);
  }
}

ActionCostValue PrayerAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}
