#include "ItemTypes.hpp"

using std::string;
using std::vector;

// Item IDs
ItemIdKeys::ItemIdKeys()
{
}

ItemIdKeys::~ItemIdKeys()
{
}

const string ItemIdKeys::ITEM_ID_LUMBER           = "_lumber";
const string ItemIdKeys::ITEM_ID_STONE_BLOCK      = "_stone_block";
const string ItemIdKeys::ITEM_ID_SOD_BRICK        = "_sod_brick";
const string ItemIdKeys::ITEM_ID_CLAY_POT         = "_clay_pot";
const string ItemIdKeys::ITEM_ID_CURRENCY         = "_currency";
const string ItemIdKeys::ITEM_ID_BRANCH           = "_branch";
const string ItemIdKeys::ITEM_ID_BOUGH            = "_bough";
const string ItemIdKeys::ITEM_ID_DIRT             = "_dirt";
const string ItemIdKeys::ITEM_ID_CLAY             = "_clay";
const string ItemIdKeys::ITEM_ID_CLAY_SHOT        = "_clay_shot";
const string ItemIdKeys::ITEM_ID_FIRE_BOMB        = "_fire_bomb";
const string ItemIdKeys::ITEM_ID_SHADOW_BOMB      = "_shadow_bomb";
const string ItemIdKeys::ITEM_ID_ROCK             = "_rock";
const string ItemIdKeys::ITEM_ID_STONE            = "_stone";
const string ItemIdKeys::ITEM_ID_HUGE_ROCK        = "huge_rock";
const string ItemIdKeys::ITEM_ID_MAGICI_SHARD     = "_magici_shard";
const string ItemIdKeys::ITEM_ID_PRIMORDIAL_ESSENCE = "_primordial_essence";
const string ItemIdKeys::ITEM_ID_COAL             = "_coal";
const string ItemIdKeys::ITEM_ID_LUMP_GOLD        = "_lump_gold";
const string ItemIdKeys::ITEM_ID_BOG_IRON         = "_bog_iron";
const string ItemIdKeys::ITEM_ID_IRON_INGOT       = "_iron_ingot";
const string ItemIdKeys::ITEM_ID_STEEL_INGOT      = "_steel_ingot";
const string ItemIdKeys::ITEM_ID_FIDDLEHEAD_GREEN = "_fiddlehead_green";
const string ItemIdKeys::ITEM_ID_FERN             = "_fern";
const string ItemIdKeys::ITEM_ID_PILE_OF_BONES    = "_pile_of_bones";
const string ItemIdKeys::ITEM_ID_INTACT_SKELETON  = "_intact_skeleton";
const string ItemIdKeys::ITEM_ID_WHITEFLOWER      = "_whiteflower";
const string ItemIdKeys::ITEM_ID_WILDFLOWER_1     = "_wildflower_1";
const string ItemIdKeys::ITEM_ID_WILDFLOWER_2     = "_wildflower_2";
const string ItemIdKeys::ITEM_ID_WILDFLOWER_3     = "_wildflower_3";
const string ItemIdKeys::ITEM_ID_WILDFLOWER_4     = "_wildflower_4";
const string ItemIdKeys::ITEM_ID_WILDFLOWER_5     = "_wildflower_5";
const string ItemIdKeys::ITEM_ID_WILDFLOWER_6     = "_wildflower_6";
const string ItemIdKeys::ITEM_ID_VEGETABLE_1      = "_vegetable_1";
const string ItemIdKeys::ITEM_ID_VEGETABLE_2      = "_vegetable_2";
const string ItemIdKeys::ITEM_ID_VEGETABLE_3      = "_vegetable_3";
const string ItemIdKeys::ITEM_ID_VEGETABLE_4      = "_vegetable_4";
const string ItemIdKeys::ITEM_ID_VEGETABLE_5      = "_vegetable_5";
const string ItemIdKeys::ITEM_ID_VEGETABLE_6      = "_vegetable_6";
const string ItemIdKeys::ITEM_ID_GOLDEN_APPLE     = "_golden_apple";
const string ItemIdKeys::ITEM_ID_SILVER_APPLE     = "_silver_apple";
const string ItemIdKeys::ITEM_ID_SHOVEL           = "_shovel";
const string ItemIdKeys::ITEM_ID_PICK_AXE         = "pick_axe";
const string ItemIdKeys::ITEM_ID_ROOT             = "_root";
const string ItemIdKeys::ITEM_ID_BERRIES          = "_berries";
const string ItemIdKeys::ITEM_ID_KELP             = "_kelp";
const string ItemIdKeys::ITEM_ID_WHEAT					  = "_wheat";
const string ItemIdKeys::ITEM_ID_WHITE_BASIL      = "_white_basil";
const string ItemIdKeys::ITEM_ID_STONEFLOWER      = "_stoneflower";
const string ItemIdKeys::ITEM_ID_VOXFLOWER        = "_voxflower";
const string ItemIdKeys::ITEM_ID_VERBENA          = "_verbena";
const string ItemIdKeys::ITEM_ID_BLACKROOT        = "_blackroot";
const string ItemIdKeys::ITEM_ID_FISHING_ROD      = "_fishing_rod";
const string ItemIdKeys::ITEM_ID_CORACLE          = "coracle";
const string ItemIdKeys::ITEM_ID_TROUT            = "_trout";
const string ItemIdKeys::ITEM_ID_CARP             = "_carp";
const string ItemIdKeys::ITEM_ID_PIKE             = "_pike";
const string ItemIdKeys::ITEM_ID_SALMON           = "_salmon";
const string ItemIdKeys::ITEM_ID_TUNA             = "_tuna";
const string ItemIdKeys::ITEM_ID_COD              = "_cod";
const string ItemIdKeys::ITEM_ID_TEMPLATE_WAND    = "_template_wand";
const string ItemIdKeys::ITEM_ID_QUILL            = "_quill";
const string ItemIdKeys::ITEM_ID_INKPOT           = "_inkpot";
const string ItemIdKeys::ITEM_ID_BLANK_SCROLL     = "_blank_scroll";
const string ItemIdKeys::ITEM_ID_TEMPLATE_SCROLL  = "_template_scroll";
const string ItemIdKeys::ITEM_ID_PAPER_PULP       = "_paper_pulp";
const string ItemIdKeys::ITEM_ID_MOLD_AND_DECKLE  = "_mold_and_deckle";
const string ItemIdKeys::ITEM_ID_CAP              = "_cap";
const string ItemIdKeys::ITEM_ID_WAYFARER_CLOTHES = "_wayfarer_clothes";
const string ItemIdKeys::ITEM_ID_CLOAK            = "_cloak";
const string ItemIdKeys::ITEM_ID_DRAM_GIN         = "dram_gin";
const string ItemIdKeys::ITEM_ID_DRAM_MEAD        = "dram_mead";
const string ItemIdKeys::ITEM_ID_DRAM_WHISKY      = "dram_whisky";
const string ItemIdKeys::ITEM_ID_GNOMISH_STOUT    = "gnomish_stout";
const string ItemIdKeys::ITEM_ID_FORTIFIED_DWARVEN_WINE = "fortified_dwarven_wine";
const string ItemIdKeys::ITEM_ID_ELVEN_BRANDY     = "elven_brandy";
const string ItemIdKeys::ITEM_ID_GOBLIN_MOONSHINE = "goblin_moonshine";
const string ItemIdKeys::ITEM_ID_UNSTONING_POTION = "_unstoning_potion";
const string ItemIdKeys::ITEM_ID_HEALING_POTION   = "_healing_potion";
const string ItemIdKeys::ITEM_ID_ETHER_POTION     = "_ether_potion";
const string ItemIdKeys::ITEM_ID_BOARD_WITH_NAIL_IN_IT = "_board_with_nail_in_it";
const string ItemIdKeys::ITEM_ID_SCARECROW        = "_scarecrow";
const string ItemIdKeys::ITEM_ID_MUSHROOM_1       = "_mushroom_1";
const string ItemIdKeys::ITEM_ID_MUSHROOM_2       = "_mushroom_2";
const string ItemIdKeys::ITEM_ID_MUSHROOM_3       = "_mushroom_3";
const string ItemIdKeys::ITEM_ID_MUSHROOM_4       = "_mushroom_4";
const string ItemIdKeys::ITEM_ID_MUSHROOM_5       = "_mushroom_5";
const string ItemIdKeys::ITEM_ID_MUSHROOM_RARE_1  = "_mushroom_rare_1";
const string ItemIdKeys::ITEM_ID_MUSHROOM_RARE_2  = "_mushroom_rare_2";
const string ItemIdKeys::ITEM_ID_MUSHROOM_RARE_3  = "_mushroom_rare_3";
const string ItemIdKeys::ITEM_ID_FUNGUS_1         = "_fungus_1";
const string ItemIdKeys::ITEM_ID_FUNGUS_2					= "_fungus_2";

