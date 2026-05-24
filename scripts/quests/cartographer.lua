local cr_id = args[SPEAKING_CREATURE_ID]
local offset_y = 20
local offset_x = 20

local wy, wx = get_player_world_map_coords()
local sw_y, sw_x, sw_text = get_nearby_shipwreck_details(wy - offset_y, wx  - offset_x, wy + offset_y, wx + offset_x)

if coord_is_end(sw_y, sw_x) then
  clear_and_add_message("CARTOGRAPHER_SPEECH_TEXT_SID")
else
  local direction_location = get_direction_location(wy, wx, sw_y, sw_x)
  
  reveal_shipwreck(sw_y, sw_x)
  clear_and_add_message("CARTOGRAPHER_SHIPWRECK_SID", {direction_location, sw_text})
end
