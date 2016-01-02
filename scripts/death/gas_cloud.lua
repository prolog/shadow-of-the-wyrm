require('death')

local function explode(creature_id, attacking_creature_id)
  cast_spell(creature_id, "a_01_wreath_of_fire") 
end

local explode_fn = explode
death.set_death_fn("gas_cloud", explode_fn)

