#include "ThieverySkillProcessor.hpp"
#include "ActionTextKeys.hpp"
#include "Commands.hpp"
#include "CommandFactory.hpp"
#include "Conversion.hpp"
#include "CreatureDescriber.hpp"
#include "CreatureProperties.hpp"
#include "CreatureUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "HostilityManager.hpp"
#include "ItemEnchantmentCalculator.hpp"
#include "ItemGenerationManager.hpp"
#include "ItemIdentifier.hpp"
#include "KeyboardCommandMap.hpp"
#include "MapUtils.hpp"
#include "RaceManager.hpp"
#include "RNG.hpp"
#include "SkillManager.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "ThieveryCalculator.hpp"

using namespace std;

ThieverySkillProcessor::ThieverySkillProcessor()
{
}

ActionCostValue ThieverySkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION_MENU;

  if (creature && map)
  {
    // Redraw the main map so any prompts don't look odd.
    Game& game = Game::instance();
    game.update_display(creature, game.get_current_map(), creature->get_decision_strategy()->get_fov_map(), false);
    pair<bool, TileDirectionMap> adj_creatures_pair = check_for_adjacent_creatures(creature, map);

    if (adj_creatures_pair.first && !adj_creatures_pair.second.empty())
    {
      CreaturePtr steal_creature = get_steal_creature(adj_creatures_pair.second, creature, map);

      if (steal_creature != nullptr)
      {
        acv = process_steal(creature, steal_creature, map);
      }
    }
  }

  return acv;
}

SkillProcessorPtr ThieverySkillProcessor::clone()
{
  SkillProcessorPtr proc = std::make_unique<ThieverySkillProcessor>();
  return proc;
}

// Check to see if there are any creature, hostile or not, that are adjacent
// to the given creature.
pair<bool, TileDirectionMap> ThieverySkillProcessor::check_for_adjacent_creatures(CreaturePtr creature, MapPtr map)
{
  pair<bool, TileDirectionMap> result;
  TileDirectionMap tdm;

  if (creature != nullptr && map != nullptr)
  {
    tdm = MapUtils::get_adjacent_tiles_to_creature(map, creature);

    for (const auto& tile_pair : tdm)
    {
      TilePtr tile = tile_pair.second;

      if (tile != nullptr && tile->has_creature())
      {
        result.first = true;
        result.second.insert(tile_pair);
      }
    }
  }

  if (!result.first && creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_THIEVERY_NO_TARGETS));
    manager.send();
  }

  return result;
}

// Get the creature to steal from.  When there is only one adjacent creature,
// use that.  Otherwise, prompt which to steal from.
CreaturePtr ThieverySkillProcessor::get_steal_creature(const TileDirectionMap& tdm, CreaturePtr creature, MapPtr map)
{
  size_t tdm_sz = tdm.size();
  CreaturePtr steal_creature;
  TilePtr steal_tile;

  if (tdm_sz == 1)
  {
    steal_tile = tdm.begin()->second;

    if (steal_tile)
    {
      steal_creature = steal_tile->get_creature();
    }
  }
  else
  {
    CommandFactoryPtr command_factory = std::make_unique<CommandFactory>();
    KeyboardCommandMapPtr kb_command_map = std::make_unique<KeyboardCommandMap>();

    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_GET_DIRECTION));
    manager.send();

    CommandPtr base_command = creature->get_decision_strategy()->get_nonmap_decision(false, creature->get_id(), command_factory.get(), kb_command_map.get(), 0, true);

    if (base_command)
    {
      // Check to see if it's an actual directional command
      DirectionalCommand* dcommand;
      dcommand = dynamic_cast<DirectionalCommand*>(base_command.get());

      if (dcommand)
      {
        TilePtr tile = MapUtils::get_adjacent_tile(map, creature, dcommand->get_direction());

        if (tile && tile->has_creature())
        {
          steal_creature = tile->get_creature();
        }
      }
    }
  }

  return steal_creature;
}

// Process the steal: first check to see if the creature we're trying to steal
// from is the stealing creature, and if not, to the necessary checks to see
// if the thievery was successful.
ActionCostValue ThieverySkillProcessor::process_steal(CreaturePtr stealing_creature, CreaturePtr steal_creature, MapPtr map)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION_MENU;

  IMessageManager& manager = MM::instance(MessageTransmit::FOV, steal_creature, steal_creature && steal_creature->get_is_player());
  CreatureDescriber cd(stealing_creature, steal_creature, true);

  // Used for only sending messages the player should see.
  IMessageManager& pl_manager = MM::instance(MessageTransmit::SELF, stealing_creature, stealing_creature && stealing_creature->get_is_player());
  CurrentCreatureAbilities cca;

  if (stealing_creature != nullptr && steal_creature != nullptr)
  {
    if (cca.can_see(stealing_creature, true) &&
        !is_stealing_from_self(stealing_creature, steal_creature, pl_manager) &&
        !is_already_stolen_from(stealing_creature, steal_creature, pl_manager) &&
        has_pockets(stealing_creature, steal_creature, pl_manager) &&
        confirm_steal(stealing_creature, steal_creature, pl_manager))
    {
      ThieveryCalculator tc;
      bool steal_result = false;

      if (RNG::percent_chance(tc.calculate_pct_chance_steal(stealing_creature, steal_creature)))
      {
        ItemPtr stolen_item = create_stolen_item(steal_creature);

        if (stolen_item != nullptr)
        {
          steal_result = true;
          transfer_stolen_item(stealing_creature, stolen_item, map, pl_manager, manager);
          set_flags_on_target_creature(stealing_creature, steal_creature);

          ItemIdentifier iid;
          manager.add_new_message(ActionTextKeys::get_steal_successful_message(cd.describe(), iid.get_appropriate_usage_description(stolen_item), stealing_creature->get_is_player()));
          manager.send();
        }
      }

      if (steal_result == false)
      {
        pl_manager.add_new_message(ActionTextKeys::get_steal_unsuccessful_message(stealing_creature->get_description_sid(), steal_creature->get_description_sid(), stealing_creature->get_is_player()));
        pl_manager.send();
      }

      SkillManager sm;
      sm.mark_skill(stealing_creature, SkillType::SKILL_GENERAL_THIEVERY, steal_result);
      acv = get_default_skill_action_cost_value(stealing_creature);
    }
  }

  return acv;
}

