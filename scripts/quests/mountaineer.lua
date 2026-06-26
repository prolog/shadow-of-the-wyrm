require('constants')

local tuition = 1500
local tuition_s = tostring(tuition)
local mountain_lore = get_skill_value(PLAYER_ID, CSKILL_GENERAL_MOUNTAIN_LORE)

if mountain_lore == 0 then
  local ivory = count_currency(PLAYER_ID)

  if ivory >= tuition then
    if add_confirmation_message("MOUNTAINEER_TEACH_TEXT_SID", {tuition_s}) then
      remove_object_from_player(CURRENCY_ID, tuition)
      set_skill_value(PLAYER_ID, CSKILL_GENERAL_MOUNTAIN_LORE, RNG_range(1,8))

      clear_and_add_message("MOUNTAINEER_FAREWELL_SID")
    end
  else
    clear_and_add_message("MOUNTAINEER_NSF_TEXT_SID", {tuition_s})
  end
else
  clear_and_add_message("MOUNTAINEER_SPEECH_TEXT_SID")
end
