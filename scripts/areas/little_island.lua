require('areas')

local isen_dun_id = "isen_dun"

-- Array containing the areas of Little Island.
local little_island = {}

-- Islet of Rowan Head
local rowan_head = Area:new(93, 98)
rowan_head:set_custom_map_id("rowan_head")
rowan_head:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_ROWAN_HEAD")

-- Little Island itself
local wintersea_keep = Area:new(95, 95)
wintersea_keep:set_custom_map_id("wintersea_keep")
wintersea_keep:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_WINTERSEA_KEEP")

local isen_dun = Area:new(96, 96)
isen_dun:set_custom_map_id(isen_dun_id)
isen_dun:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_ISEN_DUN")

local barrows = Area:new(96, 97)
barrows:set_custom_map_id("the_barrows")
barrows:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_ISEN_DUN_GRAVEYARD")

local dungeon = Area:new(97, 98)
local siriath_area = RNG_range(4, 5)
local siriath_custom_map_id_key = siriath_area .. "_CUSTOM_MAP_ID"
dungeon:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_ISEN_DUN_DUNGEON")
dungeon:set_additional_property(siriath_custom_map_id_key, "siriath_lair")
dungeon:set_additional_property("MAP_PROPERTIES_MAX_DEPTH", 25)

table.insert(little_island, rowan_head)
table.insert(little_island, wintersea_keep)
table.insert(little_island, isen_dun)
table.insert(little_island, barrows)
table.insert(little_island, dungeon)

-- Add each of the areas of Little Island to the world map.
for k,v in pairs(little_island) do
  v:insert()
end

-- The game starts out on Little Island, at Isen Dun.
map_add_location("world_map", "STARTING_LOCATION", 96, 96)

-- Shop details for Isen Dun
local shop_id = "edmund_shop"
local shopkeeper_id = get_creature_id(15, 28, isen_dun_id)
set_creature_name(shopkeeper_id, "Edmund", isen_dun_id)
set_shop_shopkeeper_id(shop_id, shopkeeper_id, isen_dun_id)
repop_shop(shop_id, isen_dun_id)

