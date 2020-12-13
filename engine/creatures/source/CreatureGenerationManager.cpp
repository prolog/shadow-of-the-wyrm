#include <iterator>
#include <map>
#include "Conversion.hpp"
#include "CreatureCalculator.hpp"
#include "CreatureGenerationConstants.hpp"
#include "CreatureGenerationManager.hpp"
#include "CreatureFactory.hpp"
#include "CreatureProperties.hpp"
#include "CreatureTypes.hpp"
#include "CreatureUtils.hpp"
#include "DecisionStrategyFactory.hpp"
#include "DecisionStrategyProperties.hpp"
#include "DecisionStrategyTypes.hpp"
#include "ExperienceManager.hpp"
#include "Game.hpp"
#include "HostilityManager.hpp"
#include "ItemEnchantmentCalculator.hpp"
#include "MapProperties.hpp"
#include "Naming.hpp"
#include "ProcgenTextKeys.hpp"
#include "RaceManager.hpp"
#include "RNG.hpp"

using namespace std;

const int CreatureGenerationManager::ANCIENT_BEASTS_MIN_DANGER_LEVEL = 20;

CreatureGenerationManager::CreatureGenerationManager()
{
}

CreatureGenerationList CreatureGenerationManager::generate_creature_generation_map(const TileType map_terrain_type, const bool permanent_map, const int min_danger_level, const int max_danger_level, const Rarity rarity, const map<string, string>& additional_properties)
{
  int min_danger = min_danger_level;
  CreatureGenerationList generation_list;

  CreaturePtr generated_creature;
  Game& game = Game::instance();
  
  CreatureMap creatures = game.get_creatures_ref();
  CreatureGenerationValuesMap cgv_map = game.get_creature_generation_values_ref();

  bool ignore_level_checks = false;

  auto a_it = additional_properties.find(MapProperties::MAP_PROPERTIES_IGNORE_CREATURE_LVL_CHECKS);
  if (a_it != additional_properties.end())
  {
    ignore_level_checks = String::to_bool(a_it->second);
  }

  // If generation needs to be restricted to undead, dragons, etc.
  string required_race;
  a_it = additional_properties.find(MapProperties::MAP_PROPERTIES_GENERATED_CREATURE_RACE_ID);
  if (a_it != additional_properties.end())
  {
    required_race = a_it->second;
  }

  // If generation needs to be restricted to one of a number of creature IDs.
  vector<string> preset_creature_ids;
  a_it = additional_properties.find(MapProperties::MAP_PROPERTIES_CREATURE_IDS);
  if (a_it != additional_properties.end())
  {
    preset_creature_ids = String::create_string_vector_from_csv_string(a_it->second);
  }

  vector<string> generator_filters;
  a_it = additional_properties.find(MapProperties::MAP_PROPERTIES_GENERATOR_FILTERS);

  if (a_it != additional_properties.end())
  {
    generator_filters = String::create_string_vector_from_csv_string(a_it->second);

    // Sort this for easy comparison later on...
    std::sort(generator_filters.begin(), generator_filters.end());
  }
    
  // Build the map of creatures available for generation given the danger level and rarity
  for (CreatureMap::iterator c_it = creatures.begin(); c_it != creatures.end(); c_it++)
  {
    string creature_id = c_it->first;

    CreaturePtr creature = c_it->second;
    CreatureGenerationValues cgvals = cgv_map[creature_id];

    if (does_creature_match_generation_criteria(cgvals, map_terrain_type, permanent_map, min_danger, max_danger_level, rarity, ignore_level_checks, required_race, generator_filters, preset_creature_ids))
    {
      generation_list.push_back({creature_id, creature, cgvals});
    }
  }
  
  return generation_list;
}

