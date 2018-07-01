require('constants')

local race_running_property = "race_running"

-- Check to see if the racemaster has already started a race.
local function race_running()
  local racem_id = args[SPEAKING_CREATURE_ID]
  local race_running = get_creature_additional_property(racem_id, race_running_property)

  if race_running == "true" then
    return true
  else
    return false
  end
end

-- All the turtles rest at least a little.  Some might be really lazy...
local function set_turtle_laziness(coords)
  local pct_chance_search = RNG_range(30, 70)

  set_decision_strategy_property(coords[1], coords[2], "search_pct", tostring(pct_chance_search))
end

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
    
    set_turtle_laziness(v)
  end

  if turtles == true then
    local do_race = add_confirmation_message("RACEMASTER_SPEECH_TEXT_SID")

    if do_race then
      -- Pick a turtle!
      local turtle_id = create_menu("CARCASSIA_TURTLE_RACES", names)

      if string.len(turtle_id) > 0 then
        local bet_amount = tonumber(add_prompt_message("RACEMASTER_BET_SID"))
        local player_curr = count_currency(PLAYER_ID)

        if bet_amount ~= nil and bet_amount > 0 and bet_amount <= player_curr then
          local bet_details = turtle_id .. "," .. tostring(bet_amount)
          set_creature_additional_property(PLAYER_ID, "turtle_race_bet", bet_details)

          -- Set a flag on the racemaster so that you can't bet until the
          -- race is done.
          local racem_id = args[SPEAKING_CREATURE_ID]
          set_creature_additional_property(racem_id, race_running_property, tostring(true))
          remove_object_from_player(CURRENCY_ID, bet_amount)

          -- Ready the turtles!
          ready_turtles(coords)
        else
          clear_and_add_message("RACEMASTER_NONSENSE_SID")
        end
      end
    else
      clear_and_add_message("RACEMASTER_DECLINE_SID")
    end
  else
    clear_and_add_message("RACEMASTER_MISSING_TURTLES_SID")
  end
end

if race_running() then
  clear_and_add_message("RACEMASTER_RACE_RUNNING_SID")
else
  run_race()
end


