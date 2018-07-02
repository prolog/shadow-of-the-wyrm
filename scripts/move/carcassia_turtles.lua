require('move')
require('racemaster')

local function race_completion_fn(creature_id, map_id, row, col)
  -- Column 31 in Carcassia A2 is the endpoint for the race.
  if col == 31 then
    racemaster.complete_race(creature_id, get_creature_additional_property(creature_id, "racemaster_id"))
  end
end

move.set_enter_tile_fn(args[MOVING_CREATURE_ID], race_completion_fn)
