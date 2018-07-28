require('map_events')

local map_id = "asher_islet"

-- Load up Asher's islet with goblin raiders.
local function setup_raiders(map_id)
  local creatures = {"goblin", "goblin_raider", "goblin_alchemist", "goblin_trapper", "goblin_champion", "goblin_elite_guard", "goblin_impaler", "goblin_raider", "goblin_pelter"}
  local placement_attempts = RNG_range(40, 50)

  for i = 1, placement_attempts do
    local row = RNG_range(4, 16)
    local col = RNG_range(6, 70)
    local creature_id = creatures[i]

    if tile_has_creature(row, col, map_id) == false then
      add_creature_to_map(creature_id, row, col, map_id)
    end
  end
end

function init_asher_islet(map_id)
  setup_raiders(map_id)
end

map_events.set_map_fn(map_id, init_asher_islet)