CreatureGenerationList CreatureGenerationManager::generate_ancient_beasts(const int danger_level, const MapType map_type, const TileType map_terrain_type)
{
  CreatureGenerationList cgl;

  // Ancient beasts only ever appear underground, in dungeons, sewers, caverns,
  // etc.
  if (map_type == MapType::MAP_TYPE_UNDERWORLD && danger_level >= ANCIENT_BEASTS_MIN_DANGER_LEVEL)
  {
    for (int i = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); i < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); i++)
    {
      string creature_id_prefix = CreatureID::CREATURE_ID_PREFIX_ANCIENT_BEAST;
      string creature_id = creature_id_prefix + std::to_string(i);
      CreatureGenerationValues cgv;

      Dice hp_dice(danger_level * 2, 6, danger_level);
      Dice ap_dice(danger_level * 2, 6, danger_level);

      Damage dam;
      dam.set_num_dice(danger_level * 2);
      dam.set_dice_sides(6);
      dam.set_damage_type(static_cast<DamageType>(i));

      for (int df = static_cast<int>(DamageFlagType::DAMAGE_FLAG_FIRST); df < static_cast<int>(DamageFlagType::DAMAGE_FLAG_LAST); df++)
      {
        if (df != static_cast<int>(DamageFlagType::DAMAGE_FLAG_CHAOTIC))
        {
          // Look, ancient beasts are in no way fair.
          if (RNG::percent_chance(50))
          {
            dam.set_damage_flag(static_cast<DamageFlagType>(df), true);
          }
        }
      }

      CreaturePtr ancient_beast;
      CreatureFactory cf;
      DecisionStrategyPtr ds = DecisionStrategyFactory::create_decision_strategy(DecisionStrategyID::DECISION_STRATEGY_MOBILE);
      string desc_sid = "ANCIENT_BEAST" + std::to_string(i) + "_DESCRIPTION_SID";
      string short_desc_sid = "ANCIENT_BEAST" + std::to_string(i) + "_SHORT_DESCRIPTION_SID";
      string text_details_sid = "ANCIENT_BEAST_TEXT_DETAILS_SID";
      string ref_id = "ancient_beast_" + std::to_string(i);

      ExperienceManager em;
      int dl = std::max(1, danger_level);
      int xp_val = em.get_total_experience_needed_for_level(nullptr, std::min(dl, 50));

      ancient_beast = cf.create_by_race_and_class(Game::instance().get_action_manager_ref(), RaceID::RACE_ID_UNKNOWN, "", "", CreatureSex::CREATURE_SEX_NOT_SPECIFIED, CreatureSize::CREATURE_SIZE_HUGE);
      ancient_beast->set_base_damage(dam);
      ancient_beast->set_evade(danger_level);
      ancient_beast->set_soak(danger_level);
      ancient_beast->set_arcana_points(Statistic(RNG::dice(ap_dice)));
      ancient_beast->set_hit_points(Statistic(RNG::dice(hp_dice)));
      ancient_beast->set_original_id(creature_id);
      ancient_beast->set_decision_strategy(std::move(ds));
      ancient_beast->set_description_sid(desc_sid);
      ancient_beast->set_short_description_sid(short_desc_sid);
      ancient_beast->set_text_details_sid(text_details_sid);
      ancient_beast->set_level(danger_level);

      Symbol s('X', static_cast<Colour>(i + 1));
      SpritesheetLocation& ssl = s.get_spritesheet_location_ref();

      ssl.set_reference_id(ref_id);
      ssl.set_index(SpritesheetIndex::SPRITESHEET_INDEX_CREATURE);

      ancient_beast->set_symbol(s);

      ancient_beast->set_experience_value(xp_val);

      cgv.set_base_experience_value(xp_val);
      cgv.set_maximum(-1);
      cgv.set_current(0);
      cgv.add_allowable_terrain_type(map_terrain_type);
      cgv.set_danger_level(danger_level);
      cgv.set_friendly(0);
      cgv.set_id(creature_id);
      cgv.set_initial_arcana_points(ap_dice);
      cgv.set_initial_hit_points(hp_dice);
      cgv.set_race_id(RaceID::RACE_ID_UNKNOWN);
      cgv.set_rarity(Rarity::RARITY_COMMON);

      cgl.push_back({ creature_id, ancient_beast, cgv });
    }
  }

  return cgl;
}

