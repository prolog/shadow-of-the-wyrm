require('constants')

local hunting_val = get_skill_value(PLAYER_ID, CSKILL_GENERAL_HUNTING)
local currency = get_item_count(PLAYER_ID, CURRENCY_ID)

if hunting_val == 0 then
  if currency >= 300 then
    if add_confirmation_message("CORBETT_TEACH_HUNTING_SID") then
      remove_object_from_player(CURRENCY_ID, 300)

      local hunting_val = RNG_range(20, 45)
      set_skill_value(PLAYER_ID, CSKILL_GENERAL_HUNTING, hunting_val)

      clear_and_add_message("CORBETT_TEACH_HUNTING_COMPLETE_SID")
    else
      clear_and_add_message("CORBETT_TEACH_HUNTING_DECLINE_SID")
    end
  else
    clear_and_add_message("CORBETT_TEACH_HUNTING_SID")
  end
else
  clear_and_add_message("CORBETT_SPEECH_TEXT_SID")
end
