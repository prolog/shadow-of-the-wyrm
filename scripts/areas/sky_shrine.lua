require('areas')

local sky_shrine = Area:new(3, 89)
sky_shrine:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_SKY_SHRINE")
sky_shrine:set_tile_subtype(0) -- always on a field
sky_shrine:set_additional_properties({["MAP_PROPERTIES_RELIC_ID"] = "heart_heaven", ["MAP_PROPERTIES_CREATURE_IDS"] = "shrine_hag,archangel,tarasque,unicorn,holy_shade,divine_avenger,wyvern", ["MAP_PROPERTIES_IGNORE_CREATURE_LVL_CHECKS"] = "1"})

sky_shrine:insert()

