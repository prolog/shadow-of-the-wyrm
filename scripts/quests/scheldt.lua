require('constants')

local guild_id = "high_tower"
local excluded = "carcassia_guild_thieves"
local desc_sid = "CARCASSIA_HIGH_TOWER_MEMBERSHIP_SID"
local thieves_member = has_membership(PLAYER_ID, excluded)

if thieves_member == true then
  clear_and_add_message("SCHELDT_THIEVES_SPEECH_TEXT_SID")
else
  if count_spells_known(PLAYER_ID) > 0 then
    if has_membership(PLAYER_ID, "high_tower") == true then
      clear_and_add_message("SCHELDT_SPEECH_TEXT_SID")
    else
      if add_confirmation_message("SCHELDT_JOIN_PROMPT_SID") then
        clear_and_add_message("SCHELDT_JOIN_ACCEPT_SID")
        add_membership(PLAYER_ID, guild_id, desc_sid, excluded)
        add_object_to_player_tile("wizard_staff")
        add_object_to_player_tile("wizard_robes")
      else
        clear_and_add_message("SCHELDT_JOIN_DECLINE_SID")
      end
    end
  else
    clear_and_add_message("SCHELDT_INITIATE_SPEECH_TEXT_SID")
  end
end


