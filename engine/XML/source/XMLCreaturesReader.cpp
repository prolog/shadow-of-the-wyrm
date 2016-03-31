#include <vector>
#include "CombatConstants.hpp"
#include "Conversion.hpp"
#include "CreatureGenerationValues.hpp"
#include "CreatureProperties.hpp"
#include "DecisionStrategyFactory.hpp"
#include "DecisionStrategyProperties.hpp"
#include "XMLCreaturesReader.hpp"
#include "XMLScriptsReader.hpp"

using namespace std;

pair<CreatureMap, CreatureGenerationValuesMap> XMLCreaturesReader::get_creatures(const XMLNode& xml_configuration_creatures_node)
{
  pair<CreatureMap, CreatureGenerationValuesMap> creature_values;
  CreatureMap creatures;
  CreatureGenerationValuesMap cgv_map;

  if (!xml_configuration_creatures_node.is_null())
  {
    vector<XMLNode> creature_nodes = XMLUtils::get_elements_by_local_name(xml_configuration_creatures_node, "Creature");

    for (const XMLNode& creature_node : creature_nodes)
    {
      pair<CreaturePtr, CreatureGenerationValues> creature_details = parse_creature(creature_node);
      CreaturePtr creature = creature_details.first;
      CreatureGenerationValues cgv = creature_details.second;
      string creature_id = creature->get_id();
      
      if (creature)
      {
        creatures.insert(make_pair(creature_id, creature));
      }
      
      cgv_map.insert(make_pair(creature_id, cgv));
    }
  }
  
  creature_values.first  = creatures;
  creature_values.second = cgv_map;

  return creature_values;
}

// Parse the details of the Creature node into a shared Creature pointer.
pair<CreaturePtr, CreatureGenerationValues> XMLCreaturesReader::parse_creature(const XMLNode& creature_node)
{
  pair<CreaturePtr, CreatureGenerationValues> creature_data;
  CreaturePtr creature;
  CreatureGenerationValues cgv;

  if (!creature_node.is_null())
  {
    creature = std::make_shared<Creature>();
    creature_data.first = creature;
      
    // The creature ID for the templates gives a unique value - for each individual
    // creature, a GUID will be genreated during creation of that creature.
    string id = XMLUtils::get_attribute_value(creature_node, "id");
    creature->set_id(id);

    // Creature's race.  
    string race_id = XMLUtils::get_child_node_value(creature_node, "RaceID");
    creature->set_race_id(race_id);

    // Creature's class.
    string class_id = XMLUtils::get_child_node_value(creature_node, "ClassID");
    creature->set_class_id(class_id);

    // Whether the creature breathes air, or water.
    BreatheType breathes = static_cast<BreatheType>(XMLUtils::get_child_node_int_value(creature_node, "BreatheType"));

    creature->set_breathes(breathes);
    
    // Typically a single word or phrase: bat, orc child, troll pedestrian, etc.
    string short_description_sid = XMLUtils::get_child_node_value(creature_node, "ShortDescriptionSID");
    creature->set_short_description_sid(short_description_sid);
    
    // A longer description, which can be used as part of a sentence:
    // "a goblin warrior", "some grey ooze", etc.
    string description_sid = XMLUtils::get_child_node_value(creature_node, "DescriptionSID");
    creature->set_description_sid(description_sid);

    // The text used to describe the creature in the bestiary.
    string text_details_sid = XMLUtils::get_child_node_value(creature_node, "TextDetailsSID");
    creature->set_text_details_sid(text_details_sid);

    // What the creature says when chatted with, if anything at all.
    string speech_text_sid = XMLUtils::get_child_node_value(creature_node, "SpeechTextSID");
    creature->set_speech_text_sid(speech_text_sid);
    
    // A decision strategy for the creature, which provides a set of actions (move, attack, and so on)
    // as appropriate.  ImmobileDecisionStrategy, for example, disallows movement, and is used for
    // immobile creatures (such as slimes, etc.)
    XMLNode decision_strategy_node = XMLUtils::get_next_element_by_local_name(creature_node, "DecisionStrategy");

    if (!decision_strategy_node.is_null())
    {
      parse_decision_strategy(decision_strategy_node, creature);
    }
    
    XMLNode text_node = XMLUtils::get_next_element_by_local_name(creature_node, "Text");
    if (!text_node.is_null())
    {
      string symbol = XMLUtils::get_child_node_value(text_node, "Symbol");
      
      if (!symbol.empty())
      {
        creature->set_symbol(symbol.at(0));
      }
      
      Colour colour = static_cast<Colour>(XMLUtils::get_child_node_int_value(text_node, "Colour"));
      creature->set_colour(colour);
    }
    
    XMLNode creature_generation_node = XMLUtils::get_next_element_by_local_name(creature_node, "CreatureGeneration");
    if (!creature_generation_node.is_null())
    {
      cgv = parse_creature_generation_values(creature_generation_node);

      // Set any additional values found outside the CreatureGeneration node.
      //
      // Set the creature's race.  Set on the generation values, as it's needed 
      // in some situations for filtering potential creatures by race.
      cgv.set_race_id(race_id);
    }
    
    uint level = XMLUtils::get_child_node_int_value(creature_node, "Level");
    creature->set_level(level);

    // Properties
    XMLNode properties_node = XMLUtils::get_next_element_by_local_name(creature_node, "Properties");
    if (!properties_node.is_null())
    {
      map<string, string> addl_props;
      parse_properties(addl_props, properties_node);
      creature->set_additional_properties_map(addl_props);
    }

    // Spells
    XMLNode spells_node = XMLUtils::get_next_element_by_local_name(creature_node, "Spells");
    if (!spells_node.is_null())
    {
      parse_spells(spells_node, creature);
    }
    
    // Set the creature's base damage - this is the damage dealt if a weapon is not used.
    // If a weapon is to be used (for humanoid-types), consider leaving this empty in the
    // configuration XML.
    XMLNode base_damage_node = XMLUtils::get_next_element_by_local_name(creature_node, "Damage");
    Damage base_damage;
    // The base damage type may or may not be overridden.  For most creatures (goblins, humans, etc.)
    // it will be POUND from punching/etc.
    base_damage.set_damage_type(CombatConstants::DEFAULT_UNARMED_DAMAGE_TYPE);
    parse_damage(base_damage, base_damage_node);
    creature->set_base_damage(base_damage);
    
    // Read the base evade and soak for the creature.  For most creatures, this will be 0,
    // but some creatures (armoured beetles, dragons, etc) will have higher than usual values.
    // Evade
    int base_evade = XMLUtils::get_child_node_int_value(creature_node, "Evade", 0);
    creature->set_base_evade(base_evade);
    
    // Soak
    int base_soak = XMLUtils::get_child_node_int_value(creature_node, "Soak", 0);
    creature->set_base_soak(base_soak);

    // Speed - optionally override the race/class speed.
    XMLNode speed_node = XMLUtils::get_next_element_by_local_name(creature_node, "Speed");
    
    if (!speed_node.is_null())
    {
      int base_speed = XMLUtils::get_node_int_value(speed_node, 0);
      creature->set_speed(base_speed);
    }

    // Event scripts
    XMLNode event_scripts_node = XMLUtils::get_next_element_by_local_name(creature_node, "EventScripts");
    parse_event_scripts(event_scripts_node, creature);
  }
  
  creature_data.second = cgv;
  
  return creature_data;
}

