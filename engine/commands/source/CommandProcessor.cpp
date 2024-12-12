#include "CommandKeys.hpp"
#include "CommandProcessor.hpp"
#include "Commands.hpp"
#include "CommandCustomValues.hpp"
#include "Conversion.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "ItemFilterFactory.hpp"
#include "Log.hpp"
#include "RNG.hpp"
#include "TextMessages.hpp"

using namespace std;

CommandProcessor::CommandProcessor()
{
}

CommandProcessor::~CommandProcessor()
{
}

// Determine the type of command, and process it appropriately.
ActionCost CommandProcessor::process(CreaturePtr creature, Command* command, DisplayPtr display)
{  
  ActionCost ac;

  if (command)
  {
    DirectionalCommand* d_command = dynamic_cast<DirectionalCommand*>(command);

    if (d_command && !(d_command->get_direction() == Direction::DIRECTION_NULL) /* search is a special case */)
    {
      return process_directional_command(creature, d_command, display);
    } 
    else
    {
      // It's a subclass of the basic command, but not one of the subclasses requiring special processing.
      return process_command(creature, command, display);
    }
  }

  return ac;
}

// Process the Command
ActionCost CommandProcessor::process_command(CreaturePtr creature, Command* command, DisplayPtr display)
{
  ActionCost ac;
  
  if (command)
  {
    bool confirm = process_confirmation(creature, command, display);
    
    if (confirm)
    {
      Game& game = Game::instance();
      string command_name = command->get_name();
      
      if (command_name == CommandKeys::QUIT)
      {
        ac = game.actions.quit(creature);
      }
      else if (command_name == CommandKeys::VERSION)
      {
        ac = game.actions.version(creature);
      }
      else if (command_name == CommandKeys::GAME_DATE_TIME_WEATHER)
      {
        ac = game.actions.date_and_time(creature);
      }
      else if (command_name == CommandKeys::SEARCH)
      {
        ac = game.actions.search(creature);
      }
      else if (command_name == CommandKeys::MOVE_UP)
      {
        ac = game.actions.ascend(creature);
      }
      else if (command_name == CommandKeys::MOVE_DOWN)
      {
        ac = game.actions.descend(creature);
      }
      else if (command_name == CommandKeys::AUTOMATIC_MOVEMENT)
      {
        ac = game.actions.automatic_movement(creature);
      }
      else if (command_name == CommandKeys::PICK_UP_ITEM)
      {
        ac = process_pick_up_command(creature, command, game);
      }
      else if (command_name == CommandKeys::PICK_UP_ALL)
      {
        ac = game.actions.pick_up(creature, PickUpType::PICK_UP_ALL);
      }
      else if (command_name == CommandKeys::DROP_ITEM)
      {
        ac = process_drop_command(creature, command, game);
      }
      else if (command_name == CommandKeys::CHAR_DETAILS)
      {
        ac = game.actions.display_character(creature);
      }
      else if (command_name == CommandKeys::CHAR_DUMP)
      {
        ac = game.actions.dump_character(creature);
      }
      else if (command_name == CommandKeys::INVENTORY)
      {
        ac = process_inventory_command(creature, command, game);
      }
      else if (command_name == CommandKeys::PRAY)
      {
        ac = game.actions.pray(creature);
      }
      else if (command_name == CommandKeys::MELEE_WEAPON_INFO)
      {
        ac = game.actions.weapon_info(creature, WeaponStyle::WEAPON_STYLE_MELEE);
      }
      else if (command_name == CommandKeys::RANGED_WEAPON_INFO)
      {
        ac = game.actions.weapon_info(creature, WeaponStyle::WEAPON_STYLE_RANGED);
      }
      else if (command_name == CommandKeys::SELECT_TILE)
      {
        ac = game.actions.select_tile(creature);
      }
      else if (command_name == CommandKeys::FIRE_MISSILE)
      {
        string skip_targetting_s = command->get_custom_value(CommandCustomValues::COMMAND_CUSTOM_VALUES_SKIP_TARGETTING);
        bool skip_targetting = false;

        if (!skip_targetting_s.empty())
        {
          skip_targetting = String::to_bool(skip_targetting_s);
        }

        ac = game.actions.fire_missile(creature, skip_targetting);
      }
      else if (command_name == CommandKeys::QUAFF)
      {
        ac = game.actions.quaff(creature);
      }
      else if (command_name == CommandKeys::READ)
      {
        ac = process_read_command(creature, command, game);
      }
      else if (command_name == CommandKeys::CHECK_CURRENCY)
      {
        ac = game.actions.check_currency(creature);
      }
      else if (command_name == CommandKeys::SAVE_GAME)
      {
        ac = game.actions.save(creature, true);
      }
      else if (command_name == CommandKeys::EAT)
      {
        ac = game.actions.eat(creature);
      }
      else if (command_name == CommandKeys::CHAT)
      {
        ac = game.actions.chat(creature);
      }
      else if (command_name == CommandKeys::APPLY_FEATURE)
      {
        ac = game.actions.apply(creature);
      }
      else if (command_name == CommandKeys::QUEST_LIST)
      {
        ac = game.actions.quest_list(creature);
      }
      else if (command_name == CommandKeys::RELOAD_SCRIPTS_ASSETS_AND_SIDS)
      {
        ac = game.actions.reload_scripts_assets_and_sids(creature);
      }
      else if (command_name == CommandKeys::RUN_SCRIPT)
      {
        ac = game.actions.run_script_command(creature);
      }
      else if (command_name == CommandKeys::CAST_SPELL)
      {
        ac = process_spell_casting_command(creature, command, game);
      }
      else if (command_name == CommandKeys::BESTIARY)
      {
        string prompt_for_creature;
        ac = game.actions.bestiary(creature, prompt_for_creature);
      }
      else if (command_name == CommandKeys::EVOKE)
      {
        ac = process_evoke_command(creature, command, game);
      }
      else if (command_name == CommandKeys::SHOW_RESISTANCES)
      {
        ac = game.actions.show_resistances(creature);
      }
      else if (command_name == CommandKeys::SHOW_CONDUCTS)
      {
        ac = game.actions.show_conducts(creature);
      }
      else if (command_name == CommandKeys::SHOW_SKILLS)
      {
        ac = game.actions.show_skills(creature, SkillsSelectionType::SKILLS_SELECTION_SELECT_SKILL);
      }
      else if (command_name == CommandKeys::LATEST_MESSAGES)
      {
        ac = game.actions.latest_messages(creature);
      }
      else if (command_name == CommandKeys::KICK)
      {
        ac = game.actions.kick(creature);
      }
      else if (command_name == CommandKeys::OFFER)
      {
        ac = game.actions.offer(creature);
      }
      else if (command_name == CommandKeys::SKIN)
      {
        ac = game.actions.skin(creature);
      }
      else if (command_name == CommandKeys::PIETY)
      {
        ac = game.actions.piety(creature);
      }
      else if (command_name == CommandKeys::EXPERIENCE)
      {
        ac = game.actions.experience(creature);
      }
      else if (command_name == CommandKeys::CUSTOM_SCRIPT_COMMAND)
      {
        // All the actions have already been done.
        // Get the custom action cost value, and then use it to
        // update the action coordinator appropriately.
        string custom_acv = command->get_custom_value(CommandCustomValues::COMMAND_CUSTOM_VALUES_ACTION_COST_VALUE);

        if (custom_acv.empty())
        {
          Log::instance().error("Custom script command indicated, but no action cost value provided!");
        }
        else
        {
          ac = game.actions.get_action_cost(creature, String::to_int(custom_acv));
        }
      }
      else if (command_name == CommandKeys::REST)
      {
        ac = game.actions.rest(creature);
      }
      else if (command_name == CommandKeys::VIEW_ITEMS)
      {
        list<IItemFilterPtr> empty_filter = ItemFilterFactory::create_empty_filter();
        game.actions.inventory(creature, creature->get_inventory(), empty_filter, {}, true, false);
      }
      else if (command_name == CommandKeys::HELP)
      {
        ac = game.actions.help(creature);
      }
      else if (command_name == CommandKeys::INSCRIBE)
      {
        ac = game.actions.inscribe(creature);
      }
      else if (command_name == CommandKeys::AUTOMATIC_ACTIONS)
      {
        ac = game.actions.automatic_actions(creature);
      }
      else if (command_name == CommandKeys::SOUND_ACTIONS)
      {
        ac = game.actions.sound_actions(creature);
      }
      else if (command_name == CommandKeys::BREED)
      {
        ac = game.actions.breed(creature);
      }
      else if (command_name == CommandKeys::ITEM_CODEX)
      {
        ac = game.actions.item_codex(creature);
      }
      else if (command_name == CommandKeys::SWITCH_GRAPHICS_MODE)
      {
        ac = game.actions.switch_graphics_mode(creature);
      }
      else if (command_name == CommandKeys::SWITCH_COLOUR_PALETTES)
      {
        ac = game.actions.switch_colour_palettes(creature);
      }
      else if (command_name == CommandKeys::TOGGLE_WINDOW_MODE)
      {
        ac = game.actions.toggle_window_mode(creature);
      }
      else if (command_name == CommandKeys::ORDER)
      {
        ac = game.actions.order(creature);
      }
    }
  }
  
  return ac;
}

