require('constants')

local fishing_val = get_skill_value(PLAYER_ID, 17)
local currency_amount = get_item_count(PLAYER_ID, CURRENCY_ID)

if fishing_val == 0 then
  if currency_amount >= 100 then
    if add_confirmation_message("FRANCK_TEACH_FISHING_SID") then
      remove_object_from_player(CURRENCY_ID, 100)
      fishing_val = RNG_range(5, 25)
      set_skill_value(PLAYER_ID, 17, fishing_val)
      clear_and_add_message("FRANCK_TEACH_FISHING_COMPLETE_SID")
    else
      clear_and_add_message("FRANCK_TEACH_FISHING_DECLINE_SID")
    end
  else
    add_message("FRANCK_TEACH_FISHING_PREREQ_SID")
  end
else
  add_message_with_pause("FRANCK_SPEECH_TEXT_SID")
end
