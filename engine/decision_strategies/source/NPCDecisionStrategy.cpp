#include "CoordUtils.hpp"
#include "Commands.hpp"
#include "CommandCustomValues.hpp"
#include "Conversion.hpp"
#include "CreatureTileSafetyChecker.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DecisionScript.hpp"
#include "Game.hpp"
#include "NPCDecisionStrategy.hpp"
#include "NPCMagicDecisionFactory.hpp"
#include "RNG.hpp"
#include "SearchStrategyFactory.hpp"

using namespace std;

const int NPCDecisionStrategy::PERCENT_CHANCE_ADVANCE_TOWARDS_TARGET = 85;
const int NPCDecisionStrategy::PERCENT_CHANCE_CONSIDER_USING_MAGIC = 75;

NPCDecisionStrategy::NPCDecisionStrategy(ControllerPtr new_controller)
: DecisionStrategy(new_controller)
{
}

// By default, always get/pick up/etc the maximum.
uint NPCDecisionStrategy::get_count(const uint max_count)
{
  return max_count;
}

bool NPCDecisionStrategy::get_confirmation(const bool confirmation_default_value)
{
  return true;
}

// The basic decision structure for NPCs.  The individual get_decision_for functions are pure virtual within this class,
// and implemented by concrete decision strategies.
CommandPtr NPCDecisionStrategy::get_nonmap_decision(const bool reprompt_on_cmd_not_found, const string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, int* key_p)
{
  MapPtr nullmap;
  return get_decision(reprompt_on_cmd_not_found, this_creature_id, command_factory, keyboard_commands, nullmap, key_p);
}

CommandPtr NPCDecisionStrategy::get_decision(const bool reprompt_on_cmd_not_found, const string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, MapPtr view_map, int* key_p)
{
  CommandPtr command;
  
  CommandFactoryType factory_type = command_factory->get_factory_type();
  
  switch(factory_type)
  {
    case CommandFactoryType::COMMAND_FACTORY_TYPE_MAP:
      command = get_decision_for_map(this_creature_id, command_factory, keyboard_commands, view_map);
      break;
    case CommandFactoryType::COMMAND_FACTORY_TYPE_INVENTORY:
      command = get_decision_for_inventory(command_factory, keyboard_commands);
      break;
    case CommandFactoryType::COMMAND_FACTORY_TYPE_EQUIPMENT:
      command = get_decision_for_equipment(command_factory, keyboard_commands);
      break;
    case CommandFactoryType::COMMAND_FACTORY_TYPE_SELECT_TILE:
      command = get_decision_for_tile_selection(command_factory, keyboard_commands);
      break;
    default:
      break;
  }

  return command;
}

CommandPtr NPCDecisionStrategy::get_decision_for_map(const std::string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, MapPtr view_map)
{
  CommandPtr command;
  
  if (view_map)
  {
    // If the creature has any spells, consider casting a spell, based on
    // low health, nearby hostile creatures, etc.
    command = get_magic_decision(this_creature_id, view_map);

    // Attack if threatened.
    if (command == nullptr)
    {
      command = get_attack_decision(this_creature_id, view_map);
    }

    // If not threatened, try a custom (script-based) decision.
    if (command == nullptr)
    {
      command = get_custom_decision(this_creature_id, view_map);
    }
    
    // If no custom decisions fired, attempt movement.
    if (command == nullptr && can_move())
    {
      command = get_movement_decision(this_creature_id);
    }    
  }

  // If we can't move, or there are no adjacent coordinates to which the NPC can move,
  // the command will be a search command - that can always be done, and will always
  // advance to the next turn.
  if (!command)
  {
    command = std::make_shared<SearchCommand>(-1);
  }
  
  return command;
}

