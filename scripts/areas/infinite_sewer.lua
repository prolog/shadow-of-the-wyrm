require('areas')

local sewer = Area:new(82, 79)
sewer:set_additional_properties({["MAP_PROPERTIES_PERMANENCE"] = "0", ["UNDERWORLD_STRUCTURE_MAX_DEPTH"] = "10000000"})
sewer:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_INFINITE_SEWER")

sewer:insert()

