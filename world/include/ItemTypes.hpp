#pragma once
#include <vector>
#include <string>

// Item types for the C++ code.
enum struct ItemType
{
  ITEM_TYPE_NULL = -1,
  ITEM_TYPE_FIRST = 0,
  ITEM_TYPE_MISC = 0,
  ITEM_TYPE_WEAPON = 1,
  ITEM_TYPE_ARMOUR = 2,
  ITEM_TYPE_POTION = 3,
  ITEM_TYPE_SPELLBOOK = 4,
  ITEM_TYPE_SCROLL = 5,
  ITEM_TYPE_WAND = 6,
  ITEM_TYPE_STAFF = 7,
  ITEM_TYPE_RING = 8,
  ITEM_TYPE_AMULET = 9,
  ITEM_TYPE_FOOD = 10,
  ITEM_TYPE_AMMUNITION = 11,
  ITEM_TYPE_PLANT = 12,
  ITEM_TYPE_BOAT = 13,
  ITEM_TYPE_CURRENCY = 14,
  ITEM_TYPE_TOOL = 15,
  ITEM_TYPE_LAST = 16
};

// Item types for the Lua code.
constexpr auto CITEM_TYPE_MISC = 0;
constexpr auto CITEM_TYPE_WEAPON = 1;
constexpr auto CITEM_TYPE_ARMOUR = 2;
constexpr auto CITEM_TYPE_POTION = 3;
constexpr auto CITEM_TYPE_SPELLBOOK = 4;
constexpr auto CITEM_TYPE_SCROLL = 5;
constexpr auto CITEM_TYPE_WAND = 6;
constexpr auto CITEM_TYPE_STAFF = 7;
constexpr auto CITEM_TYPE_RING = 8;
constexpr auto CITEM_TYPE_AMULET = 9;
constexpr auto CITEM_TYPE_FOOD = 10;
constexpr auto CITEM_TYPE_AMMUNITION = 11;
constexpr auto CITEM_TYPE_PLANT = 12;
constexpr auto CITEM_TYPE_BOAT = 13;
constexpr auto CITEM_TYPE_CURRENCY = 14;
constexpr auto CITEM_TYPE_TOOL = 15;

enum struct ItemStatus
{
  ITEM_STATUS_UNCURSED = 0,
  ITEM_STATUS_BLESSED = 1,
  ITEM_STATUS_CURSED = 2
};

