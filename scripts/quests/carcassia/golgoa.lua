require('constants')

local gol_gift_key = "golgoa_gift_generated"
local pl_val = get_creature_additional_property(PLAYER_ID, gol_gift_key)

if has_membership(PLAYER_ID, HIGH_TOWER_GUILD_ID) and string.len(pl_val) == 0 then
  add_spell_castings(PLAYER_ID, "a_02_dragon_breath", RNG_range(4,6))
  add_spell_castings(PLAYER_ID, "a_09_frost_bolt", RNG_range(10,15))

  add_message_with_pause("GOLGOA_GIFT_TEXT_SID")
  clear_and_add_message("GOLGOA_GIFT_TEXT2_SID")

  set_creature_additional_property(PLAYER_ID, gol_gift_key, "1")
else
  if has_membership(PLAYER_ID, THIEVES_GUILD_ID) then
    clear_and_add_message("GOLGOA_THIEVES_GUILD_MEMBER_SID")
  else
    clear_and_add_message("GOLGOA_SPEECH_TEXT_SID")
  end
end
