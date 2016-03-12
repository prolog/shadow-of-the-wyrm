require('decide')

-- Red, yellow, white, blue-white (cyan), blue
local colours = {[9]=11, [11]=15, [15]=14, [14]=12, [12]=9}

-- Properties is a table keyed by colour whose values are tables
-- containing, in order, evade, damage dice, speed.
local properties = {[9] = {-20, 30, 70}, 
                    [11] = {0, 40, 60},
                    [15] = {10, 50, 50},
                    [14] = {20, 60, 35},
                    [12] = {40, 70, 25}}

-- Set the dying star's statistics based on its new colour.
local function set_creature_properties(creature_id, next_colour)
  log(CLOG_DEBUG, "Setting creature properties for creature_id " .. creature_id .. " and next_colour " .. next_colour)

  local props = properties[next_colour]

  if props ~= nil then
    local new_evade = props[1]
    local new_damage_dice = props[2]
    local new_speed = props[3]

    log(CLOG_DEBUG, "New evade/damage dice/speed: " .. new_evade .. "/" .. new_damage_dice .. "/" .. new_speed)

    set_creature_colour(creature_id, next_colour)
    set_creature_evade(creature_id, new_evade)
    set_creature_base_damage(creature_id, 1, new_damage_dice)
    set_creature_speed(creature_id, new_speed)
  else
    log(CLOG_ERROR, "Couldn't find properties for next_colour!")
  end
end

-- Get the next colour for the dying star, and then set its properties
-- (evade, etc) based on the new colour.
local function change_colour(creature_id)
  log(CLOG_DEBUG, "Changing colour for creature_id " .. creature_id)

  local ds_colour = get_creature_colour(creature_id)
  local next_colour = colours[ds_colour]

  if next_colour == nil then
    next_colour = 9
  end

  log(CLOG_DEBUG, "Changing colour from " .. ds_colour .. " to " .. next_colour)

  set_creature_properties(creature_id, next_colour)
  local action_cost = 1
  return action_cost
end

-- Dying stars can change intensity, which then changes their speed,
-- damage, and evade.
local function ds_decision_fn(creature_id)
  local change_colour_fn = change_colour
  
  local decision_fns = {change_colour_fn}
  return decision_fns
end

local ds_fn = ds_decision_fn

decide.set_decision_fn("dying_star", ds_fn)

