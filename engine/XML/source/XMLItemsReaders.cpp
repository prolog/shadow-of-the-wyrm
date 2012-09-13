#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "MaterialFactory.hpp"
#include "XMLItemsReaders.hpp"
#include "MiscItem.hpp"

using namespace std;
using boost::make_shared;

XMLItemsReader::XMLItemsReader()
{
}

XMLItemsReader::~XMLItemsReader()
{
}

// Gets all the items of the various types and returns them in a map,
// keyed by their ID (specified in the XML).
ItemMap XMLItemsReader::get_items(const XMLNode& items_node)
{
  ItemMap items;
  
  if (!items_node.is_null())
  {
    XMLNode armours_node = XMLUtils::get_next_element_by_local_name(items_node, "Armours");
    
    if (!armours_node.is_null())
    {
      ItemMap armours_map = get_armour(armours_node);
      items.insert(armours_map.begin(), armours_map.end());
    }
    
    XMLNode weapons_node = XMLUtils::get_next_element_by_local_name(items_node, "Weapons");
    
    if (!weapons_node.is_null())
    {
      ItemMap weapons_map = get_weapons(weapons_node);
      items.insert(weapons_map.begin(), weapons_map.end());
    }
    
    XMLNode ranged_weapons_node = XMLUtils::get_next_element_by_local_name(items_node, "RangedWeapons");
    
    if (!ranged_weapons_node.is_null())
    {
      ItemMap ranged_weapons_map = get_ranged_weapons(ranged_weapons_node);
      items.insert(ranged_weapons_map.begin(), ranged_weapons_map.end());
    }
    
    XMLNode ammunition_node = XMLUtils::get_next_element_by_local_name(items_node, "Ammunition");
    
    if (!ammunition_node.is_null())
    {
      ItemMap ammunition_map = get_ammunition(ammunition_node);
      items.insert(ammunition_map.begin(), ammunition_map.end());
    }
    
    XMLNode food_node = XMLUtils::get_next_element_by_local_name(items_node, "Foodstuffs");
    
    if (!food_node.is_null())
    {
      ItemMap food_map = get_food(food_node);
      items.insert(food_map.begin(), food_map.end());
    }
    
    XMLNode plants_node = XMLUtils::get_next_element_by_local_name(items_node, "Plants");
    
    if (!plants_node.is_null())
    {
      ItemMap plants_map = get_plants(plants_node);
      items.insert(plants_map.begin(), plants_map.end());
    }
    
    XMLNode boats_node = XMLUtils::get_next_element_by_local_name(items_node, "Boats");
    
    if (!boats_node.is_null())
    {
      ItemMap boats_map = get_boats(boats_node);
      items.insert(boats_map.begin(), boats_map.end());
    }
    
    XMLNode potions_node = XMLUtils::get_next_element_by_local_name(items_node, "Potions");
    
    if (!potions_node.is_null())
    {
      ItemMap potions_map = get_potions(potions_node);
      items.insert(potions_map.begin(), potions_map.end());
    }
    
    XMLNode scrolls_node = XMLUtils::get_next_element_by_local_name(items_node, "Scrolls");
    
    if (!scrolls_node.is_null())
    {
      ItemMap scrolls_map = get_scrolls(scrolls_node);
      items.insert(scrolls_map.begin(), scrolls_map.end());
    }
    
    XMLNode misc_items_node = XMLUtils::get_next_element_by_local_name(items_node, "MiscItems");
    
    if (!misc_items_node.is_null())
    {
      ItemMap misc_items_map = get_misc_items(misc_items_node);
      items.insert(misc_items_map.begin(), misc_items_map.end());
    }
  }
  
  return items;
}

ItemMap XMLItemsReader::get_misc_items(const XMLNode& misc_items_node)
{
  ItemMap misc_items;
  
  if (!misc_items_node.is_null())
  {
    vector<XMLNode> misc_items_nodes = XMLUtils::get_elements_by_local_name(misc_items_node, "Item");
    
    BOOST_FOREACH(XMLNode node, misc_items_nodes)
    {
      if (!node.is_null())
      {
        ItemPtr item = make_shared<MiscItem>();
        item_reader.parse(item, node);
        misc_items.insert(make_pair(item->get_id(), item));  
      }
    }
  }
  
  return misc_items;
}

ItemMap XMLItemsReader::get_armour(const XMLNode& armours_node)
{
  ItemMap armour_map;
  
  if (!armours_node.is_null())
  {
    vector<XMLNode> armour_nodes = XMLUtils::get_elements_by_local_name(armours_node, "Armour");
    
    BOOST_FOREACH(XMLNode node, armour_nodes)
    {
      if (!node.is_null())
      {
        ArmourPtr armour = make_shared<Armour>();
        armour_reader.parse(armour, node);
        armour_map.insert(make_pair(armour->get_id(), armour));
      }
    }
  }
  
  return armour_map;
}