// Decide whether or not to cast a spell.
CommandPtr NPCDecisionStrategy::get_magic_decision(const string& this_creature_id, MapPtr view_map)
{
  CommandPtr magic_command;
  INPCMagicDecisionPtr npc_magic_decision;

  if (view_map != nullptr)
  {
    CreaturePtr creature = view_map->get_creature(this_creature_id);
    CurrentCreatureAbilities cca;
    Game& game = Game::instance();
    const SpellMap& spell_map = game.get_spells_ref();
    const set<string> creature_threats = threat_ratings.get_all_threats_without_level();
    std::vector<std::pair<std::string, Direction>> potential_spells;

    if (creature != nullptr && cca.can_speak(creature))
    {
      SpellKnowledge& sk = creature->get_spell_knowledge_ref();

      if (sk.get_knows_spells() && RNG::percent_chance(PERCENT_CHANCE_CONSIDER_USING_MAGIC))
      {
        SpellKnowledgeMap skm = sk.get_spell_knowledge_map();

        for (const auto& skm_pair : skm)
        {
          const auto& s_it = spell_map.find(skm_pair.first);

          if (s_it != spell_map.end())
          {
            const Spell& spell = s_it->second;

            // Only consider the spell if the creature actually has enough
            // AP to cast it!
            if (spell.get_ap_cost() <= static_cast<uint>(creature->get_arcana_points().get_current()))
            {
              npc_magic_decision = NPCMagicDecisionFactory::create_npc_magic_decision(spell.get_magic_classification());

              if (npc_magic_decision != nullptr)
              {
                pair<bool, Direction> decision_details = npc_magic_decision->decide(creature, view_map, spell, creature_threats);

                if (npc_magic_decision && decision_details.first)
                {
                  potential_spells.push_back(make_pair(spell.get_spell_id(), decision_details.second));
                }
              }
            }
          }
        }
      }
    }

    if (potential_spells.size() > 0)
    {
      std::shuffle(potential_spells.begin(), potential_spells.end(), RNG::get_engine());
      pair<string, Direction> spell_to_cast = potential_spells.at(0);

      // Create the spell command, adding properties to set the spell details.
      magic_command = make_shared<CastSpellCommand>(-1);
      magic_command->set_custom_value(CommandCustomValues::COMMAND_CUSTOM_VALUES_SELECTED_SPELL_ID, spell_to_cast.first);
      magic_command->set_custom_value(CommandCustomValues::COMMAND_CUSTOM_VALUES_DIRECTION, to_string(static_cast<int>(spell_to_cast.second)));
    }
  }

  return magic_command;
}

// Get the decision for what to attack.
CommandPtr NPCDecisionStrategy::get_attack_decision(const string& this_creature_id, MapPtr view_map)
{
  CommandPtr no_attack;

  // Iterate through the threats in order of threatiness
  ThreatMap threat_map = threat_ratings.get_all_threats();
  ThreatMap::const_reverse_iterator t_it = threat_map.rbegin();
  
  if (view_map != nullptr)
  {
    Coordinate c_this = view_map->get_location(this_creature_id);
    TilePtr this_tile = view_map->at(c_this);

    if (this_tile != nullptr)
    {
      CreaturePtr this_cr = this_tile->get_creature();

      while (t_it != threat_map.rend())
      {
        set<string> creature_ids = t_it->second;

        for (const string& threatening_creature_id : creature_ids)
        {
          // Check the view map to see if the creature exists
          if (view_map->has_creature(threatening_creature_id))
          {
            // Check if adjacent to this_creature_id
            Coordinate c_threat = view_map->get_location(threatening_creature_id);

            if (CoordUtils::are_coordinates_adjacent(c_this, c_threat))
            {
              Direction direction = CoordUtils::get_direction(c_this, c_threat);

              // create movement command, return.
              CommandPtr command = std::make_shared<AttackCommand>(direction, -1);
              return command;
            }
            else
            {
              // If the creature is hostile, and the target is generally far away,
              // advance towards the target, but only do so with a certain
              // probability, to allow for other actions (script decisions, etc).
              if (can_move() && RNG::percent_chance(PERCENT_CHANCE_ADVANCE_TOWARDS_TARGET) && this_cr != nullptr)
              {
                SearchStrategyPtr ss = SearchStrategyFactory::create_search_strategy(SearchType::SEARCH_TYPE_UNIFORM_COST, this_cr); // JCD FIXME WAS BFS...
                Direction direction = CoordUtils::get_direction(c_this, ss->search(view_map, c_this, c_threat));

                if (direction != Direction::DIRECTION_NULL)
                {
                  CommandPtr command = std::make_shared<MovementCommand>(direction, -1);
                  return command;
                }
              }
            }
          }
        }

        // Try the next threat level.
        t_it++;
      }
    }
  }
  
  return no_attack;
}

