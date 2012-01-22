#pragma once
#include "XMLDataStructures.hpp"
#include "Armour.hpp"
#include "Weapon.hpp"
#include "Wearable.hpp"

class XMLItemReader
{
  public:
    XMLItemReader();
    virtual ~XMLItemReader();
    
    virtual void parse(ItemPtr item, const XMLNode& item_node);
    
  protected:
};

class XMLWearableReader : public XMLItemReader
{
  public:
    XMLWearableReader();
    ~XMLWearableReader();

  protected:
    void parse(WearablePtr wearable, const XMLNode& wearable_node);
};

class XMLWeaponsReader : public XMLWearableReader
{
  public:
    XMLWeaponsReader();
    ~XMLWeaponsReader();
    
  protected:
    friend class XMLItemsReader;
    void parse(WeaponPtr weapon, const XMLNode& ranged_weapon_node);
};

class XMLArmourReader : public XMLWearableReader
{
  public:
    XMLArmourReader();
    ~XMLArmourReader();
    
  protected:
    friend class XMLItemsReader;
    void parse(ArmourPtr armour, const XMLNode& armour_node);
};

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

    XMLItemReader item_reader;
    XMLArmourReader armour_reader;
    XMLWeaponsReader weapons_reader;
};

class XMLPotionReader
{
  public:
  
  protected:
};

class XMLBookReader
{
  public:
  
  protected:
};

class XMLScrollReader
{
  public:
  
  protected:
};

class XMLWandReader
{
  public:
  
  protected:
};

class XMLStaffReader
{
  public:
  
  protected:
};

class XMLRingReader
{
  public:
  
  protected:
};

class XMLAmuletReader
{
  public:
  
  protected:
};
