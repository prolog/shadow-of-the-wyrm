require('constants')

local generated_key = get_creature_additional_property(PLAYER_ID, "high_tower_generated_key")

if has_membership(PLAYER_ID, HIGH_TOWER_GUILD_ID) and string.len(generated_key) == 0 then
  clear_and_add_message("OKHOA_KEY_TEXT_SID")
  add_object_to_player_tile("okhoa_key")
  
  set_creature_additional_property(PLAYER_ID, generated_key, tostring(true))
else
  clear_and_add_message("OKHOA_SPEECH_TEXT_SID")
end
