require('death')

local function explode(creature_id, attacking_creature_id)
  -- Cast wreath of fire
  -- ...
end

local explode_fn = explode
death.set_death_fn("gas_cloud", explode_fn)

