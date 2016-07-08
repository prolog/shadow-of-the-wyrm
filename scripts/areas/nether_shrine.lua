require('areas')

local nether_shrine = Area:new(97, 2)
nether_shrine:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_NETHER_SHRINE")
nether_shrine:set_tile_subtype(13) -- always on a marsh
nather_shrine:set_additional_properties({["MAP_PROPERTIES_RELIC_ID"] = "heart_world_beyond"})

nether_shrine:insert()

