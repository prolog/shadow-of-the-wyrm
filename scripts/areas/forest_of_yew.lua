require('areas')
local creature = require('creature')
local yew_id = "forest_of_yew"

local creatures = {{"skeleton", 9, 13},
                   {"thrall", 9, 13},
                   {"grey_glider", 9, 13},
                   {"ghoul", 9, 13},
                   {"lichling", 9, 13},
                   {"corpse_bird", 9, 13},
                   {"quisling", 9, 13},
                   {"lalo", 1, 1}}

local creatures_csv = creature.to_csv(creatures)

-- Set the details of the Forest of Yew and Lalo's Grotto
local yew = Area:new(62, 81)
yew:set_custom_map_id(yew_id)
yew:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_FOREST_OF_YEW")

local grotto = Area:new(61, 80)
grotto:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_LALOS_GROTTO")
grotto:set_additional_properties({["UNDERWORLD_STRUCTURE_DEPTH"] = "14", ["UNDERWORLD_STRUCTURE_MAX_DEPTH"] = "14", ["MAP_PROPERTIES_INITIAL_CREATURES"] = creatures_csv})

yew:insert()
grotto:insert()

-- Shop details for Forest of Yew
local shop_id = "bree_shop"
local shk_id = get_creature_id(4, 53, yew_id)
set_creature_name(shk_id, "Bree", yew_id)
set_shop_shopkeeper_id(shop_id, shk_id, yew_id)
repop_shop(shop_id, yew_id)

