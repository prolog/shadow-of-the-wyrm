require('constants')

local lumps_gold = get_item_count(PLAYER_ID, LUMP_GOLD_ID)
local grunt = true

if lumps_gold >= 4 then
  if add_confirmation_message("GNOMISH_SEATRADER_LUMP_GOLD_SID") then
    remove_object_from_player(LUMP_GOLD_ID, 4)
    add_object_to_player_tile(IVORY_TUSK_ID, 6)
    clear_and_add_message("GNOMISH_SEATRADER_THANKS_SID")

    grunt = false
  end
end

if grunt == true then
  clear_and_add_message("GNOMISH_SEATRADER_SPEECH_TEXT_SID")
end

