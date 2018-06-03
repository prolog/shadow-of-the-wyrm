require('constants')

local lore_gift_key = "lorelei_gift_generated"
local pl_val = get_creature_additional_property(PLAYER_ID, lore_gift_key)

if has_membership(PLAYER_ID, HIGH_TOWER_GUILD_ID) and string.len(pl_val) == 0 then
  add_object_to_player_tile("gain_attributes_potion")
  add_object_to_player_tile("fireball_wand")

  add_message_with_pause("LORELEI_GIFT_TEXT_SID")
  clear_and_add_message("LORELEI_GIFT_TEXT2_SID")

  set_creature_additional_property(PLAYER_ID, lore_gift_key, "1")
else
  clear_and_add_message("LORELEI_SPEECH_TEXT_SID")
end
