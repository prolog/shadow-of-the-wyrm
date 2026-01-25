require('constants')

local foraging = get_skill_value(PLAYER_ID, CSKILL_GENERAL_FORAGING)

if foraging == 0 then
  set_skill_value(PLAYER_ID, CSKILL_GENERAL_FORAGING, RNG_range(1, 10))
  clear_and_add_message("HERMIT_FORAGING_SID")
else
  clear_and_add_message("HERMIT_SPEECH_TEXT_SID")
end
