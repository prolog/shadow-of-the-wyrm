require('areas')

local creatures = {"skeleton", "thrall", "grey_glider", "ghoul", "lichling", "corpse_bird", "quisling"}

local creatures_to_gen = ""
local num_creatures = RNG_range(9, 13)
local idx = 1

-- Create the csv list of creatures for Lalo's Grotto
for i = 1, num_creatures do
  idx = RNG_range(1, table.getn(creatures))
  creatures_to_gen = creatures_to_gen .. creatures[idx]
  creatures_to_gen = creatures_to_gen .. ","
end

creatures_to_gen = creatures_to_gen .. "lalo"

-- Set the details of the Forest of Yew and Lalo's Grotto
local yew = Area:new(62, 81)
yew:set_custom_map_id("forest_of_yew")
yew:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_FOREST_OF_YEW")

local grotto = Area:new(61, 80)
grotto:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_LALOS_GROTTO")
grotto:set_additional_properties({["UNDERWORLD_STRUCTURE_DEPTH"] = "14", ["UNDERWORLD_STRUCTURE_MAX_DEPTH"] = "14", ["MAP_PROPERTIES_INITIAL_CREATURES"] = creatures_to_gen})

yew:insert()
grotto:insert()

