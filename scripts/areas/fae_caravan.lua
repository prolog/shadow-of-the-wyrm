require('areas')
require('constants')

local creature = require('creature')

-- The caravan has no fixed location, appearing instead on one of the
-- outer island tiles.
local caravan_locs = {{6, 53}, {8, 53}, {7, 52}, {7, 54}}
local coords = caravan_locs[RNG_range(1, #caravan_locs)]
local creatures_csv = ""

local creature_list = {{"caravan_guard", 7, 10},
                       {"fae_traveller", 6, 9},
                       {"fae_musician", 5, 7},
                       {"caravan_master"}}

local creatures_csv = creature.to_csv(creature_list)

local fae_caravan = Area:new(coords[1], coords[2])

-- Field-based random generators by default don't preserve permanence,
-- so turn the flag on in this case.  Also set the map ID ("fae_caravan")
-- so that the Cithriel custom map can link back to the permanent,
-- generated map.
fae_caravan:set_permanence(true)
fae_caravan:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_FAE_CARAVAN")
fae_caravan:set_additional_properties({["MAP_PROPERTIES_INITIAL_CREATURES"] = creatures_csv, ["MAP_PROPERTIES_GENERATED_MAP_ID"] = MAP_ID_FAE_CARAVAN})

fae_caravan:insert()

