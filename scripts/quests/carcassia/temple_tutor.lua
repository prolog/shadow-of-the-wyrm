require('constants')

local literacy = get_skill_value(PLAYER_ID, CSKILL_GENERAL_LITERACY)

if literacy == 0 then
  local currency = get_item_count(PLAYER_ID, CURRENCY_ID)

  if currency >= 2000 then
    if add_confirmation_message("TEMPLE_TUTOR_LITERACY_SID") then
      clear_and_add_message("TEMPLE_TUTOR_LITERACY_ACCEPT_SID")
      remove_object_from_player(CURRENCY_ID, 2000)

      local literacy_val = RNG_range(1, 40)
      set_skill_value(PLAYER_ID, CSKILL_GENERAL_LITERACY, literacy_val)
    else
      clear_and_add_message("TEMPLE_TUTOR_LITERACY_DECLINE_SID")
    end
  else
    clear_and_add_message("TEMPLE_TUTOR_NSF_SID")
  end
else
  clear_and_add_message("TEMPLE_TUTOR_SPEECH_TEXT_SID")
end

