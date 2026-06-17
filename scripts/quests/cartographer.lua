require('constants')
require('fn')

local wy, wx = get_player_world_map_coords()
local has_revealed_prop = "has_revealed_shipwreck"
local cr_id = args[SPEAKING_CREATURE_ID]
local offset_y = 30 
local offset_x = 30
local sw_y, sw_x = -1, -1
local sw_text = ""
local min_lore = -1
local revealed_already = get_creature_additional_property(cr_id, has_revealed_prop)
local add_default_msg = true 

local function should_reveal_shipwreck(min_lore)
  -- Before anything else happens, cartographers know if you've killed other
  -- cartographers (presumably, giving them money to reveal the location of a
  -- wreck, and then killing them to get it back). Word gets around, and
  -- others won't work with you.
  if get_num_creatures_killed(PLAYER_ID, CARTOGRAPHER_ID) > 0 then
    clear_and_add_message("CARTOGRAPHER_UNWILLING_SID")

    return false
  end

  local should_reveal = false
  local cost = min_lore * 50
  local player_ivory = get_item_count(PLAYER_ID, CURRENCY_ID)

  if cost > player_ivory then
    clear_and_add_message("CARTOGRAPHER_REVEAL_SID", {tostring(cost)})
  else
    if add_confirmation_message("CARTOGRAPHER_REVEAL_SID", {tostring(cost)}) then
      should_reveal = true
      remove_object_from_player(CURRENCY_ID, cost)
      add_object_to_creature(get_current_map_id(), cr_id, cost)
    end
  end

  return should_reveal
end

if string.len(revealed_already) == 0 then
  -- Offer to reveal a shipwreck nearby, if one exists.
  sw_y, sw_x, sw_text, min_lore = get_nearby_shipwreck_details(wy - offset_y, wx  - offset_x, wy + offset_y, wx + offset_x, false)

  if not coord_is_end(sw_y, sw_x) then
    -- The cartographer's going to talk, so don't show the default message at
    -- the end of the chat logic.
    add_default_msg = false

    if should_reveal_shipwreck(min_lore) then
      reveal_shipwreck(sw_y, sw_x)

      -- Use a pipe as the separator because a comma will already be in use by
      -- the shipwreck text string.
      set_creature_additional_property(cr_id, has_revealed_prop, tostring(sw_y) .. "|" .. tostring(sw_x) .. "|" .. sw_text)
    else
      -- Player either declined or the cartographer did. Shipwreck? What
      -- shipwreck?
      sw_y, sw_x = -1, -1
    end
  end
else
  sw_details = fn.split(revealed_already, "|")
  sw_y, sw_x, sw_text = tonumber(sw_details[1]), tonumber(sw_details[2]), sw_details[3]
end

-- After the various initial checks: see if shipwreck coordinates have been
-- set. If so, give a message hinting at the location.
if not coord_is_end(sw_y, sw_x) then
  local direction_location = get_direction_location(wy, wx, sw_y, sw_x)  
  clear_and_add_message("CARTOGRAPHER_SHIPWRECK_SID", {direction_location, sw_text})
else
  if add_default_msg == true then
    clear_and_add_message("CARTOGRAPHER_SPEECH_TEXT_SID")
  end
end

