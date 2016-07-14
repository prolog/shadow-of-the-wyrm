require('areas')

local nether_shrine = Area:new(97, 2)
nether_shrine:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_NETHER_SHRINE")
nether_shrine:set_tile_subtype(13) -- always on a marsh
nether_shrine:set_additional_properties({["MAP_PROPERTIES_RELIC_ID"] = "heart_world_beyond",["MAP_PROPERTIES_CREATURE_IDS"] = "black_unicorn,shadow_wyrm,spectral_emperor,shrine_hag,pit_fiend,abyssal_beast", ["MAP_PROPERTIES_IGNORE_CREATURE_LVL_CHECKS"] = "1"})

nether_shrine:insert()

