require('constants')
require('areas')

-- The Carcassian mines
local carcassia_mines = Area:new(44, 46)
carcassia_mines:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_CARCASSIA_MINES")
carcassia_mines:set_additional_property("MAP_PROPERTIES_MAX_DEPTH", "1")
carcassia_mines:set_additional_property("MAP_PROPERTIES_CREATURE_DANGER_LEVEL_FIXED", "1")
carcassia_mines:set_additional_property("MAP_PROPERTIES_DANGER_LEVEL_OVERRIDE", "-1")

-- Detail's for Asher's islet
local asher_islet = Area:new(40,48)
asher_islet:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_ASHER_ISLET")
asher_islet:set_custom_map_id("asher_islet")

-- Details for Serat's dungeon.
local dungeon = Area:new(43,52)
local serat_level = RNG_range(6,10)
dungeon:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_CARCASSIA_DUNGEON")
dungeon:set_additional_property(serat_level .. "_CUSTOM_MAP_ID", "serat_lair")
dungeon:set_additional_property("MAP_PROPERTIES_MAX_DEPTH", tostring(serat_level))

-- Set up the seat of the empire.
local carcassia = Area:new(47, 53)

-- Set up the city tile appropriately.
carcassia:set_custom_map_id("carcassia_a1")
carcassia:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_CARCASSIA")
carcassia:insert()

local carcassia_island = {}

table.insert(carcassia_island, carcassia_mines)
table.insert(carcassia_island, asher_islet)
table.insert(carcassia_island, dungeon)
table.insert(carcassia_island, carcassia)

for k,v in pairs(carcassia_island) do
  v:insert()
end

generate_hireling("carcassia_a1", 10, 78, RNG_range(8, 10))