// Get a custom decision (script-based)
CommandPtr NPCDecisionStrategy::get_custom_decision(const string& this_creature_id, MapPtr view_map)
{
  CommandPtr command;

  if (view_map != nullptr)
  {
    CreaturePtr creature = view_map->get_creature(this_creature_id);

    if (creature != nullptr)
    {
      ScriptDetails decision_script_details = creature->get_event_script(CreatureEventScripts::CREATURE_EVENT_SCRIPT_DECISION);
      string decision_script = decision_script_details.get_script();

      if (!decision_script.empty() && RNG::percent_chance(decision_script_details.get_chance()))
      {
        Game& game = Game::instance();
        ScriptEngine& se = game.get_script_engine_ref();
        DecisionScript ds;

        ActionCostValue acv = ds.execute(se, decision_script, creature);
        if (acv > 0)
        {
          command = std::make_shared<CustomScriptCommand>();
          command->set_custom_value(CommandCustomValues::COMMAND_CUSTOM_VALUES_ACTION_COST_VALUE, std::to_string(acv));
        }
      }
    }
  }

  return command;
}

// Get the decision for where to move.
// Move stupidly (randomly) when no threat is present.
CommandPtr NPCDecisionStrategy::get_movement_decision(const string& this_creature_id)
{   
  CommandPtr movement_command;

  Game& game = Game::instance();
  
  MapPtr current_map = game.get_current_map();

  if (current_map != nullptr)
  {
    Dimensions current_dimensions = current_map->size();
    Coordinate this_creature_coords = current_map->get_location(this_creature_id);
    TilePtr this_creature_tile = current_map->at(this_creature_coords);
    CreaturePtr this_creature = this_creature_tile->get_creature();

    int this_row = this_creature_coords.first;
    int this_col = this_creature_coords.second;

    vector<Coordinate> adjacent_coordinates = CoordUtils::get_adjacent_map_coordinates(current_dimensions, this_row, this_col);
    vector<Coordinate> choice_coordinates = get_adjacent_safe_coordinates_without_creatures(current_map, adjacent_coordinates, this_creature);

    // Pick a tile if not empty
    if (!choice_coordinates.empty())
    {
      Coordinate movement_coord = choice_coordinates.at(RNG::range(0, choice_coordinates.size() - 1));
      Direction direction = CoordUtils::get_direction(this_creature_coords, movement_coord);
      movement_command = std::make_shared<MovementCommand>(direction, -1);
    }
  }

  return movement_command;
}

// Get a list of the adjacent coordinates that do not contain creatures
vector<Coordinate> NPCDecisionStrategy::get_adjacent_safe_coordinates_without_creatures(MapPtr current_map, const vector<Coordinate>& all_adjacent_coordinates, CreaturePtr this_creature)
{
  CreatureTileSafetyChecker safety_checker;
  vector<Coordinate> coords_without_creatures;
  
  for (const Coordinate& c : all_adjacent_coordinates)
  {
    // Don't move if there's a creature on that coordinate.
    TilePtr adjacent_tile = current_map->at(c.first, c.second);

    if (adjacent_tile != nullptr)
    {
      if (adjacent_tile->has_creature() || (!safety_checker.is_tile_safe_for_creature(this_creature, adjacent_tile)))
      {
        continue;
      }
      else
      {
        coords_without_creatures.push_back(c);
      }
    }
  }
  
  return coords_without_creatures;
}

