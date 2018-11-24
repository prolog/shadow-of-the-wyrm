require('constants')

local key_gen_key = "praetor_footman_key_generated"
local key_gen = get_creature_additional_property(PLAYER_ID, key_gen_key)

if string.len(key_gen) == 0 then
  clear_and_add_message("PRAETOR_FOOTMAN_PROVIDE_KEY_SID")

  add_object_to_player_tile("carcassia_footman_key")
  set_creature_additional_property(PLAYER_ID, key_gen_key, "1")
else
  clear_and_add_message("PRAETOR_FOOTMAN_SPEECH_TEXT_SID")
end
