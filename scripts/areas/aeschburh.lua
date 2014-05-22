require('areas')
local aeschburh = Area:new(84, 83)

local creature = require('creature')
local creature_list = {{"grave_worm", 8, 12},
                       {"black_servant", 10, 12},
                       {"will_o_the_wisp", 6, 8}}

local creatures_csv = creature.to_csv(creature_list)

aeschburh:set_custom_map_id("aeschburh")
aeschburh:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_AESCHBURH")
aeschburh:set_additional_properties({["MAP_PROPERTIES_INITIAL_CREATURES"] = creatures_csv})

aeschburh:insert()
