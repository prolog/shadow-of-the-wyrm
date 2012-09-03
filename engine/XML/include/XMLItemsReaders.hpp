#pragma once
#include "XMLDataStructures.hpp"
#include "Ammunition.hpp"
#include "Armour.hpp"
#include "Food.hpp"
#include "Plant.hpp"
#include "Weapon.hpp"
#include "Wearable.hpp"
#include "XMLAmuletReader.hpp"
#include "XMLArmourReader.hpp"
#include "XMLBookReader.hpp"
#include "XMLBoatReader.hpp"
#include "XMLFoodReader.hpp"
#include "XMLPlantReader.hpp"
#include "XMLPotionReader.hpp"
#include "XMLRingReader.hpp"
#include "XMLScrollReader.hpp"
#include "XMLStaffReader.hpp"
#include "XMLWandReader.hpp"
#include "XMLWeaponsReaders.hpp"

class XMLItemsReader
{
  public:
    XMLItemsReader();
    ~XMLItemsReader();
    
    ItemMap get_items(const XMLNode& items_node);

  protected:
    ItemMap get_misc_items(const XMLNode& misc_items_node);
    ItemMap get_armour(const XMLNode& armour_node);
    ItemMap get_weapons(const XMLNode& weapons_node);
    ItemMap get_ranged_weapons(const XMLNode& ranged_weapons_node);
    ItemMap get_ammunition(const XMLNode& ammunition_node);
    ItemMap get_food(const XMLNode& foodstuffs_node);
    ItemMap get_plants(const XMLNode& plants_node);
    ItemMap get_boats(const XMLNode& boats_node);
    ItemMap get_potions(const XMLNode& potions_node);
    
    XMLItemReader item_reader;
    XMLAmuletReader amulet_reader;
    XMLArmourReader armour_reader;
    XMLBookReader book_reader;
    XMLBoatReader boat_reader;
    XMLWeaponsReader weapons_reader;
    XMLAmmunitionReader ammunition_reader;
    XMLFoodReader food_reader;
    XMLPlantReader plant_reader;
    XMLPotionReader potion_reader;
    XMLRingReader ring_reader;
    XMLScrollReader scroll_reader;
    XMLStaffReader staff_reader;
    XMLWandReader wand_reader;
};

