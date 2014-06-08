require('areas')
local creature = require('creature')

local creatures = {{"satyr", 6, 10},
                   {"black_manticore"}}
local creatures_csv = creature.to_csv(creatures)

-- Set the Gnordvar/mine details.
local gnordvar = Area:new(49, 93)
gnordvar:set_custom_map_id("gnordvar")
gnordvar:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_GNORDVAR")

local gnordvar_mines = Area:new(50, 94)
gnordvar_mines:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_GNORDVAR_MINES")
gnordvar_mines:set_additional_properties({["UNDERWORLD_STRUCTURE_DEPTH"] = "20", ["UNDERWORLD_STRUCTURE_MAX_DEPTH"] = "20", ["MAP_PROPERTIES_INITIAL_CREATURES"] = creatures_csv})

gnordvar:insert()
gnordvar_mines:insert()

