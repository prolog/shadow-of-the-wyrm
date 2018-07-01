require('move')

local function race_completion_fn(creature_id, map_id, row, col)
  log(CLOG_INFO, "Remove this later")
end

move.set_enter_tile_fn(args[MOVING_CREATURE_ID], race_completion_fn)