// Process a spell casting command.
ActionCost CommandProcessor::process_spell_casting_command(CreaturePtr creature, Command* command, Game& game)
{
  // Get the spell ID and direction out of the command's properties.
  // These will be present when an NPC is casting the spell.
  string sp_id = command->get_custom_value(CommandCustomValues::COMMAND_CUSTOM_VALUES_SELECTED_SPELL_ID);
  string direction_s = command->get_custom_value(CommandCustomValues::COMMAND_CUSTOM_VALUES_DIRECTION);
  Direction dir = Direction::DIRECTION_NULL;

  if (!direction_s.empty())
  {
    dir = static_cast<Direction>(String::to_int(direction_s));
  }

  return game.actions.cast_spell(creature, sp_id, dir);
}

// Process the DirectionalCommand
ActionCost CommandProcessor::process_directional_command(CreaturePtr creature, DirectionalCommand* command, DisplayPtr display)
{
  ActionCost ac;
  
  if (command)
  {
    Game& game = Game::instance();
    string command_name = command->get_name();
    Direction direction = command->get_direction();
    CurrentCreatureAbilities cca;

    if (!cca.can_select_movement_direction(creature, true))
    {
      // If the creature is stunned, intercept the direction before the game
      // even decides whether to move or attack, and change the direction to
      // something random.  There is a 25% chance the creature gets to keep
      // its decided direction.
      if (RNG::percent_chance(75))
      {
        direction = static_cast<Direction>(RNG::range(static_cast<int>(Direction::DIRECTION_SOUTH_WEST), static_cast<int>(Direction::DIRECTION_NORTH_EAST)));
      }
    }

    if (CommandKeys::is_movement_type_key(command_name))
    {
      return game.actions.move(creature, direction);
    }
    else if (CommandKeys::is_attack_type_key(command_name))
    {
      return game.actions.attack(creature, direction);
    }
    else if (command_name == CommandKeys::KICK)
    {
      return game.actions.kick(creature, direction);
    }
  }
  
  return ac;
}

