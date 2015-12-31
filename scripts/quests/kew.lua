require('quest')

-- After Kew provides his key, he will give a quest to the south-east
-- dungeons.
local function kew_dungeon_start_fn()
  add_message_with_pause("KEW_DUNGEON_QUEST_START_SID")
  add_message_with_pause("KEW_DUNGEON_QUEST_START2_SID")
  add_message_with_pause("KEW_DUNGEON_QUEST_START3_SID")
  clear_and_add_message("KEW_DUNGEON_QUEST_START4_SID")
end

-- Quest requires Siriath to be destroyed.
local function kew_dungeon_completion_condition_fn()
  return (get_num_creature_killed_global("siriath") > 0)
end

-- Kew, in his gratitute, grants the player the best part of his former
-- adventuring arsenal: chain mail, a good sword, and a few healing
-- potions.
local function kew_dungeon_completion_fn()
  add_message("KEW_DUNGEON_QUEST_COMPLETE_SID")
  add_object_to_player_tile("chain_mail")
  add_object_to_player_tile("lightning_sword")
  add_object_to_player_tile("healing_potion", 2)

  return true
end

-- Create Kew's quest to slay Siriath.
kew_quest = Quest:new("kew_dungeon",
                      "KEW_DUNGEON_QUEST_TITLE_SID",
                      "KEW_SHORT_DESCRIPTION_SID",
                      "KEW_DUNGEON_QUEST_DESCRIPTION_SID",
                      "KEW_DUNGEON_QUEST_COMPLETE_SID",
                      "KEW_DUNGEON_QUEST_REMINDER_SID",
                      truefn,
                      kew_dungeon_start_fn,
                      kew_dungeon_completion_condition_fn,
                      kew_dungeon_completion_fn)

-- Random chat topics.
local chat_topics = {"KEW_SPEECH_TEXT_SID",
                     "KEW_SPEECH_TEXT2_SID",
                     "KEW_SPEECH_TEXT3_SID",
                     "KEW_SPEECH_TEXT4_SID",
                     "KEW_SPEECH_TEXT5_SID",
                     "KEW_SPEECH_TEXT6_SID",
                     "KEW_SPEECH_TEXT7_SID",
                     "KEW_SPEECH_TEXT8_SID",
                     "KEW_SPEECH_TEXT9_SID",
                     "KEW_SPEECH_TEXT10_SID"}

if is_item_generated("kew_key") == true then
  if kew_quest:execute() == false then
    add_message(chat_topics[RNG_range(1, table.getn(chat_topics))])
  end
else
  add_message("KEW_SUPPLIES_SPEECH_SID")
  add_object_to_player_tile("kew_key")
end

