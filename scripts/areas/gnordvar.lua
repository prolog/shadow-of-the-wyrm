require('areas')

local creatures_to_gen = ""
local num_creatures = RNG_range(5, 10)
local idx = 1

-- Create the satyrs and manticore
for i = 1, num_creatures do
  creatures_to_gen = creatures_to_gen .. "satyr" 
  creatures_to_gen = creatures_to_gen .. ","
end

creatures_to_gen = creatures_to_gen .. "black_manticore"

-- Set the Gnordvar/mine details.
local gnordvar = Area:new(49, 93)
gnordvar:set_custom_map_id("gnordvar")
gnordvar:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_GNORDVAR")

local gnordvar_mines = Area:new(50, 94)
gnordvar_mines:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_GNORDVAR_MINES")
gnordvar_mines:set_additional_properties({["UNDERWORLD_STRUCTURE_DEPTH"] = "20", ["UNDERWORLD_STRUCTURE_MAX_DEPTH"] = "20", ["MAP_PROPERTIES_INITIAL_CREATURES"] = creatures_to_gen})

gnordvar:insert()
gnordvar_mines:insert()

