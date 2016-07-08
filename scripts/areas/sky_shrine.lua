require('areas')

local sky_shrine = Area:new(3, 89)
sky_shrine:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_SKY_SHRINE")
sky_shrine:set_additional_properties({["MAP_PROPERTIES_RELIC_ID"] = "heart_heaven"})

sky_shrine:insert()

