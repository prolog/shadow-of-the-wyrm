module(..., package.seeall)
require('constants')

-- Function that fires when a creature moves into a new tile.  These are
-- fired automatically and don't count have any effect on a creature's
-- action points, etc.
enter_tile_fns = {}

function set_enter_tile_fn(creature_id, fn)
  enter_tile_fns[creature_id] = fn
end

function enter_tile(creature_id, map_id, tile_y, tile_x)
  local fn = enter_tile_fns[creature_id]

  if fn ~= nil then
    fn(creature_id, map_id, tile_y, tile_x)
  end
end
