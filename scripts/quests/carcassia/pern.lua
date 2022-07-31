require('constants')

local cost_per_sp = 400

if has_membership(PLAYER_ID, ORDER_EX_GLADIATORES_GUILD_ID) then
  if has_trainable_skill(PLAYER_ID) == false then
    clear_and_add_message("PERN_NO_TRAINABLE_SKILLS_SID")
  else
    add_message_direct("TODO")
  end
else
  clear_and_add_message("PERN_SPEECH_TEXT_SID")
end
