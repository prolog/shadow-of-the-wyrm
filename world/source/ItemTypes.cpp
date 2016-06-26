#include "ItemTypes.hpp"

using std::string;

// Item IDs
ItemIdKeys::ItemIdKeys()
{
}

ItemIdKeys::~ItemIdKeys()
{
}

const string ItemIdKeys::ITEM_ID_CURRENCY         = "_currency";
const string ItemIdKeys::ITEM_ID_BRANCH           = "_branch";
const string ItemIdKeys::ITEM_ID_ROCK             = "_rock";
const string ItemIdKeys::ITEM_ID_KINGFLOWER       = "_kingflower";
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
const string ItemIdKeys::ITEM_ID_ROOT             = "_root";
const string ItemIdKeys::ITEM_ID_BERRIES          = "_berries";
const string ItemIdKeys::ITEM_ID_KELP             = "_kelp";
const string ItemIdKeys::ITEM_ID_WHITE_BASIL      = "_white_basil";
const string ItemIdKeys::ITEM_ID_STONEFLOWER      = "_stoneflower";
const string ItemIdKeys::ITEM_ID_VOXFLOWER        = "_voxflower";
const string ItemIdKeys::ITEM_ID_VERBENA          = "_verbena";
const string ItemIdKeys::ITEM_ID_BLACKROOT        = "_blackroot";
const string ItemIdKeys::ITEM_ID_FISHING_ROD      = "_fishing_rod";
const string ItemIdKeys::ITEM_ID_TROUT            = "_trout";
const string ItemIdKeys::ITEM_ID_CARP             = "_carp";
const string ItemIdKeys::ITEM_ID_PIKE             = "_pike";
const string ItemIdKeys::ITEM_ID_SALMON           = "_salmon";
const string ItemIdKeys::ITEM_ID_TUNA             = "_tuna";
const string ItemIdKeys::ITEM_ID_COD              = "_cod";

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

