#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "MaterialFactory.hpp"
#include "XMLItemsReaders.hpp"
#include "MiscItem.hpp"

using namespace std;

XMLItemsReader::XMLItemsReader()
{
}

XMLItemsReader::~XMLItemsReader()
{
}

// Gets all the items of the various types and returns them in a map,
// keyed by their ID (specified in the XML).
pair<ItemMap, GenerationValuesMap> XMLItemsReader::get_items(const XMLNode& items_node)
{
  ItemMap items;
  GenerationValuesMap igv_map;
  
  if (!items_node.is_null())
  {
    XMLNode armours_node = XMLUtils::get_next_element_by_local_name(items_node, "Armours");
    
    if (!armours_node.is_null())
    {
      pair<ItemMap, GenerationValuesMap> armours = get_armour(armours_node);
      items.insert(armours.first.begin(), armours.first.end());
      igv_map.insert(armours.second.begin(), armours.second.end());
    }
    
    XMLNode weapons_node = XMLUtils::get_next_element_by_local_name(items_node, "Weapons");
    
    if (!weapons_node.is_null())
    {
      pair<ItemMap, GenerationValuesMap> weapons = get_weapons(weapons_node);
      items.insert(weapons.first.begin(), weapons.first.end());
      igv_map.insert(weapons.second.begin(), weapons.second.end());
    }
    
    XMLNode ranged_weapons_node = XMLUtils::get_next_element_by_local_name(items_node, "RangedWeapons");
    
    if (!ranged_weapons_node.is_null())
    {
      pair<ItemMap, GenerationValuesMap> ranged_weapons = get_ranged_weapons(ranged_weapons_node);
      items.insert(ranged_weapons.first.begin(), ranged_weapons.first.end());
      igv_map.insert(ranged_weapons.second.begin(), ranged_weapons.second.end());
    }
    
    XMLNode ammunition_node = XMLUtils::get_next_element_by_local_name(items_node, "Ammunition");
    
    if (!ammunition_node.is_null())
    {
      pair<ItemMap, GenerationValuesMap> ammunition = get_ammunition(ammunition_node);
      items.insert(ammunition.first.begin(), ammunition.first.end());
      igv_map.insert(ammunition.second.begin(), ammunition.second.end());
    }
    
    XMLNode food_node = XMLUtils::get_next_element_by_local_name(items_node, "Foodstuffs");
    
    if (!food_node.is_null())
    {
      pair<ItemMap, GenerationValuesMap> food = get_food(food_node);
      items.insert(food.first.begin(), food.first.end());
      igv_map.insert(food.second.begin(), food.second.end());
    }
    
    XMLNode plants_node = XMLUtils::get_next_element_by_local_name(items_node, "Plants");
    
    if (!plants_node.is_null())
    {
      pair<ItemMap, GenerationValuesMap> plants = get_plants(plants_node);
      items.insert(plants.first.begin(), plants.first.end());
      igv_map.insert(plants.second.begin(), plants.second.end());
    }
    
    XMLNode boats_node = XMLUtils::get_next_element_by_local_name(items_node, "Boats");
    
    if (!boats_node.is_null())
    {
      pair<ItemMap, GenerationValuesMap> boats = get_boats(boats_node);
      items.insert(boats.first.begin(), boats.first.end());
      igv_map.insert(boats.second.begin(), boats.second.end());
    }
    
    XMLNode potions_node = XMLUtils::get_next_element_by_local_name(items_node, "Potions");
    
    if (!potions_node.is_null())
    {
      pair<ItemMap, GenerationValuesMap> potions = get_potions(potions_node);
      items.insert(potions.first.begin(), potions.first.end());
      igv_map.insert(potions.second.begin(), potions.second.end());
    }
    
    XMLNode scrolls_node = XMLUtils::get_next_element_by_local_name(items_node, "Scrolls");
    
    if (!scrolls_node.is_null())
    {
      pair<ItemMap, GenerationValuesMap> scrolls = get_scrolls(scrolls_node);
      items.insert(scrolls.first.begin(), scrolls.first.end());
      igv_map.insert(scrolls.second.begin(), scrolls.second.end());
    }
    
    XMLNode currencies_node = XMLUtils::get_next_element_by_local_name(items_node, "Currencies");
    
    if (!currencies_node.is_null())
    {
      pair<ItemMap, GenerationValuesMap> currencies = get_currencies(currencies_node);
      items.insert(currencies.first.begin(), currencies.first.end());
      igv_map.insert(currencies.second.begin(), currencies.second.end());
    }
    
    XMLNode tools_node = XMLUtils::get_next_element_by_local_name(items_node, "Tools");

    if (!tools_node.is_null())
    {
      pair<ItemMap, GenerationValuesMap> tools = get_tools(tools_node);
      items.insert(tools.first.begin(), tools.first.end());
      igv_map.insert(tools.second.begin(), tools.second.end());
    }

    XMLNode wands_node = XMLUtils::get_next_element_by_local_name(items_node, "Wands");

    if (!wands_node.is_null())
    {
      pair<ItemMap, GenerationValuesMap> wands = get_wands(wands_node);
      items.insert(wands.first.begin(), wands.first.end());
      igv_map.insert(wands.second.begin(), wands.second.end());
    }

    XMLNode spellbooks_node = XMLUtils::get_next_element_by_local_name(items_node, "Spellbooks");

    if (!spellbooks_node.is_null())
    {
      pair<ItemMap, GenerationValuesMap> spellbooks = get_spellbooks(spellbooks_node);
      items.insert(spellbooks.first.begin(), spellbooks.first.end());
      igv_map.insert(spellbooks.second.begin(), spellbooks.second.end());
    }

    XMLNode misc_items_node = XMLUtils::get_next_element_by_local_name(items_node, "MiscItems");
    
    if (!misc_items_node.is_null())
    {
      std::pair<ItemMap, GenerationValuesMap> misc_items = get_misc_items(misc_items_node);
      items.insert(misc_items.first.begin(), misc_items.first.end());
      igv_map.insert(misc_items.second.begin(), misc_items.second.end());
    }
  }

  pair<ItemMap, GenerationValuesMap> item_pair;
  item_pair.first = items;
  item_pair.second = igv_map;
  
  return item_pair;
}

