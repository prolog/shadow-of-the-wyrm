#include <vector>
#include "CombatConstants.hpp"
#include "Conversion.hpp"
#include "CreatureGenerationValues.hpp"
#include "CreatureProperties.hpp"
#include "DecisionStrategyFactory.hpp"
#include "DecisionStrategyProperties.hpp"
#include "Log.hpp"
#include "ModifyStatisticsEffect.hpp"
#include "XMLCreaturesReader.hpp"
#include "XMLModifierReader.hpp"

using namespace std;

XMLCreaturesReader::XMLCreaturesReader()
{
}

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
      vector<pair<CreaturePtr, CreatureGenerationValues>> creature_details = parse_creature(creature_node);

      for (const auto& c_pair : creature_details)
      {
        CreaturePtr creature = c_pair.first;
        CreatureGenerationValues cgv = c_pair.second;
        string creature_id = creature->get_id();

        if (creature)
        {
          creatures.insert(make_pair(creature_id, creature));
        }

        cgv_map.insert(make_pair(creature_id, cgv));
      }
    }
  }
  
  creature_values.first  = creatures;
  creature_values.second = cgv_map;

  return creature_values;
}

// Parse the details of the Creature node into a shared Creature pointer.
vector<pair<CreaturePtr, CreatureGenerationValues>> XMLCreaturesReader::parse_creature(const XMLNode& creature_node)
{
  vector<pair<CreaturePtr, CreatureGenerationValues>> creatures_data;

  if (!creature_node.is_null())
  {
    // Template creatures are those with multiple ids, short descs, descs, 
    // text details, and speech text. When these are vectorized and are
    // the same length, iterate through the arrays, creating a new
    // creature for each.
    string id = XMLUtils::get_attribute_value(creature_node, "id");
    string short_description_sid = XMLUtils::get_child_node_value(creature_node, "ShortDescriptionSID");
    string description_sid = XMLUtils::get_child_node_value(creature_node, "DescriptionSID");
    string text_details_sid = XMLUtils::get_child_node_value(creature_node, "TextDetailsSID");
    string speech_text_sid = XMLUtils::get_child_node_value(creature_node, "SpeechTextSID");
    string night_speech_text_sid = XMLUtils::get_child_node_value(creature_node, "NightSpeechTextSID");

    vector<string> id_vec = String::create_string_vector_from_csv_string(id);
    vector<string> sdesc_vec = String::create_string_vector_from_csv_string(short_description_sid);
    vector<string> desc_vec = String::create_string_vector_from_csv_string(description_sid);
    vector<string> td_vec = String::create_string_vector_from_csv_string(text_details_sid);
    vector<string> stext_vec = String::create_string_vector_from_csv_string(speech_text_sid);
    vector<string> ntext_vec = String::create_string_vector_from_csv_string(night_speech_text_sid);
    bool length_ok = (id_vec.size() == sdesc_vec.size() && 
                      sdesc_vec.size() == desc_vec.size() && 
                      desc_vec.size() == td_vec.size() && 
                      td_vec.size() == stext_vec.size());

    if (!length_ok)
    {
      Log::instance().error("Incorrect vector lengths for creature with id_vec=" + id);
    }

    for (size_t i = 0; i < id_vec.size(); i++)
    {
      pair<CreaturePtr, CreatureGenerationValues> creature_data;
      CreatureGenerationValues cgv;
      CreaturePtr creature = std::make_shared<Creature>();
      creature_data.first = creature;

      // The creature ID for the templates gives a unique value - for each individual
      // creature, a GUID will be genreated during creation of that creature.
      string id_val = id_vec.at(i);
      creature->set_id(id_val);

      // Creature's race.  
      string race_id = XMLUtils::get_child_node_value(creature_node, "RaceID");
      creature->set_race_id(race_id);

      // Creature's class.
      string class_id = XMLUtils::get_child_node_value(creature_node, "ClassID");
      creature->set_class_id(class_id);

      // Deity, maybe.
      string deity_id = XMLUtils::get_child_node_value(creature_node, "DeityID");

      if (!deity_id.empty())
      {
        creature->get_religion_ref().set_active_deity_id(deity_id);
      }

      // Whether the creature breathes air, or water.  Only set the value if
      // explicitly set on the creature - most things will breathe air, and some
      // races will set a number of options.
      XMLNode breathetype_node = XMLUtils::get_next_element_by_local_name(creature_node, "BreatheType");
      BreatheType breathes = BreatheType::BREATHE_TYPE_AIR;

      if (!breathetype_node.is_null())
      {
        breathes = static_cast<BreatheType>(XMLUtils::get_node_int_value(breathetype_node));
        creature->set_breathes(breathes);
      }

      // Typically a single word or phrase: bat, orc child, troll pedestrian, etc.
      short_description_sid = sdesc_vec.at(sdesc_vec.size() == id_vec.size() ? i : 0);
      creature->set_short_description_sid(short_description_sid);

      // A longer description, which can be used as part of a sentence:
      // "a goblin warrior", "some grey ooze", etc.
      description_sid = desc_vec.at(desc_vec.size() == id_vec.size() ? i : 0);
      creature->set_description_sid(description_sid);

      // The text used to describe the creature in the bestiary.
      text_details_sid = td_vec.at(td_vec.size() == id_vec.size() ? i : 0);
      creature->set_text_details_sid(text_details_sid);

      // What the creature says when chatted with, if anything at all.
      speech_text_sid = stext_vec.at(stext_vec.size() == id_vec.size() ? i : 0);
      creature->set_speech_text_sid(speech_text_sid);

      // What the creature says at night.  If nothing is provided, the engine
      // will fall back on the regular speech text sid.
      night_speech_text_sid = ntext_vec.at(ntext_vec.size() == id_vec.size() ? i : 0);

      if (!night_speech_text_sid.empty())
      {
        creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_NIGHT_SPEECH_TEXT_SID, night_speech_text_sid);
      }

      // Size. May not be defined, in which case the game will use the race's
      // value.
      creature->set_size(static_cast<CreatureSize>(XMLUtils::get_child_node_int_value(creature_node, "Size", -1)));

      // What sex is the creature?  If unspecified, default to male.
      CreatureSex sex = static_cast<CreatureSex>(XMLUtils::get_child_node_int_value(creature_node, "Sex"));
      creature->set_sex(sex);

      // Read any permanent statuses that override the race values.
      vector<pair<string, string>> element_and_id = { {"Flying", StatusIdentifiers::STATUS_ID_FLYING}, {"WaterBreathing", StatusIdentifiers::STATUS_ID_WATER_BREATHING} };

      for (const auto& ei : element_and_id)
      {
        bool node_val = XMLUtils::get_child_node_bool_value(creature_node, ei.first);

        if (node_val)
        {
          Modifier m;
          ModifyStatisticsEffect mse;
          m.set_status(ei.second, true);
          mse.apply_modifiers(creature, m, ModifyStatisticsDuration::MODIFY_STATISTICS_DURATION_PRESET, -1);
        }
      }

      // A decision strategy for the creature, which provides a set of actions (move, attack, and so on)
      // as appropriate.  ImmobileDecisionStrategy, for example, disallows movement, and is used for
      // immobile creatures (such as slimes, etc.)
      XMLNode decision_strategy_node = XMLUtils::get_next_element_by_local_name(creature_node, "DecisionStrategy");

      if (!decision_strategy_node.is_null())
      {
        parse_decision_strategy(decision_strategy_node, creature);
      }

      XMLNode symbol_node = XMLUtils::get_next_element_by_local_name(creature_node, "Symbol");
      Symbol s('?', Colour::COLOUR_WHITE);
      parse_symbol(s, symbol_node, true, i);
      creature->set_symbol(s);

      XMLNode creature_generation_node = XMLUtils::get_next_element_by_local_name(creature_node, "CreatureGeneration");
      if (!creature_generation_node.is_null())
      {
        cgv = parse_creature_generation_values(creature_generation_node);

        // Set any additional values found outside the CreatureGeneration node.

        // Set the creature's ID. Set on the generation values, as it's needed 
        // in some situations for ensuring only creatures from a certain set
        // of IDs are generated.
        cgv.set_id(id);

        // Set the creature's race. Needed occasionally for filtering so that 
        // only creatures of a particular race are generated.
        cgv.set_race_id(race_id);

        // Set the breathe type so that air breathers aren't generated
        // underwater.
        cgv.set_breathe_type(breathes);
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

      XMLNode range_node = XMLUtils::get_next_element_by_local_name(creature_node, "Range");
      if (!range_node.is_null())
      {
        creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_PRIMARY_MELEE_RANGE, XMLUtils::get_node_value(range_node));
      }

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
      map<string, string> node_details = { {"CreateScript", CreatureEventScripts::CREATURE_EVENT_SCRIPT_CREATE},
                                           {"DeathScript", CreatureEventScripts::CREATURE_EVENT_SCRIPT_DEATH},
                                           {"AttackScript", CreatureEventScripts::CREATURE_EVENT_SCRIPT_ATTACK},
                                           {"ChatScript", CreatureEventScripts::CREATURE_EVENT_SCRIPT_CHAT},
                                           {"NightChatScript", CreatureEventScripts::CREATURE_EVENT_SCRIPT_CHAT_NIGHT},
                                           {"DecisionScript", CreatureEventScripts::CREATURE_EVENT_SCRIPT_DECISION},
                                           {"DropScript", CreatureEventScripts::CREATURE_EVENT_SCRIPT_DROP},
                                           {"TameScript", CreatureEventScripts::CREATURE_EVENT_SCRIPT_TAME} };

      parse_event_scripts(event_scripts_node, node_details, creature->get_event_scripts_ref());
      creature_data.second = cgv;
      creatures_data.push_back(creature_data);
  }
  }
    
  return creatures_data;
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

    // Optional modifiers node.
    XMLNode initial_modifiers_node = XMLUtils::get_next_element_by_local_name(creature_generation_values_node, "InitialModifiers");
    XMLModifierReader modifier_reader;

    Modifier m = modifier_reader.get_modifier(initial_modifiers_node);
    cgv.set_modifier(m);

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
    decision_strategy->set_property(DecisionStrategyProperties::DECISION_STRATEGY_SUPPRESS_MAGIC, std::to_string(suppress_magic));

    bool breeds = XMLUtils::get_child_node_bool_value(decision_strategy_node, "Breeds", false);
    decision_strategy->set_property(DecisionStrategyProperties::DECISION_STRATEGY_BREEDS, std::to_string(breeds));

    bool sentinel = XMLUtils::get_child_node_bool_value(decision_strategy_node, "Sentinel", false);
    decision_strategy->set_property(DecisionStrategyProperties::DECISION_STRATEGY_SENTINEL, std::to_string(sentinel));

    bool sentry = XMLUtils::get_child_node_bool_value(decision_strategy_node, "Sentry", false);

    if (sentry)
    {
      decision_strategy->set_property(DecisionStrategyProperties::DECISION_STRATEGY_ASSIST_PCT, std::to_string(100));
    }

    string allies = XMLUtils::get_child_node_value(decision_strategy_node, "Allies");

    if (!allies.empty())
    {
      decision_strategy->set_property(DecisionStrategyProperties::DECISION_STRATEGY_ALLIES_IDS, allies);
    }

    XMLNode acontra_node = XMLUtils::get_next_element_by_local_name(decision_strategy_node, "AttackContraband");
    if (!acontra_node.is_null())
    {
      bool attack_contra = XMLUtils::get_node_bool_value(acontra_node);
      decision_strategy->set_property(DecisionStrategyProperties::DECISION_STRATEGY_ATTACK_CONTRABAND, to_string(attack_contra));
    }

    bool pickup = XMLUtils::get_child_node_bool_value(decision_strategy_node, "Pickup", true);
    decision_strategy->set_property(DecisionStrategyProperties::DECISION_STRATEGY_PICKUP, std::to_string(pickup));

    bool shopkeeper = XMLUtils::get_child_node_bool_value(decision_strategy_node, "Shopkeeper", false);
    decision_strategy->set_property(DecisionStrategyProperties::DECISION_STRATEGY_SHOPKEEPER, std::to_string(shopkeeper));

    bool resist_switch = XMLUtils::get_child_node_bool_value(decision_strategy_node, "ResistSwitch", false);
    decision_strategy->set_property(DecisionStrategyProperties::DECISION_STRATEGY_RESIST_SWITCH, std::to_string(resist_switch));

    creature->set_decision_strategy(std::move(decision_strategy));
  }
}
