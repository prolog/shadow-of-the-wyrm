require('constants')
require('fn')
module('racemaster', package.seeall)

local turtle_race_bet_prop = "turtle_race_bet"
local race_running_prop = "race_running"
local racemaster_id_prop = "racemaster_id"
local turtle_ids_prop = "turtle_ids"

function complete_race(winning_turtle_id, racemaster_id)
  local pl_turtle_id, bet_amount = get_creature_additional_property_csv(PLAYER_ID, turtle_race_bet_prop)
  bet_amount = tonumber(bet_amount)
  local msg_sid = "CARCASSIA_TURTLE_FINISH"
  local outcome_sid = "DEALER_LOSE_SID"
  local turtle_ids = {get_creature_additional_property_csv(winning_turtle_id, turtle_ids_prop)}

  -- Add a notification about the winner
  clear_and_add_message(msg_sid, {get_creature_name(winning_turtle_id)})

  if pl_turtle_id == winning_turtle_id then
    add_object_to_player_tile(CURRENCY_ID, bet_amount * 2)
    outcome_sid = "DEALER_WIN_SID"
  end

  -- Did the player win or lose?
  add_message(outcome_sid)
  
  -- Get everything ready for the next race.
  for i,v in ipairs(turtle_ids) do
    -- Transport the turtles back to the beginning.
    local y,x = get_creature_yx(v)
    local new_x = 25
    teleport(v, y, new_x)

    -- Reset the turtle sentinel flags.
    set_sentinel(y, new_x, true)
  end

  -- Reset the racemaster's flag so races can run again.
  remove_creature_additional_property(racemaster_id, race_running_prop)
end


-- Check to see if the racemaster has already started a race.
local function race_running()
  local racem_id = args[SPEAKING_CREATURE_ID]
  local race_running = get_creature_additional_property(racem_id, race_running_prop)

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
  local turtle_ids = {}
  local turtles = true

  -- Turtles all the way down?
  for k, v in ipairs(coords) do 
    local base_id = get_creature_base_id(v[1], v[2])
    local id = get_creature_id(v[1], v[2])
    local name = get_creature_name(id)

    table.insert(names, id .. "=" .. name)
    table.insert(turtle_ids, id)
    turtles = turtles and base_id == "snapping_turtle"
    
    set_turtle_laziness(v)
  end

  local turtle_ids_csv = fn.array_to_csv(turtle_ids)
  local racem_id = args[SPEAKING_CREATURE_ID]

  -- Each turtle needs to know all the other turtle ids so that when
  -- one wins, the race can be nicely reset.
  for i,v in ipairs(turtle_ids) do
    set_creature_additional_property(v, turtle_ids_prop, turtle_ids_csv)
    set_creature_additional_property(v, racemaster_id_prop, racem_id)
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
          set_creature_additional_property(PLAYER_ID, turtle_race_bet_prop, bet_details)

          -- Set a flag on the racemaster so that you can't bet until the
          -- race is done.
          set_creature_additional_property(racem_id, race_running_prop, tostring(true))
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


