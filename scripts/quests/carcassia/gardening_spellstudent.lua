require('constants')

local cr_id = args[SPEAKING_CREATURE_ID]
local flower_key = cr_id .. "_flowers_summoned"
local flowers_summoned = get_creature_additional_property(PLAYER_ID, flower_key)

if string.len(flowers_summoned) == 0 then
  summon_items_around_creature(cr_id, "silverweed,_whiteflower", 70)
  set_creature_additional_property(PLAYER_ID, flower_key, "1")

  add_message_with_pause("GARDENING_SPELLSTUDENT_FLOWER_TEXT_SID")
  clear_and_add_message("GARDENING_SPELLSTUDENT_FLOWER_TEXT2_SID")
else
  clear_and_add_message("GARDENING_SPELLSTUDENT_SPEECH_TEXT_SID")
end
