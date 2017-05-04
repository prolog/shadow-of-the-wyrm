require('areas')

local inf_dungeon = Area:new(89, 98)
inf_dungeon:set_additional_properties({["MAP_PROPERTIES_PERMANENCE"] = "0", ["MAP_PROPERTIES_MAX_DEPTH"] = "10000000"})
inf_dungeon:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_INFINITE_DUNGEON")

inf_dungeon:insert()

