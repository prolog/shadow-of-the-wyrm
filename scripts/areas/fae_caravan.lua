require('areas')

-- The caravan has no fixed location, appearing instead on one of the
-- outer island tiles.
local caravan_locs = {{6, 53}, {8, 53}, {7, 52}, {7, 54}}
local coords = caravan_locs[RNG_range(1, #caravan_locs)]
local creatures_csv = "caravan_master"

local fae_caravan = Area:new(coords[1], coords[2])
fae_caravan:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_FAE_CARAVAN")
fae_caravan:set_additional_properties({["MAP_PROPERTIES_INITIAL_CREATURES"] = creatures_csv})

fae_caravan:insert()
