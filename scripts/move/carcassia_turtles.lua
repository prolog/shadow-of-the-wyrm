require('constants')
require('move')
require('racemaster')

local turtle_ids_prop = "turtle_ids"

local function position_and_hostility_ok(turtle_id)
  -- Check 1 - is the turtle even still alive?
  if creature_exists(turtle_id) == false then
    return false
  end

  -- Check 2 - is the turtle in roughly the right area?
  local min_row = 4
  local max_row = 6
  local min_col = 25
  local max_col = 31
  local pos_ok = false

  local y, x = get_creature_yx(turtle_id)

  if ((y >= min_row and y <= max_row) and (x >= min_col and x <= max_col)) == false then
    return false
  end

  -- Check 3 - is the turtle hostile to the player?
  local hostile = is_creature_hostile(turtle_id, PLAYER_ID)

  if hostile == true then
    return false
  end

  -- If we haven't returned by now, the creature exists, its position is
  -- ok, and it's not hostile.
  return true
end


local function race_completion_fn(creature_id, map_id, row, col)
  -- Column 31 in Carcassia A2 is the endpoint for the race.
  local turtle_ids = {get_creature_additional_property_csv(creature_id, turtle_ids_prop)}

  if col == 31 and turtle_ids ~= nil then
    local all_friendly = true

    for i,v in ipairs(turtle_ids) do
      if position_and_hostility_ok(v) == false then
        all_friendly = false
        break
      end
    end

    if all_friendly then
      racemaster.complete_race(creature_id, get_creature_additional_property(creature_id, "racemaster_id"))
    else
      -- If things are messed up, halt the turtle at the finish line.
      set_sentinel(row, col, true)
    end
  end
end


move.set_enter_tile_fn(args[MOVING_CREATURE_ID], race_completion_fn)