ItemMap XMLItemsReader::get_weapons(const XMLNode& weapons_node)
{
  ItemMap weapons_map;
  
  if (!weapons_node.is_null())
  {
    vector<XMLNode> weapons_nodes = XMLUtils::get_elements_by_local_name(weapons_node, "Weapon");
    
    BOOST_FOREACH(XMLNode node, weapons_nodes)
    {
      MeleeWeaponPtr weapon = make_shared<MeleeWeapon>();
      weapons_reader.parse(weapon, node);
      weapons_map.insert(make_pair(weapon->get_id(), weapon));
    }
  }

  return weapons_map;
}

ItemMap XMLItemsReader::get_ranged_weapons(const XMLNode& ranged_weapons_node)
{
  ItemMap weapons_map;
  
  if (!ranged_weapons_node.is_null())
  {
    vector<XMLNode> ranged_weapons_nodes = XMLUtils::get_elements_by_local_name(ranged_weapons_node, "Weapon");
    
    BOOST_FOREACH(XMLNode node, ranged_weapons_nodes)
    {
      RangedWeaponPtr ranged_weapon = make_shared<RangedWeapon>();
      weapons_reader.parse(ranged_weapon, node);
      weapons_map.insert(make_pair(ranged_weapon->get_id(), ranged_weapon));
    }
  }
  
  return weapons_map;
}

ItemMap XMLItemsReader::get_ammunition(const XMLNode& ammunition_node)
{
  ItemMap ammunition_map;
  
  if (!ammunition_node.is_null())
  {
    vector<XMLNode> missiles_nodes = XMLUtils::get_elements_by_local_name(ammunition_node, "Missile");
    
    BOOST_FOREACH(XMLNode node, missiles_nodes)
    {
      WeaponPtr ammunition = make_shared<MeleeWeapon>();
      ammunition_reader.parse(ammunition, node);
      ammunition_map.insert(make_pair(ammunition->get_id(), ammunition));
    }
  }
  
  return ammunition_map;
}

ItemMap XMLItemsReader::get_food(const XMLNode& food_node)
{
  ItemMap food_map;
  
  if (!food_node.is_null())
  {
    vector<XMLNode> food_nodes = XMLUtils::get_elements_by_local_name(food_node, "Food");
    
    BOOST_FOREACH(XMLNode node, food_nodes)
    {
      FoodPtr food = make_shared<Food>();
      food_reader.parse(food, node);
      food_map.insert(make_pair(food->get_id(), food));
    }
  }
  
  return food_map;
}

ItemMap XMLItemsReader::get_plants(const XMLNode& plants_node)
{
  ItemMap plants_map;
  
  if (!plants_node.is_null())
  {
    vector<XMLNode> plants_nodes = XMLUtils::get_elements_by_local_name(plants_node, "Plant");
    
    BOOST_FOREACH(XMLNode node, plants_nodes)
    {
      PlantPtr plant = make_shared<Plant>();
      plant_reader.parse(plant, node);
      plants_map.insert(make_pair(plant->get_id(), plant));
    }
  }
  
  return plants_map;
}

ItemMap XMLItemsReader::get_boats(const XMLNode& boats_node)
{
  ItemMap boats_map;
  
  if (!boats_node.is_null())
  {
    vector<XMLNode> boats_nodes = XMLUtils::get_elements_by_local_name(boats_node, "Boat");
    
    BOOST_FOREACH(XMLNode node, boats_nodes)
    {
      BoatPtr boat = make_shared<Boat>();
      boat_reader.parse(boat, node);
      boats_map.insert(make_pair(boat->get_id(), boat));
    }
  }
  
  return boats_map;
}

ItemMap XMLItemsReader::get_potions(const XMLNode& potions_node)
{
  ItemMap potions_map;
  
  if (!potions_node.is_null())
  {
    vector <XMLNode> potions_nodes = XMLUtils::get_elements_by_local_name(potions_node, "Potion");
    
    BOOST_FOREACH(XMLNode node, potions_nodes)
    {
      PotionPtr potion = make_shared<Potion>();
      potion_reader.parse(potion, node);
      potions_map.insert(make_pair(potion->get_id(), potion));
    }
  }
  
  return potions_map;
}

ItemMap XMLItemsReader::get_scrolls(const XMLNode& scrolls_node)
{
  ItemMap scrolls_map;
  
  if (!scrolls_node.is_null())
  {
    vector <XMLNode> scrolls_nodes = XMLUtils::get_elements_by_local_name(scrolls_node, "Scroll");

    BOOST_FOREACH(XMLNode node, scrolls_nodes)
    {
      ScrollPtr scroll = make_shared<Scroll>();
      scroll_reader.parse(scroll, node);
      scrolls_map.insert(make_pair(scroll->get_id(), scroll));
    }
  }
  
  return scrolls_map;
}
