require('constants')
require('cosmos_common')
require('fn')
require('map_events')

local cosmos_map_id = args[MAP_ID]

-- Add random creatures to the map.  The random creatures are taken from
-- the deities' anger summons in the game data.
function add_divine_creatures(map_id, rows, cols, num_creatures)
  local divine_creatures = {"archangel", "titan", "air_elemental",
                            "skyborn", "fire_elemental", "planewalker",
                            "voidling", "star_beast", "astral_horror"}
  local y, x = 0, 0
  local creature_id = divine_creatures[1]

  for i = 1, num_creatures do
    y = RNG_range(0, rows-1)
    x = RNG_range(0, cols-1)
    creature_id = divine_creatures[RNG_range(1, #divine_creatures)]

    if tile_has_creature(y, x, map_id) == false then
      add_creature_to_map(creature_id, y, x, map_id, true)
    end
  end
end

function create_rift(map_id, rift_y, rift_x)
  -- Generate the rift and the exclusionary area around the center
  -- of the map.  Only divine creatures may enter/move within the rift.  
  for ry = rift_y - 1, rift_y + 1 do
    for rx = rift_x - 1, rift_x + 1 do
      add_configurable_feature_to_map("_rift", ry, rx, map_id)
      map_set_tile_property(map_id, ry, rx, "TILE_PROPERTY_ALLOWED_RACES", "_divine")
    end
  end
end

-- Initializing the cosmos is done by picking a deity, and spawning it
-- along with a number of its followers.  These are given action speeds
-- greater than the player's to ensure that the player always gets to act
-- first.
-- 
-- Sceadugenga is excluded from the initial spawn.  He is always the last 
-- to generate.
function init_cosmos(map_id)
  local r, c = map_get_dimensions(map_id)
  local rift_y, rift_x = cosmos_common.get_rift_yx(r, c)

  -- Create the rift, add the race restrictions, and then add one of The
  -- Nine with associated followers.
  create_rift(map_id, rift_y, rift_x)
  cosmos_common.populate_rift(map_id, rift_y, rift_x)
 
  -- Generate lesser divine beings throughout the level.  The number of
  -- creatures should be half the number of columns.
  add_divine_creatures(map_id, r, c, c/2)

  -- Finally, now that the player has entered the cosmos, the Nine are aware
  -- of them and devout creatures will no longer become friendly if they share
  -- the same god.
  set_creature_additional_property(PLAYER_ID, "CREATURE_PROPERTIES_APOSTATE", "1")
end

map_events.set_map_fn(cosmos_map_id, init_cosmos)

