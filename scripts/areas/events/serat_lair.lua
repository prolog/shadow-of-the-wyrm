require('map_events')

local map_id = "serat_lair"

-- Serat's lair contains Serat himself, as well as a number of powerful
-- henchlings.
local function init_serat_lair(map_id)
  local creatures = {"serat"}
  local addl_creatures = {"goblin_alchemist", "snakeling_thief", "ogre", "goblin_champion"}

  for i = 6,9 do
    local idx = RNG_range(1, table.getn(addl_creatures))
    local henchling = addl_creatures[idx]

    table.insert(creatures, henchling)
  end

  for i = 1, #creatures do
    local ry = RNG_range(4, 13)
    local rx = RNG_range(31, 49)

    add_creature_to_map(creatures[i], ry, rx, map_id)
  end
end

map_events.set_map_fn(map_id, init_serat_lair)

