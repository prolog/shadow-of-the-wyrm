#include <iterator>
#include <map>
#include "Conversion.hpp"
#include "CreatureCalculator.hpp"
#include "CreatureGenerationConstants.hpp"
#include "CreatureGenerationManager.hpp"
#include "CreatureFactory.hpp"
#include "DecisionStrategyFactory.hpp"
#include "DecisionStrategyTypes.hpp"
#include "ExperienceManager.hpp"
#include "Game.hpp"
#include "MapProperties.hpp"
#include "RaceManager.hpp"
#include "RNG.hpp"

using namespace std;

CreatureGenerationManager::CreatureGenerationManager()
{
}

CreatureGenerationMap CreatureGenerationManager::generate_creature_generation_map(const TileType map_terrain_type, const bool permanent_map, const int min_danger_level, const int max_danger_level, const Rarity rarity, const map<string, string>& additional_properties)
{
  int min_danger = min_danger_level;
  CreatureGenerationMap generation_map;

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
    
  while (generation_map.empty() && (min_danger > 0))
  {
    // Build the map of creatures available for generation given the danger level and rarity
    for (CreatureMap::iterator c_it = creatures.begin(); c_it != creatures.end(); c_it++)
    {
      string creature_id = c_it->first;

      CreaturePtr creature = c_it->second;
      CreatureGenerationValues cgvals = cgv_map[creature_id];

      if (does_creature_match_generation_criteria(cgvals, map_terrain_type, permanent_map, min_danger, max_danger_level, rarity, ignore_level_checks, required_race, generator_filters, preset_creature_ids))
      {
        generation_map.insert(make_pair(creature_id, make_pair(creature, cgvals)));
      }
    }

    min_danger /= 2;
  }
  
  return generation_map;
}

CreatureGenerationMap CreatureGenerationManager::generate_ancient_beasts(const int danger_level, const TileType map_terrain_type)
{
  CreatureGenerationMap cgm;

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
      // Look, ancient beasts are in no way fair.
      if (RNG::percent_chance(50))
      {
        dam.set_damage_flag(static_cast<DamageFlagType>(df), true);
      }
    }

    CreaturePtr ancient_beast;
    CreatureFactory cf;
    ancient_beast = cf.create_by_race_and_class(Game::instance().get_action_manager_ref(), RaceID::RACE_ID_UNKNOWN, "", "", CreatureSex::CREATURE_SEX_NOT_SPECIFIED);
    ancient_beast->set_base_damage(dam);
    ancient_beast->set_evade(danger_level);
    ancient_beast->set_soak(danger_level);
    ancient_beast->set_arcana_points(Statistic(RNG::dice(ap_dice)));
    ancient_beast->set_hit_points(Statistic(RNG::dice(hp_dice)));
    ancient_beast->set_colour(static_cast<Colour>(i+1));
    ancient_beast->set_original_id(creature_id);

    DecisionStrategyPtr ds = DecisionStrategyFactory::create_decision_strategy(DecisionStrategyID::DECISION_STRATEGY_MOBILE);
    ancient_beast->set_decision_strategy(ds);

    string desc_sid = "ANCIENT_BEAST" + std::to_string(i) + "_DESCRIPTION_SID";
    string short_desc_sid = "ANCIENT_BEAST" + std::to_string(i) + "_SHORT_DESCRIPTION_SID"; // JCD FIXME REFACTOR
    string text_details_sid = "ANCIENT_BEAST_TEXT_DETAILS_SID";
    ancient_beast->set_description_sid(desc_sid);
    ancient_beast->set_short_description_sid(short_desc_sid);
    ancient_beast->set_text_details_sid(text_details_sid);
    ancient_beast->set_level(danger_level);
    ancient_beast->set_symbol('X');

    ExperienceManager em;
    int dl = std::max(1, danger_level);
    int xp_val = em.get_total_experience_needed_for_level(nullptr, std::min(dl, 50));
    cgv.set_base_experience_value(xp_val);
    ancient_beast->set_experience_value(xp_val);

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

    cgm[creature_id] = make_pair(ancient_beast, cgv);
  }

  return cgm;
}

string CreatureGenerationManager::select_creature_id_for_generation(ActionManager& am, CreatureGenerationMap& generation_map)
{
  string creature_id;

  // Iterate through the generation map, and attempt to generate a creature with probability P,
  // where P = (danger level / danger_level + num_creatures_in_map)
  int p_denominator = 0;

  // Get the denominator for the probabilistic generation by summing the danger level over all creatures
  // in the map.
  for (CreatureGenerationMap::iterator c_it = generation_map.begin(); c_it != generation_map.end(); c_it++)
  {
    CreatureGenerationValues cgv = c_it->second.second;
    p_denominator += cgv.get_danger_level();
  }

  float p_denominator_f = static_cast<float>(p_denominator);

  // Determine the creature to generate
  for (CreatureGenerationMap::iterator c_it = generation_map.begin(); c_it != generation_map.end(); c_it++)
  {
    CreatureGenerationValues cgv = c_it->second.second;

    int p_numerator = cgv.get_danger_level();
    int P = static_cast<int>((static_cast<float>(p_numerator) / p_denominator_f) * 100);

    // Generate the creature if we hit the percentage, or if we're on the last item in the map
    // and a creature has not yet been generated.
    if (!cgv.is_maximum_reached() && (RNG::percent_chance(P) || ((distance(c_it, generation_map.end()) == 1))))
    {
      creature_id = c_it->first;
      break;
    }
  }

  return creature_id;
}

CreaturePtr CreatureGenerationManager::generate_creature(ActionManager& am, CreatureGenerationMap& generation_map)
{
  CreaturePtr generated_creature;
  CreatureFactory cf;

  string creature_id = select_creature_id_for_generation(am, generation_map);

  if (Creature::is_ancient_beast(creature_id))
  {
    auto c_it = generation_map.find(creature_id);

    if (c_it != generation_map.end())
    {
      generated_creature = cf.create_by_creature_id(am, creature_id, c_it->second.first);
    }
  }
  else
  {
    generated_creature = cf.create_by_creature_id(am, creature_id);
  }

  if (generated_creature)
  {
    CreatureCalculator::update_calculated_values(generated_creature);
  }
    
  return generated_creature;
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
