#pragma once
#include <string>
#include "ItemTypes.hpp"

class ItemTypeTextKeys
{
  public:
    static std::string get_item_type_description_singular(const ItemType item_type);
    static std::string get_food_type(const FoodType food_type);

    static const std::string ITEM_TYPE_MISC;
    static const std::string ITEM_TYPE_WEAPONS;
    static const std::string ITEM_TYPE_ARMOURS;
    static const std::string ITEM_TYPE_POTIONS;
    static const std::string ITEM_TYPE_BOOKS;
    static const std::string ITEM_TYPE_SCROLLS;
    static const std::string ITEM_TYPE_WANDS;
    static const std::string ITEM_TYPE_STAVES;
    static const std::string ITEM_TYPE_RINGS;
    static const std::string ITEM_TYPE_AMULETS;
    static const std::string ITEM_TYPE_FOOD;
    static const std::string ITEM_TYPE_AMMUNITION;
    static const std::string ITEM_TYPE_PLANTS;
    static const std::string ITEM_TYPE_BOATS;
    static const std::string ITEM_TYPE_CURRENCY;
    static const std::string ITEM_TYPE_TOOLS;

    static const std::string FOOD_TYPE_VEGETABLE;
    static const std::string FOOD_TYPE_MEAT;
    static const std::string FOOD_TYPE_CARBS;
    static const std::string FOOD_TYPE_DAIRY;
    static const std::string FOOD_TYPE_OTHER;

  protected:
    ItemTypeTextKeys();
    ~ItemTypeTextKeys();

    static const std::string ITEM_TYPE_MISC_SINGULAR;
    static const std::string ITEM_TYPE_WEAPON_SINGULAR;
    static const std::string ITEM_TYPE_ARMOUR_SINGULAR;
    static const std::string ITEM_TYPE_POTION_SINGULAR;
    static const std::string ITEM_TYPE_BOOK_SINGULAR;
    static const std::string ITEM_TYPE_SCROLL_SINGULAR;
    static const std::string ITEM_TYPE_WAND_SINGULAR;
    static const std::string ITEM_TYPE_STAFF_SINGULAR;
    static const std::string ITEM_TYPE_RING_SINGULAR;
    static const std::string ITEM_TYPE_AMULET_SINGULAR;
    static const std::string ITEM_TYPE_FOOD_SINGULAR;
    static const std::string ITEM_TYPE_AMMUNITION_SINGULAR;
    static const std::string ITEM_TYPE_PLANT_SINGULAR;
    static const std::string ITEM_TYPE_BOAT_SINGULAR;
    static const std::string ITEM_TYPE_CURRENCY_SINGULAR;
    static const std::string ITEM_TYPE_TOOL_SINGULAR;
};
