require('areas')
local creature = require('creature')

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
yew:set_custom_map_id("forest_of_yew")
yew:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_FOREST_OF_YEW")

local grotto = Area:new(61, 80)
grotto:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_LALOS_GROTTO")
grotto:set_additional_properties({["UNDERWORLD_STRUCTURE_DEPTH"] = "14", ["UNDERWORLD_STRUCTURE_MAX_DEPTH"] = "14", ["MAP_PROPERTIES_INITIAL_CREATURES"] = creatures_csv})

yew:insert()
grotto:insert()

