require('areas')

-- Array containing the areas of Little Island.
local little_island = {}

local wintersea_keep = Area:new(95, 95)
wintersea_keep:set_custom_map_id("wintersea_keep")
wintersea_keep:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_WINTERSEA_KEEP")

local isen_dun = Area:new(96, 96)
isen_dun:set_custom_map_id("isen_dun")
isen_dun:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_ISEN_DUN")

local barrows = Area:new(96, 97)
barrows:set_custom_map_id("the_barrows")
barrows:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_ISEN_DUN_GRAVEYARD")

local dungeon = Area:new(97, 98)
dungeon:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_ISEN_DUN_DUNGEON")

table.insert(little_island, wintersea_keep)
table.insert(little_island, isen_dun)
table.insert(little_island, barrows)
table.insert(little_island, dungeon)

-- Add each of the areas of Little Island to the world map.
for k,v in pairs(little_island) do
  v:insert()
end

-- The game starts out on Little Island, at Isen Dun.
map_add_location("overworld", "STARTING_LOCATION", 96, 96)