std::pair<ItemMap, GenerationValuesMap> XMLItemsReader::get_misc_items(const XMLNode& misc_items_node)
{
  ItemMap misc_items_map;
  GenerationValuesMap igv_map;
  pair<ItemMap, GenerationValuesMap> misc_items;
  
  if (!misc_items_node.is_null())
  {
    vector<XMLNode> misc_items_nodes = XMLUtils::get_elements_by_local_name(misc_items_node, "Item");
    
    BOOST_FOREACH(XMLNode node, misc_items_nodes)
    {
      if (!node.is_null())
      {
        ItemPtr item = boost::make_shared<MiscItem>();
        GenerationValues igv;
        item_reader.parse(item, igv, node);
        misc_items_map.insert(make_pair(item->get_id(), item));  
        igv_map.insert(make_pair(item->get_id(), igv));
      }
    }
  }
  
  misc_items.first = misc_items_map;
  misc_items.second = igv_map;

  return misc_items;
}

pair<ItemMap, GenerationValuesMap> XMLItemsReader::get_armour(const XMLNode& armours_node)
{
  pair<ItemMap, GenerationValuesMap> armour;
  ItemMap armour_map;
  GenerationValuesMap igv_map;
  
  if (!armours_node.is_null())
  {
    vector<XMLNode> armour_nodes = XMLUtils::get_elements_by_local_name(armours_node, "Armour");
    
    BOOST_FOREACH(XMLNode node, armour_nodes)
    {
      if (!node.is_null())
      {
        ArmourPtr armour = boost::make_shared<Armour>();
        GenerationValues igv;
        armour_reader.parse(armour, igv, node);
        armour_map.insert(make_pair(armour->get_id(), armour));
        igv_map.insert(make_pair(armour->get_id(), igv));
      }
    }
  }
  
  armour.first = armour_map;
  armour.second = igv_map;
  return armour;
}

pair<ItemMap, GenerationValuesMap> XMLItemsReader::get_weapons(const XMLNode& weapons_node)
{
  pair<ItemMap, GenerationValuesMap> weapons;
  ItemMap weapons_map;
  GenerationValuesMap igv_map;
  
  if (!weapons_node.is_null())
  {
    vector<XMLNode> weapons_nodes = XMLUtils::get_elements_by_local_name(weapons_node, "Weapon");
    
    BOOST_FOREACH(XMLNode node, weapons_nodes)
    {
      MeleeWeaponPtr weapon = boost::make_shared<MeleeWeapon>();
      GenerationValues igv;
      weapons_reader.parse(weapon, igv, node);
      weapons_map.insert(make_pair(weapon->get_id(), weapon));
      igv_map.insert(make_pair(weapon->get_id(), igv));
    }
  }

  weapons.first = weapons_map;
  weapons.second = igv_map;
  return weapons;
}

