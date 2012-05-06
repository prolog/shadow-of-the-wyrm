#include <vector>
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "CreatureGenerationValues.hpp"
#include "XMLCreaturesReader.hpp"
#include "DecisionStrategyFactory.hpp"

using boost::make_shared;
using namespace std;

pair<CreatureMap, CreatureGenerationValuesMap> XMLCreaturesReader::get_creatures(const XMLNode& xml_configuration_creatures_node)
{
  pair<CreatureMap, CreatureGenerationValuesMap> creature_values;
  CreatureMap creatures;
  CreatureGenerationValuesMap cgv_map;

  if (!xml_configuration_creatures_node.is_null())
  {
    vector<XMLNode> creature_nodes = XMLUtils::get_elements_by_local_name(xml_configuration_creatures_node, "Creature");

    BOOST_FOREACH(XMLNode creature_node, creature_nodes)
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
    creature = make_shared<Creature>();
    creature_data.first = creature;
      
    // The creature ID for the templates gives a unique value - for each individual
    // creature, a GUID will be genreated during creation of that creature.
    string id = XMLUtils::get_attribute_value(creature_node, "id");
    creature->set_id(id);
    
    // Typically a single word or phrase: bat, orc child, troll pedestrian, etc.
    string short_description_sid = XMLUtils::get_child_node_value(creature_node, "ShortDescriptionSID");
    creature->set_short_description_sid(short_description_sid);
    
    // A longer description, which can be used as part of a sentence:
    // "a goblin warrior", "some grey ooze", etc.
    string description_sid = XMLUtils::get_child_node_value(creature_node, "DescriptionSID");
    creature->set_description_sid(description_sid);
    
    // A decision strategy for the creature, which provides a set of actions (move, attack, and so on)
    // as appropriate.  ImmobileDecisionStrategy, for example, disallows movement, and is used for
    // immobile creatures (such as slimes, etc.)
    string decision_strategy_id = XMLUtils::get_child_node_value(creature_node, "DecisionStrategy");
    DecisionStrategyPtr decision_strategy = DecisionStrategyFactory::create_decision_strategy(decision_strategy_id);
    creature->set_decision_strategy(decision_strategy);
    
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
    }
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
    XMLNode allowable_terrain_types_node = XMLUtils::get_next_element_by_local_name(creature_generation_values_node, "AllowableTerrainTypes");
    
    // The tile (map) types that the creature can be generated for. (dungeon, forest, mountains, etc)
    if (!allowable_terrain_types_node.is_null())
    {
      vector<XMLNode> allowable_terrain_nodes = XMLUtils::get_elements_by_local_name(allowable_terrain_types_node, "TileType");

      BOOST_FOREACH(XMLNode terrain_node, allowable_terrain_nodes)
      {
        TileType att = static_cast<TileType>(XMLUtils::get_node_int_value(terrain_node, TILE_TYPE_UNDEFINED));
        cgv.add_allowable_terrain_type(att);
      }
    }
    
    // Danger level
    uint danger_level = XMLUtils::get_child_node_int_value(creature_generation_values_node, "DangerLevel");
    cgv.set_danger_level(danger_level);
    
    // Creature rarity
    Rarity rarity = static_cast<Rarity>(XMLUtils::get_child_node_int_value(creature_generation_values_node, "Rarity"));
    cgv.set_rarity(rarity);
  }
  
  return cgv;
}
