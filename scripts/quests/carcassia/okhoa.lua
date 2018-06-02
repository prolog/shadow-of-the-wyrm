require('constants')

local generated_key = get_creature_additional_property(PLAYER_ID, "high_tower_generated_key")

-- Generate the library contents based on the player's preferred school
-- of magic.
local function generate_library_contents()
  -- ...
end

if has_membership(PLAYER_ID, HIGH_TOWER_GUILD_ID) and string.len(generated_key) == 0 then
  generate_library_contents()
  log(CLOG_ERROR, generated_key)

  clear_and_add_message("OKHOA_KEY_TEXT_SID")
  add_object_to_player_tile("okhoa_key")
  set_creature_additional_property(PLAYER_ID, generated_key, tostring(true))
else
  clear_and_add_message("OKHOA_SPEECH_TEXT_SID")
end