pair<ItemMap, GenerationValuesMap> XMLItemsReader::get_ranged_weapons(const XMLNode& ranged_weapons_node)
{
  pair<ItemMap, GenerationValuesMap> ranged_weapons;
  ItemMap weapons_map;
  GenerationValuesMap igv_map;
  
  if (!ranged_weapons_node.is_null())
  {
    vector<XMLNode> ranged_weapons_nodes = XMLUtils::get_elements_by_local_name(ranged_weapons_node, "Weapon");
    
    BOOST_FOREACH(XMLNode node, ranged_weapons_nodes)
    {
      RangedWeaponPtr ranged_weapon = boost::make_shared<RangedWeapon>();
      GenerationValues igv;
      weapons_reader.parse(ranged_weapon, igv, node);
      weapons_map.insert(make_pair(ranged_weapon->get_id(), ranged_weapon));
      igv_map.insert(make_pair(ranged_weapon->get_id(), igv));
    }
  }
  
  ranged_weapons.first = weapons_map;
  ranged_weapons.second = igv_map;
  return ranged_weapons;
}

pair<ItemMap, GenerationValuesMap> XMLItemsReader::get_ammunition(const XMLNode& ammunition_node)
{
  pair<ItemMap, GenerationValuesMap> ammunition;
  ItemMap ammunition_map;
  GenerationValuesMap igv_map;
  
  if (!ammunition_node.is_null())
  {
    vector<XMLNode> missiles_nodes = XMLUtils::get_elements_by_local_name(ammunition_node, "Missile");
    
    BOOST_FOREACH(XMLNode node, missiles_nodes)
    {
      WeaponPtr ammunition = boost::make_shared<Ammunition>();
      GenerationValues igv;
      ammunition_reader.parse(ammunition, igv, node);
      ammunition_map.insert(make_pair(ammunition->get_id(), ammunition));
      igv_map.insert(make_pair(ammunition->get_id(), igv));
    }
  }
  
  ammunition.first = ammunition_map;
  ammunition.second = igv_map;
  return ammunition;
}

pair<ItemMap, GenerationValuesMap> XMLItemsReader::get_food(const XMLNode& food_node)
{
  pair<ItemMap, GenerationValuesMap> food;
  ItemMap food_map;
  GenerationValuesMap igv_map;
  
  if (!food_node.is_null())
  {
    vector<XMLNode> food_nodes = XMLUtils::get_elements_by_local_name(food_node, "Food");
    
    BOOST_FOREACH(XMLNode node, food_nodes)
    {
      FoodPtr food = boost::make_shared<Food>();
      GenerationValues igv;
      food_reader.parse(food, igv, node);
      food_map.insert(make_pair(food->get_id(), food));
      igv_map.insert(make_pair(food->get_id(), igv));
    }
  }
  
  food.first = food_map;
  food.second = igv_map;
  return food;
}

pair<ItemMap, GenerationValuesMap> XMLItemsReader::get_plants(const XMLNode& plants_node)
{
  pair<ItemMap, GenerationValuesMap> plants;
  ItemMap plants_map;
  GenerationValuesMap igv_map;
  
  if (!plants_node.is_null())
  {
    vector<XMLNode> plants_nodes = XMLUtils::get_elements_by_local_name(plants_node, "Plant");
    
    BOOST_FOREACH(XMLNode node, plants_nodes)
    {
      PlantPtr plant = boost::make_shared<Plant>();
      GenerationValues gv;
      plant_reader.parse(plant, gv, node);
      plants_map.insert(make_pair(plant->get_id(), plant));
      igv_map.insert(make_pair(plant->get_id(), gv));
    }
  }
  
  plants.first = plants_map;
  plants.second = igv_map;
  return plants;
}

pair<ItemMap, GenerationValuesMap> XMLItemsReader::get_boats(const XMLNode& boats_node)
{
  pair<ItemMap, GenerationValuesMap> boats;
  ItemMap boats_map;
  GenerationValuesMap igv_map;
  
  if (!boats_node.is_null())
  {
    vector<XMLNode> boats_nodes = XMLUtils::get_elements_by_local_name(boats_node, "Boat");
    
    BOOST_FOREACH(XMLNode node, boats_nodes)
    {
      BoatPtr boat = boost::make_shared<Boat>();
      GenerationValues igv;
      boat_reader.parse(boat, igv, node);
      boats_map.insert(make_pair(boat->get_id(), boat));
      igv_map.insert(make_pair(boat->get_id(), igv));
    }
  }
  
  boats.first = boats_map;
  boats.second = igv_map;
  return boats;
}

pair<ItemMap, GenerationValuesMap> XMLItemsReader::get_potions(const XMLNode& potions_node)
{
  pair<ItemMap, GenerationValuesMap> potions;
  ItemMap potions_map;
  GenerationValuesMap igv_map;
  
  if (!potions_node.is_null())
  {
    vector <XMLNode> potions_nodes = XMLUtils::get_elements_by_local_name(potions_node, "Potion");
    
    BOOST_FOREACH(XMLNode node, potions_nodes)
    {
      PotionPtr potion = boost::make_shared<Potion>();
      GenerationValues igv;
      potion_reader.parse(potion, igv, node);
      potions_map.insert(make_pair(potion->get_id(), potion));
      igv_map.insert(make_pair(potion->get_id(), igv));
    }
  }
  
  potions.first = potions_map;
  potions.second = igv_map;
  return potions;
}

