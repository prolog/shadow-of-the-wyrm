#pragma once
#include <string>

enum ItemType
{
  ITEM_TYPE_FIRST = 0,
  ITEM_TYPE_MISC = 0,
  ITEM_TYPE_WEAPON = 1,
  ITEM_TYPE_ARMOUR = 2,
  ITEM_TYPE_POTION = 3,
  ITEM_TYPE_BOOK = 4,
  ITEM_TYPE_SCROLL = 5,
  ITEM_TYPE_WAND = 6,
  ITEM_TYPE_STAFF = 7,
  ITEM_TYPE_RING = 8,
  ITEM_TYPE_AMULET = 9,
  ITEM_TYPE_FOOD = 10,
  ITEM_TYPE_AMMUNITION = 11,
  ITEM_TYPE_PLANT = 12,
  ITEM_TYPE_LAST = 13
};

enum ItemStatus
{
  ITEM_STATUS_UNCURSED = 0,
  ITEM_STATUS_BLESSED = 1,
  ITEM_STATUS_CURSED = 2
};

enum ItemIdentificationType
{
  ITEM_IDENTIFY_ON_GENERATION = 0,
  ITEM_IDENTIFY_ON_USE = 1,
  ITEM_IDENTIFY_ON_SUCCESSFUL_USE = 2,
  ITEM_IDENTIFY_ON_EQUIP = 3
};

// String constants used to identify items by things like generators.
class ItemIdKeys
{
  public:
  public:
    static std::string ITEM_ID_BRANCH;
    static std::string ITEM_ID_ROCK;
    static std::string ITEM_ID_KINGFLOWER;
    static std::string ITEM_ID_FIDDLEHEAD_GREEN;
    static std::string ITEM_ID_FERN;
    static std::string ITEM_ID_WILDFLOWER_1;
    static std::string ITEM_ID_WILDFLOWER_2;
    static std::string ITEM_ID_WILDFLOWER_3;
    static std::string ITEM_ID_WILDFLOWER_4;
    static std::string ITEM_ID_WILDFLOWER_5;
    static std::string ITEM_ID_WILDFLOWER_6;
    static std::string ITEM_ID_VEGETABLE_1;
    static std::string ITEM_ID_VEGETABLE_2;
    static std::string ITEM_ID_VEGETABLE_3;
    static std::string ITEM_ID_VEGETABLE_4;
    static std::string ITEM_ID_VEGETABLE_5;
    static std::string ITEM_ID_VEGETABLE_6;

  protected:
    ItemIdKeys();
    ~ItemIdKeys();
};
