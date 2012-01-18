#pragma once
#include "XMLDataStructures.hpp"
#include "Item.hpp"

class XMLItemsReader
{
  public:
    XMLItemsReader();
    ~XMLItemsReader();
    
    ItemMap get_items(const XMLNode& items_node);

  protected:
    ItemMap get_misc_items(const XMLNode& misc_items_node);
    void parse_item(ItemPtr item, const XMLNode& item_node);
};

class XMLWeaponReader
{
  public:
  
  protected:
};

class XMLArmourReader
{
  public:
  
  protected:
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