// Parse the details about the creature's generation values
CreatureGenerationValues XMLCreaturesReader::parse_creature_generation_values(const XMLNode& creature_generation_values_node)
{
  CreatureGenerationValues cgv;
  
  if (!creature_generation_values_node.is_null())
  {
    int max = XMLUtils::get_child_node_int_value(creature_generation_values_node, "Max", -1);
    cgv.set_maximum(max);

    XMLNode allowable_terrain_types_node = XMLUtils::get_next_element_by_local_name(creature_generation_values_node, "AllowableTerrainTypes");
    
    // The tile (map) types that the creature can be generated for. (dungeon, forest, mountains, etc)
    if (!allowable_terrain_types_node.is_null())
    {
      vector<XMLNode> allowable_terrain_nodes = XMLUtils::get_elements_by_local_name(allowable_terrain_types_node, "TileType");

      for (const XMLNode& terrain_node : allowable_terrain_nodes)
      {
        TileType att = static_cast<TileType>(XMLUtils::get_node_int_value(terrain_node, static_cast<int>(TileType::TILE_TYPE_UNDEFINED)));
        cgv.add_allowable_terrain_type(att);
      }
    }

    // Optional GeneratorFilters node.
    XMLNode generator_filters_node = XMLUtils::get_next_element_by_local_name(creature_generation_values_node, "GeneratorFilters");
    if (!generator_filters_node.is_null())
    {
      vector<XMLNode> generator_filter_node = XMLUtils::get_elements_by_local_name(generator_filters_node, "Filter");
      vector<string> filters;

      for (const XMLNode& node : generator_filter_node)
      {
        filters.push_back(XMLUtils::get_node_value(node));
      }

      cgv.set_generator_filters(filters);
    }
    
    // Friendly?
    bool friendly = XMLUtils::get_child_node_bool_value(creature_generation_values_node, "Friendly", false);
    cgv.set_friendly(friendly);

    // Danger level
    int danger_level = XMLUtils::get_child_node_int_value(creature_generation_values_node, "DangerLevel");
    cgv.set_danger_level(danger_level);
    
    // Creature rarity
    Rarity rarity = static_cast<Rarity>(XMLUtils::get_child_node_int_value(creature_generation_values_node, "Rarity"));
    cgv.set_rarity(rarity);
    
    // Initial hit point; dice are used to represent a range of possible values.  A random value will be
    // generated when the creature is created, based on the Dice provided.
    XMLNode hp_dice_node = XMLUtils::get_next_element_by_local_name(creature_generation_values_node, "HP");
    Dice hp_dice;
    parse_dice(hp_dice, hp_dice_node);
    cgv.set_initial_hit_points(hp_dice);

    // Initial arcana points.  If none are provided, the base HP are used.
    XMLNode ap_dice_node = XMLUtils::get_next_element_by_local_name(creature_generation_values_node, "AP");
    Dice ap_dice;

    if (!ap_dice_node.is_null())
    {
      parse_dice(ap_dice, ap_dice_node);
    }
    else
    {
      ap_dice = hp_dice;
      ap_dice.set_num_dice(std::max<int>(1, ap_dice.get_num_dice() / 2));
    }

    cgv.set_initial_arcana_points(ap_dice);
    
    // Base experience value; a range around this value will be used to generate the experience value
    // for each generated creature.
    uint base_experience = XMLUtils::get_child_node_int_value(creature_generation_values_node, "Exp");
    cgv.set_base_experience_value(base_experience);

    XMLNode skills_node = XMLUtils::get_next_element_by_local_name(creature_generation_values_node, "Skills");
    if (!skills_node.is_null())
    {
      Skills skills = skill_reader.get_skills(skills_node);
      cgv.set_skills(skills);
    }

    // Optional equipment/inventory node.
    XMLNode eq_inv_node = XMLUtils::get_next_element_by_local_name(creature_generation_values_node, "InitialEquipmentAndInventory");
    if (!eq_inv_node.is_null())
    {
      map<EquipmentWornLocation, InitialItem> initial_eq;
      vector<InitialItem> initial_inv;

      parse_initial_equipment_and_inventory(initial_eq, initial_inv, eq_inv_node);

      cgv.set_initial_equipment(initial_eq);
      cgv.set_initial_inventory(initial_inv);
    }
  }
  
  return cgv;
}

