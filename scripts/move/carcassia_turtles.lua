require('move')

local function race_completion_fn(creature_id, map_id, row, col)
  -- JCD FIXME: Check to see if any turtles are in the completion
  -- column, then call the necessary functions in the racemaster's
  -- chat script.
end

move.set_enter_tile_fn(args[MOVING_CREATURE_ID], race_completion_fn)