pair<ItemMap, GenerationValuesMap> XMLItemsReader::get_scrolls(const XMLNode& scrolls_node)
{
  pair<ItemMap, GenerationValuesMap> scrolls;
  ItemMap scrolls_map;
  GenerationValuesMap igv_map;
  
  if (!scrolls_node.is_null())
  {
    vector <XMLNode> scrolls_nodes = XMLUtils::get_elements_by_local_name(scrolls_node, "Scroll");

    BOOST_FOREACH(XMLNode node, scrolls_nodes)
    {
      ScrollPtr scroll = boost::make_shared<Scroll>();
      GenerationValues igv;
      scroll_reader.parse(scroll, igv, node);
      scrolls_map.insert(make_pair(scroll->get_id(), scroll));
      igv_map.insert(make_pair(scroll->get_id(), igv));
    }
  }
  
  scrolls.first = scrolls_map;
  scrolls.second = igv_map;
  return scrolls;
}

pair<ItemMap, GenerationValuesMap> XMLItemsReader::get_currencies(const XMLNode& currencies_node)
{
  pair<ItemMap, GenerationValuesMap> currencies;
  ItemMap currencies_map;
  GenerationValuesMap igv_map;
  
  if (!currencies_node.is_null())
  {
    vector<XMLNode> currencies_nodes = XMLUtils::get_elements_by_local_name(currencies_node, "Currency");
    
    BOOST_FOREACH(XMLNode node, currencies_nodes)
    {
      CurrencyPtr currency = boost::make_shared<Currency>();
      GenerationValues igv;
      item_reader.parse(currency, igv, node);
      currencies_map.insert(make_pair(currency->get_id(), currency));
      igv_map.insert(make_pair(currency->get_id(), igv));
    }
  }

  currencies.first = currencies_map;
  currencies.second = igv_map;
  return currencies;;
}

pair<ItemMap, GenerationValuesMap> XMLItemsReader::get_tools(const XMLNode& tools_node)
{
  pair<ItemMap, GenerationValuesMap> tools;
  ItemMap tools_map;
  GenerationValuesMap igv_map;

  if (!tools_node.is_null())
  {
    vector<XMLNode> tools_nodes = XMLUtils::get_elements_by_local_name(tools_node, "Tool");

    BOOST_FOREACH(XMLNode node, tools_nodes)
    {
      ToolPtr tool = boost::make_shared<Tool>();
      GenerationValues igv;
      tool_reader.parse(tool, igv, node);
      tools_map.insert(make_pair(tool->get_id(), tool));
      igv_map.insert(make_pair(tool->get_id(), igv));
    }
  }

  tools.first = tools_map;
  tools.second = igv_map;
  return tools;
}

pair<ItemMap, GenerationValuesMap> XMLItemsReader::get_wands(const XMLNode& wands_node)
{
  pair<ItemMap, GenerationValuesMap> wands;
  ItemMap wands_map;
  GenerationValuesMap igv_map;

  if (!wands_node.is_null())
  {
    vector<XMLNode> wands_nodes = XMLUtils::get_elements_by_local_name(wands_node, "Wand");

    BOOST_FOREACH(XMLNode node, wands_nodes)
    {
      WandPtr wand = boost::make_shared<Wand>();
      GenerationValues igv;
      wand_reader.parse(wand, igv, node);
      wands_map.insert(make_pair(wand->get_id(), wand));
      igv_map.insert(make_pair(wand->get_id(), igv));
    }
  }

  wands.first = wands_map;
  wands.second = igv_map;
  return wands;
}

pair<ItemMap, GenerationValuesMap> XMLItemsReader::get_spellbooks(const XMLNode& spellbooks_node)
{
  pair<ItemMap, GenerationValuesMap> spellbooks;
  ItemMap spellbook_map;
  GenerationValuesMap igv_map;

  if (!spellbooks_node.is_null())
  {
    vector<XMLNode> spellbooks_nodes = XMLUtils::get_elements_by_local_name(spellbooks_node, "Spellbook");

    BOOST_FOREACH(XMLNode node, spellbooks_nodes)
    {
      SpellbookPtr book = boost::make_shared<Spellbook>();
      GenerationValues igv;
      spellbook_reader.parse(book, igv, node);
      spellbook_map.insert(make_pair(book->get_id(), book));
      igv_map.insert(make_pair(book->get_id(), igv));
    }
  }

  spellbooks.first = spellbook_map;
  spellbooks.second = igv_map;

  return spellbooks;
}