require('areas')
local creature = require('creature')
local gnordvar_id = "gnordvar"

local creatures = {{"satyr", 6, 10},
                   {"black_manticore"}}
local creatures_csv = creature.to_csv(creatures)

-- Set the Gnordvar/mine details.
local gnordvar = Area:new(49, 93)
gnordvar:set_custom_map_id(gnordvar_id)
gnordvar:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_GNORDVAR")

local gnordvar_mines = Area:new(50, 94)
gnordvar_mines:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_GNORDVAR_MINES")
gnordvar_mines:set_additional_properties({["UNDERWORLD_STRUCTURE_DEPTH"] = "20", ["UNDERWORLD_STRUCTURE_MAX_DEPTH"] = "20", ["MAP_PROPERTIES_INITIAL_CREATURES"] = creatures_csv})

gnordvar:insert()
gnordvar_mines:insert()

-- Gantt runs a potion shop in the north-east corner of Gnordvar.
local shop_id = "gantt_shop"
local shopkeeper_id = get_creature_id(5, 71, gnordvar_id)
set_creature_name(shopkeeper_id, "Gantt", gnordvar_id)
set_shop_shopkeeper_id(shop_id, shopkeeper_id, gnordvar_id)
repop_shop(shop_id, gnordvar_id)

