require('death')
require('cosmos_common')

local function generate_next_deity(creature_id, attacking_creature_id, map_id)
  local r, c = map_get_dimensions(map_id)
  local rift_y, rift_x = cosmos_common.get_rift_yx(r, c)

  cosmos_common.populate_rift(map_id, rift_y, rift_x)
end

local next_fn = generate_next_deity

death.set_death_fn("celeste", next_fn)
death.set_death_fn("aurelion", next_fn)
death.set_death_fn("the_lady", next_fn)
death.set_death_fn("vedere", next_fn)
death.set_death_fn("voros", next_fn)
death.set_death_fn("the_trickster", next_fn)
death.set_death_fn("shiver", next_fn)
death.set_death_fn("urgoth", next_fn)

