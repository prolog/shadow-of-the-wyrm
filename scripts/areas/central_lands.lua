require('constants')
require('areas')

-- Details for Kazmar's dungeon.
local dungeon = Area:new(43,52)
dungeon:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_CARCASSIA_DUNGEON")
dungeon:set_additional_property("MAP_PROPERTIES_MAX_DEPTH", 10)

-- Set up the seat of the empire.
local carcassia = Area:new(47, 53)

-- Set up the city tile appropriately.
carcassia:set_custom_map_id("carcassia_a1")
carcassia:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_CARCASSIA")
carcassia:insert()

local carcassia_island = {}

table.insert(carcassia_island, dungeon)
table.insert(carcassia_island, carcassia)

for k,v in pairs(carcassia_island) do
  v:insert()
end