// collections
const vector<string> ItemIdKeys::ITEM_IDS_MUSHROOM = { ItemIdKeys::ITEM_ID_MUSHROOM_1, ItemIdKeys::ITEM_ID_MUSHROOM_2, ItemIdKeys::ITEM_ID_MUSHROOM_3, ItemIdKeys::ITEM_ID_MUSHROOM_4, ItemIdKeys::ITEM_ID_MUSHROOM_5 };
const vector<string> ItemIdKeys::ITEM_IDS_MUSHROOM_RARE = { ItemIdKeys::ITEM_ID_MUSHROOM_RARE_1, ItemIdKeys::ITEM_ID_MUSHROOM_RARE_2, ItemIdKeys::ITEM_ID_MUSHROOM_RARE_3 };
const vector<string> ItemIdKeys::ITEM_IDS_FUNGUS = { ItemIdKeys::ITEM_ID_FUNGUS_1, ItemIdKeys::ITEM_ID_FUNGUS_2 };

// Item Scripts
ItemEventScripts::ItemEventScripts()
{
}

ItemEventScripts::~ItemEventScripts()
{
}

// If you are changing any of these values, go through the Lua scripts to
// ensure those are updated as well!
const string ItemEventScripts::ITEM_EVENT_AMMO_DESTRUCT = "ITEM_EVENT_AMMO_DESTRUCT";

// Item values
ItemValues::ItemValues()
{
}

ItemValues::~ItemValues()
{
}

const int ItemValues::DEFAULT_MIN_GENERATION_VALUE = -1;
const int ItemValues::DEFAULT_MIN_SHOP_VALUE = 5;