string CreatureGenerationManager::select_creature_id_for_generation(ActionManager& am, CreatureGenerationList& generation_list)
{
  string creature_id;

  // Determine the creature to generate
  if (!generation_list.empty())
  {
    for (int i = 0; i < 10; i++)
    {
      int rnd_val = RNG::range(0, generation_list.size() - 1);
      const CreatureGenerationListValue& cglv = generation_list.at(rnd_val);
      const CreatureGenerationValues& cgv = cglv.get_creature_generation_values();

      if (!cgv.is_maximum_reached())
      {
        creature_id = cglv.get_creature_base_id();
        break;
      }
    }
  }

  return creature_id;
}

CreaturePtr CreatureGenerationManager::generate_creature(ActionManager& am, CreatureGenerationList& generation_list, MapPtr current_map)
{
  CreaturePtr generated_creature;
  CreatureFactory cf;

  string creature_id = select_creature_id_for_generation(am, generation_list);

  if (Creature::is_ancient_beast(creature_id))
  {
    auto gl_it = std::find_if(generation_list.begin(), generation_list.end(),
      [&creature_id](const CreatureGenerationListValue& cglv) { return cglv.get_creature_base_id() == creature_id; } );

    if (gl_it != generation_list.end())
    {
      generated_creature = cf.create_by_creature_id(am, creature_id, current_map, gl_it->get_creature());
    }
  }
  else
  {
    generated_creature = cf.create_by_creature_id(am, creature_id, current_map);
  }

  if (generated_creature)
  {
    CreatureCalculator cc;
    cc.update_calculated_values(generated_creature);
  }
    
  return generated_creature;
}

CreaturePtr CreatureGenerationManager::generate_hireling(ActionManager& am, const int danger_level)
{
  CreatureSex sex = static_cast<CreatureSex>(RNG::range(static_cast<int>(CreatureSex::CREATURE_SEX_MALE), static_cast<int>(CreatureSex::CREATURE_SEX_FEMALE)));
  CreatureFactory cf;

  Race* race = CreatureUtils::get_random_user_playable_race();
  Class* cur_class = CreatureUtils::get_random_user_playable_class();
  string race_id;
  string class_id;

  if (race != nullptr && cur_class != nullptr)
  {
    race_id = race->get_race_id();
    class_id = cur_class->get_class_id();
  }

  string name = Naming::generate_name(sex);
  CreaturePtr hireling = cf.create_by_race_and_class(am, race_id, class_id, name, sex, CreatureSize::CREATURE_SIZE_NA);
  DecisionStrategyPtr ds = DecisionStrategyFactory::create_decision_strategy(DecisionStrategyID::DECISION_STRATEGY_MOBILE);

  // Hirelings remain neutral and never jump in to help.
  ds->set_property(DecisionStrategyProperties::DECISION_STRATEGY_ASSIST_PCT, std::to_string(0));

  hireling->set_decision_strategy(std::move(ds));

  hireling->set_description_sid(ProcgenTextKeys::HIRELING_DESC_SID);
  hireling->set_short_description_sid(ProcgenTextKeys::HIRELING_SHORT_DESC_SID);
  hireling->set_text_details_sid(ProcgenTextKeys::HIRELING_TEXT_DETAILS_SID);
  
  string lua_script = StringTable::get(ProcgenTextKeys::HIRELING_LUA_SCRIPT_SID);
  EventScriptsMap scripts;
  ScriptDetails sd(lua_script, 100);
  hireling->add_event_script(CreatureEventScripts::CREATURE_EVENT_SCRIPT_CHAT, sd);

  Symbol s('@', static_cast<Colour>(RNG::range(1, 15)));
  SpritesheetLocation & ssl = s.get_spritesheet_location_ref();

  ssl.set_reference_id(CreatureReferences::HIRELING);
  ssl.set_index(SpritesheetIndex::SPRITESHEET_INDEX_CREATURE);
  hireling->set_symbol(s);

  HostilityManager hm;
  hm.set_hostility_to_player(hireling, false);

  hireling->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_HIRELING_CHAT_SID, "HIRELING_HIRE" + std::to_string(RNG::range(1, 5)) + "_SID");

  int hire_fee = danger_level * 50;
  hireling->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_HIRE_FEE, std::to_string(hire_fee));

  // Set up the creature's attack, HP, AP, spells.
  ExperienceManager em;
  int xp = em.get_total_experience_needed_for_level(hireling, danger_level);
  em.gain_experience(hireling, static_cast<uint>(xp));

  // Enchant its equipment
  ItemEnchantmentCalculator iec;
  Equipment& eq = hireling->get_equipment();

  for (int e = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); e < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); e++)
  {
    EquipmentWornLocation ewl = static_cast<EquipmentWornLocation>(e);
    ItemPtr item = eq.get_item(ewl);

    if (item != nullptr)
    {
      int num_enchants = 2 + iec.calculate_enchantments(danger_level);      
      item->enchant(iec.calculate_pct_chance_brand(1.0, item), num_enchants);
    }
  }

  // Add a boat
  IInventoryPtr inv = hireling->get_inventory();

  if (!inv->has_item_type(ItemType::ITEM_TYPE_BOAT))
  {
    ItemPtr coracle = ItemManager::create_item(ItemIdKeys::ITEM_ID_CORACLE);
    inv->merge_or_add(coracle, InventoryAdditionType::INVENTORY_ADDITION_FRONT);
  }

  return hireling;
}

