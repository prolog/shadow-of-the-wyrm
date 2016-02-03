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