bool ThieverySkillProcessor::is_stealing_from_self(CreaturePtr stealing_creature, CreaturePtr steal_creature, IMessageManager& pl_manager)
{
  bool self_steal = false;

  if (stealing_creature->get_id() == steal_creature->get_id())
  {
    self_steal = true;

    pl_manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_THIEVERY_SELF_TARGET));
    pl_manager.send();
  }

  return self_steal;
}

// Has the targetted creature already been pilfered?  Potentially add a message 
// if so.
bool ThieverySkillProcessor::is_already_stolen_from(CreaturePtr stealing_creature, CreaturePtr steal_creature, IMessageManager& pl_manager)
{
  bool stolen = false;

  if (steal_creature != nullptr && !steal_creature->get_is_player())
  {
    stolen = String::to_bool(steal_creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_STOLEN_FROM));
  }

  CreatureDescriber cd(stealing_creature, steal_creature, true);

  if (stolen)
  {
    pl_manager.add_new_message(ActionTextKeys::get_already_stolen_message(cd.describe()));
    pl_manager.send();
  }

  return stolen;
}

bool ThieverySkillProcessor::has_pockets(CreaturePtr stealing_creature, CreaturePtr steal_creature, IMessageManager& pl_manager)
{
  RaceManager rm;
  Race* steal_race = rm.get_race(steal_creature->get_race_id());

  bool has_pockets = (steal_race && steal_race->get_has_pockets());
  CreatureDescriber cd(stealing_creature, steal_creature, true);

  if (!has_pockets)
  {
    pl_manager.add_new_message(ActionTextKeys::get_no_pockets_message(cd.describe()));
    pl_manager.send();
  }

  return has_pockets;
}

bool ThieverySkillProcessor::confirm_steal(CreaturePtr stealing_creature, CreaturePtr steal_creature, IMessageManager& pl_manager)
{
  bool steal = false;

  // Stealing from hostile creatures is always okay...
  if (steal_creature->get_decision_strategy()->get_threats_ref().has_threat(stealing_creature->get_id()).first)
  {
    steal = true;
  }
  // ...it's the innocents that some of the deities have issues with.
  else
  {
    pl_manager.add_new_confirmation_message(TextMessages::get_confirmation_message(TextKeys::DECISION_STEAL_FRIENDLY_CREATURE));
    steal = stealing_creature->get_decision_strategy()->get_confirmation();

    if (steal)
    {
      // Attacking and stealing are considered one and the same by the Nine.
      MapPtr map = Game::instance().get_current_map();
      Game::instance().get_deity_action_manager_ref().notify_action(stealing_creature, map, CreatureActionKeys::ACTION_ATTACK_FRIENDLY);
    }
  }

  return steal;
}

ItemPtr ThieverySkillProcessor::create_stolen_item(CreaturePtr steal_creature)
{
  Game& game = Game::instance();
  Rarity rarity = Rarity::RARITY_VERY_RARE;
  ItemEnchantmentCalculator iec;
  ItemGenerationManager igm;

  int danger_level = steal_creature->get_level().get_current();
  vector<ItemType> i_restr = {};
  ItemGenerationMap generation_map = igm.generate_item_generation_map({1, danger_level, rarity, i_restr, ItemValues::DEFAULT_MIN_GENERATION_VALUE});
  int enchant_points = iec.calculate_enchantments(danger_level);
  ItemPtr stolen_item = igm.generate_item(game.get_action_manager_ref(), generation_map, rarity, i_restr, enchant_points);

  return stolen_item;
}

void ThieverySkillProcessor::transfer_stolen_item(CreaturePtr stealing_creature, ItemPtr stolen_item, MapPtr map, IMessageManager& pl_manager, IMessageManager& /*general_manager*/)
{
  if (stealing_creature != nullptr && stolen_item != nullptr && map != nullptr)
  {
    tuple<bool, uint, string> steal = CreatureUtils::can_pick_up(stealing_creature, stolen_item);

    if (get<0>(steal))
    {
      stealing_creature->get_inventory()->merge_or_add(stolen_item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
    }
    else
    {
      pl_manager.add_new_message(StringTable::get(get<2>(steal)));
      pl_manager.send();

      TilePtr creature_tile = MapUtils::get_tile_for_creature(map, stealing_creature);
      creature_tile->get_items()->add_front(stolen_item);
    }
  }
}

void ThieverySkillProcessor::set_flags_on_target_creature(CreaturePtr stealing_creature, CreaturePtr steal_creature)
{
  if (stealing_creature != nullptr && steal_creature != nullptr)
  {
    HostilityManager hm;
    hm.set_hostility_to_creature(steal_creature, stealing_creature->get_id(), ThreatConstants::ACTIVE_THREAT_RATING);
    steal_creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_STOLEN_FROM, to_string(true));
  }
}

ActionCostValue ThieverySkillProcessor::get_default_skill_action_cost_value(CreaturePtr /*creature*/) const
{
  return 1;
}