bool CreatureGenerationManager::does_creature_match_generation_criteria(const CreatureGenerationValues& cgv, const TileType terrain_type, const bool permanent_map, const int min_danger_level, const int max_danger_level, const Rarity rarity, const bool ignore_level_checks, const string& required_race, const vector<string>& generator_filters, const vector<string>& preset_creature_ids)
{
  RaceManager rm;
  int cgv_danger_level = cgv.get_danger_level();
  int cgv_maximum = cgv.get_maximum();
  vector<string> cgv_generator_filters = cgv.get_generator_filters();

  // Sort the vectors.  The assumption is that the input vector is sorted.
  std::sort(cgv_generator_filters.begin(), cgv_generator_filters.end());

  if ( cgv.is_terrain_type_allowed(terrain_type)
    && cgv_danger_level >= 0 // Exclude danger level of -1, which means "don't generate"
    && (ignore_level_checks || cgv_danger_level >= min_danger_level)
    && (ignore_level_checks || cgv_danger_level <= max_danger_level)
    && (required_race.empty() || rm.is_race_or_descendent(cgv.get_race_id(), required_race))
    && (cgv_maximum <= CreatureGenerationConstants::CREATURE_GENERATION_UNLIMITED || (cgv.get_current() < cgv_maximum)) // Either no max, or less than the > 0 maximum
    // If a list of preset creature IDs are present, filter out all creature
    // IDs not in that list.
    && (preset_creature_ids.empty() || (std::find(preset_creature_ids.begin(), preset_creature_ids.end(), cgv.get_id()) != preset_creature_ids.end()))
    && (cgv_maximum != 1 || permanent_map) // no uniques on temporary maps
    // If there are no generator filters (from the generator/map) the creature
    // can be generated.  If there are generator filters, then the creature's
    // values must be present in the generator/map's.
    && (generator_filters.empty() || std::includes(cgv_generator_filters.begin(), cgv_generator_filters.end(), generator_filters.begin(), generator_filters.end()))
    && cgv.get_rarity() <= rarity )
  {
    return true;
  }
  
  return false;
}
