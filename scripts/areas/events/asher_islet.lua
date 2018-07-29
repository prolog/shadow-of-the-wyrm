require('generate')
require('map_events')

local map_id = "asher_islet"

-- Load up Asher's islet with goblin raiders.
local function setup_raiders(map_id)
  local creatures = {"goblin", "goblin_raider", "goblin_alchemist", "goblin_trapper", "goblin_champion", "goblin_elite_guard", "goblin_impaler", "goblin_raider", "goblin_pelter"}
  local num_creatures = RNG_range(40, 50)
  local hostile = true

  -- Generate Akhra, and then the rest.
  add_creature_to_map("akhra_goblin", 7, 36, map_id)
  generate.add_creatures(map_id, {4,6}, {11,72}, creatures, num_creatures, hostile)
end

function init_asher_islet(map_id)
  setup_raiders(map_id)
end

map_events.set_map_fn(map_id, init_asher_islet)

