-- Get the turtles ready to race by flipping their sentinel flags off.
local function ready_turtles(coords)
  for k,v in ipairs(coords) do
    set_sentinel(v[1], v[2], false)
  end
end

local function run_race()
  local coords = {{4,25},{5,25},{6,25}}
  local names = {}
  local turtles = true

  -- Turtles all the way down?
  for k, v in ipairs(coords) do 
    local base_id = get_creature_base_id(v[1], v[2])
    local id = get_creature_id(v[1], v[2])
    local name = get_creature_name(id)

    table.insert(names, id .. "=" .. name)
    turtles = turtles and base_id == "snapping_turtle"
  end

  if turtles == true then
    local do_race = add_confirmation_message("RACEMASTER_SPEECH_TEXT_SID")

    if do_race then
      -- Pick a turtle!
      local turtle_id = create_menu("CARCASSIA_TURTLE_RACES", names)

      -- Ready the turtles!
      ready_turtles(coords)
    else
      clear_and_add_message("RACEMASTER_DECLINE_SID")
    end
  else
    clear_and_add_message("RACEMASTER_MISSING_TURTLES_SID")
  end
end

run_race()