enum struct ItemIdentificationType
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
    static const std::string ITEM_ID_LUMBER;
    static const std::string ITEM_ID_STONE_BLOCK;
    static const std::string ITEM_ID_SOD_BRICK;
    static const std::string ITEM_ID_CLAY_POT;
    static const std::string ITEM_ID_CURRENCY;
    static const std::string ITEM_ID_BRANCH;
    static const std::string ITEM_ID_BOUGH;
    static const std::string ITEM_ID_DIRT;
    static const std::string ITEM_ID_CLAY;
    static const std::string ITEM_ID_CLAY_SHOT;
    static const std::string ITEM_ID_FIRE_BOMB;
    static const std::string ITEM_ID_SHADOW_BOMB;
    static const std::string ITEM_ID_ROCK;
    static const std::string ITEM_ID_STONE;
    static const std::string ITEM_ID_HUGE_ROCK;
    static const std::string ITEM_ID_MAGICI_SHARD;
    static const std::string ITEM_ID_PRIMORDIAL_ESSENCE;
    static const std::string ITEM_ID_COAL;
    static const std::string ITEM_ID_LUMP_GOLD;
    static const std::string ITEM_ID_BOG_IRON;
    static const std::string ITEM_ID_IRON_INGOT;
    static const std::string ITEM_ID_STEEL_INGOT;
    static const std::string ITEM_ID_FIDDLEHEAD_GREEN;
    static const std::string ITEM_ID_FERN;
    static const std::string ITEM_ID_PILE_OF_BONES;
    static const std::string ITEM_ID_INTACT_SKELETON;
    static const std::string ITEM_ID_WHITEFLOWER;
    static const std::string ITEM_ID_WILDFLOWER_1;
    static const std::string ITEM_ID_WILDFLOWER_2;
    static const std::string ITEM_ID_WILDFLOWER_3;
    static const std::string ITEM_ID_WILDFLOWER_4;
    static const std::string ITEM_ID_WILDFLOWER_5;
    static const std::string ITEM_ID_WILDFLOWER_6;
    static const std::string ITEM_ID_VEGETABLE_1;
    static const std::string ITEM_ID_VEGETABLE_2;
    static const std::string ITEM_ID_VEGETABLE_3;
    static const std::string ITEM_ID_VEGETABLE_4;
    static const std::string ITEM_ID_VEGETABLE_5;
    static const std::string ITEM_ID_VEGETABLE_6;
    static const std::string ITEM_ID_GOLDEN_APPLE;
    static const std::string ITEM_ID_SILVER_APPLE;
    static const std::string ITEM_ID_SHOVEL;
    static const std::string ITEM_ID_PICK_AXE;

    // Foragables
    static const std::string ITEM_ID_ROOT;
    static const std::string ITEM_ID_BERRIES;
    static const std::string ITEM_ID_KELP;
    static const std::string ITEM_ID_WHEAT;

    // Herbs and plants
    static const std::string ITEM_ID_WHITE_BASIL; // cures poison
    static const std::string ITEM_ID_STONEFLOWER; // cures petrification
    static const std::string ITEM_ID_VERBENA; // increases AP
    static const std::string ITEM_ID_BLACKROOT; // increases HP
    static const std::string ITEM_ID_VOXFLOWER; // restores the voice
    
    // Fishing stuff
    static const std::string ITEM_ID_FISHING_ROD;
    static const std::string ITEM_ID_CORACLE;

    // Fish species
    static const std::string ITEM_ID_TROUT;
    static const std::string ITEM_ID_CARP;
    static const std::string ITEM_ID_PIKE;

    static const std::string ITEM_ID_SALMON;
    static const std::string ITEM_ID_TUNA;
    static const std::string ITEM_ID_COD;

    // Wandcraft
    static const std::string ITEM_ID_TEMPLATE_WAND;

    // Scribing
    static const std::string ITEM_ID_QUILL;
    static const std::string ITEM_ID_INKPOT;
    static const std::string ITEM_ID_BLANK_SCROLL;
    static const std::string ITEM_ID_TEMPLATE_SCROLL;

    // Papercraft
    static const std::string ITEM_ID_PAPER_PULP;
    static const std::string ITEM_ID_MOLD_AND_DECKLE;

    // Weaving
    static const std::string ITEM_ID_CAP;
    static const std::string ITEM_ID_CLOAK;
    static const std::string ITEM_ID_WAYFARER_CLOTHES;

    // Beer Halls
    static const std::string ITEM_ID_DRAM_GIN;
    static const std::string ITEM_ID_DRAM_MEAD;
    static const std::string ITEM_ID_DRAM_WHISKY;
    static const std::string ITEM_ID_GNOMISH_STOUT;
    static const std::string ITEM_ID_FORTIFIED_DWARVEN_WINE;
    static const std::string ITEM_ID_ELVEN_BRANDY;
    static const std::string ITEM_ID_GOBLIN_MOONSHINE;
    static const std::string ITEM_ID_UNSTONING_POTION;
    static const std::string ITEM_ID_HEALING_POTION;
    static const std::string ITEM_ID_ETHER_POTION;

    // Misc
    static const std::string ITEM_ID_BOARD_WITH_NAIL_IN_IT;
    static const std::string ITEM_ID_SCARECROW;

    // Mushrooms and fungus
    static const std::string ITEM_ID_MUSHROOM_1;
    static const std::string ITEM_ID_MUSHROOM_2;
    static const std::string ITEM_ID_MUSHROOM_3;
    static const std::string ITEM_ID_MUSHROOM_4;
    static const std::string ITEM_ID_MUSHROOM_5;
    static const std::string ITEM_ID_MUSHROOM_RARE_1;
    static const std::string ITEM_ID_MUSHROOM_RARE_2;
    static const std::string ITEM_ID_MUSHROOM_RARE_3;
    static const std::string ITEM_ID_FUNGUS_1;
    static const std::string ITEM_ID_FUNGUS_2;

    // make sure any collections are initialized at the bottom
    static const std::vector<std::string> ITEM_IDS_MUSHROOM;
    static const std::vector<std::string> ITEM_IDS_MUSHROOM_RARE;
    static const std::vector<std::string> ITEM_IDS_FUNGUS;

  protected:
    ItemIdKeys();
    ~ItemIdKeys();
};

enum struct FoodType
{
  FOOD_TYPE_VEGETABLE = 0,
  FOOD_TYPE_CARBS = 1,
  FOOD_TYPE_MEAT = 2,
  FOOD_TYPE_DAIRY = 3,
  FOOD_TYPE_OTHER = 4,
  FOOD_TYPE_LAST = 5
};

class ItemValues
{
  public:
    static const int DEFAULT_MIN_GENERATION_VALUE;
    static const int DEFAULT_MIN_SHOP_VALUE;

  protected:
    ItemValues();
    ~ItemValues();
};

enum struct ForagableType
{
  FORAGABLE_TYPE_FORAGABLES = 0,
  FORAGABLE_TYPE_HERBS = 1
};

class ItemEventScripts
{
  public:
    static const std::string ITEM_EVENT_AMMO_DESTRUCT;

  protected:
    ItemEventScripts();
    ~ItemEventScripts();
};