// Parse in the list of event scripts for the creature
void XMLCreaturesReader::parse_event_scripts(const XMLNode& event_scripts_node, CreaturePtr creature)
{
  XMLScriptsReader xsr;

  if (!event_scripts_node.is_null())
  {
    vector<pair<string, string>> node_details = { { "DeathScript", CreatureEventScripts::CREATURE_EVENT_SCRIPT_DEATH }, 
                                                  { "AttackScript", CreatureEventScripts::CREATURE_EVENT_SCRIPT_ATTACK },
                                                  { "ChatScript", CreatureEventScripts::CREATURE_EVENT_SCRIPT_CHAT },
                                                  { "DecisionScript", CreatureEventScripts::CREATURE_EVENT_SCRIPT_DECISION } };

    for (const auto& details : node_details)
    {
      XMLNode node = XMLUtils::get_next_element_by_local_name(event_scripts_node, details.first);
      ScriptDetails sd = xsr.get_script_details(node);
      creature->add_event_script(details.second, sd);
    }
  }
}

// Read in any spells the creature has
void XMLCreaturesReader::parse_spells(const XMLNode& spells_node, CreaturePtr creature)
{
  if (!spells_node.is_null())
  {
    vector<XMLNode> spell_nodes = XMLUtils::get_elements_by_local_name(spells_node, "Spell");
    SpellKnowledge& sk = creature->get_spell_knowledge_ref();

    for (const XMLNode& spell_node : spell_nodes)
    {
      string spell_id = XMLUtils::get_child_node_value(spell_node, "SpellID");
      int castings = XMLUtils::get_child_node_int_value(spell_node, "Castings");
      int bonus = XMLUtils::get_child_node_int_value(spell_node, "Bonus");

      IndividualSpellKnowledge isk;
      isk.set_castings(castings);
      isk.set_bonus(bonus);

      sk.set_spell_knowledge(spell_id, isk);
    }
  }
}

void XMLCreaturesReader::parse_decision_strategy(const XMLNode& decision_strategy_node, CreaturePtr creature)
{
  if (!decision_strategy_node.is_null())
  {
    string decision_strategy_id = XMLUtils::get_child_node_value(decision_strategy_node, "Strategy");
    DecisionStrategyPtr decision_strategy = DecisionStrategyFactory::create_decision_strategy(decision_strategy_id);

    bool suppress_magic = XMLUtils::get_child_node_bool_value(decision_strategy_node, "SuppressMagic");
    decision_strategy->set_property(DecisionStrategyProperties::DECISION_STRATEGY_SUPPRESS_MAGIC, Bool::to_string(suppress_magic));

    bool breeds = XMLUtils::get_child_node_bool_value(decision_strategy_node, "Breeds", false);
    decision_strategy->set_property(DecisionStrategyProperties::DECISION_STRATEGY_BREEDS, Bool::to_string(breeds));

    creature->set_decision_strategy(decision_strategy);
  }
}