ActionCost CommandProcessor::process_pick_up_command(CreaturePtr creature, Command* command, Game& game)
{
  ActionCost ac;
  PickUpCommand* pu_cmd = dynamic_cast<PickUpCommand*>(command);

  if (pu_cmd != nullptr)
  {
    string item_id = pu_cmd->get_item_id();

    if (!item_id.empty())
    {
      ac = game.actions.pick_up(creature, item_id);
    }
    else
    {
      ac = game.actions.pick_up(creature, PickUpType::PICK_UP_SINGLE);
    }
  }

  return ac;
}

ActionCost CommandProcessor::process_drop_command(CreaturePtr creature, Command* command, Game& game)
{
  ActionCost ac;
  DropCommand* drop_cmd = dynamic_cast<DropCommand*>(command);

  if (drop_cmd != nullptr)
  {
    string drop_id = drop_cmd->get_drop_id();

    if (!drop_id.empty())
    {
      ac = game.actions.drop(creature, drop_id);
    }
    else
    {
      ac = game.actions.drop(creature);
    }
  }

  return ac;
}

ActionCost CommandProcessor::process_evoke_command(CreaturePtr creature, Command* command, Game& game)
{
  ActionCost ac;
  EvokeCommand* ev_cmd = dynamic_cast<EvokeCommand*>(command);

  if (ev_cmd != nullptr)
  {
    string item_id = ev_cmd->get_item_id();
    Direction direction = ev_cmd->get_direction();

    if (!item_id.empty())
    {
      ac = game.actions.evoke(creature, item_id, direction);
    }
    else
    {
      ac = game.actions.evoke(creature);
    }
  }

  return ac;
}

ActionCost CommandProcessor::process_inventory_command(CreaturePtr creature, Command* command, Game& game)
{
  ActionCost ac;
  InventoryCommand* inv_cmd = dynamic_cast<InventoryCommand*>(command);

  if (inv_cmd != nullptr)
  {
    ItemPtr i = inv_cmd->get_item();
    EquipmentWornLocation ewl = inv_cmd->get_equipment_worn_location();

    if (i != nullptr && ewl != EquipmentWornLocation::EQUIPMENT_WORN_NONE)
    {
      ac = game.actions.equipment(creature, i, ewl);
    }
    else
    {
      ac = game.actions.equipment(creature);
    }
  }

  return ac;
}

ActionCost CommandProcessor::process_read_command(CreaturePtr creature, Command* command, Game& game)
{
  ActionCost ac;
  ReadCommand* read_cmd = dynamic_cast<ReadCommand*>(command);

  if (read_cmd != nullptr)
  {
    string item_id = read_cmd->get_item_id();
    ac = game.actions.read(creature, item_id);
  }

  return ac;
}

// Get a confirmation from the creature's decision strategy, if necessary
bool CommandProcessor::process_confirmation(CreaturePtr creature, Command* command, DisplayPtr display)
{
  bool confirm = true;
  
  if (command && command->requires_confirmation())
  {
    if (creature->get_is_player())
    {
      display->confirm(TextMessages::get_confirmation_message(command->get_confirmation_sid()));
    }
    
    confirm = creature->get_decision_strategy()->get_confirmation();
    
    if (creature->get_is_player())
    {
      display->clear_messages();
    }
  }
  
  return confirm;
}
