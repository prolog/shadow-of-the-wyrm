require('quest')

local function asher_islet_start_fn()
  add_message_with_pause("ASHER_ISLET_QUEST_START_SID")
  add_message_with_pause("ASHER_ISLET_QUEST_START2_SID")
  add_message_with_pause("ASHER_ISLET_QUEST_START3_SID")
  clear_and_add_message("ASHER_ISLET_QUEST_START4_SID")
end

local function asher_islet_completion_condition_fn()
  return (map_creature_ids_have_substring("asher_islet", "goblin") == false)
end


local function asher_islet_completion_fn()
  add_message_with_pause("ASHER_ISLET_QUEST_COMPLETE_SID")
  add_message_with_pause("ASHER_ISLET_QUEST_COMPLETE2_SID")
  clear_and_add_message("ASHER_ISLET_QUEST_COMPLETE3_SID")

  add_piety(PLAYER_ID, CPIETY_CROWNING)
  set_map_music("asher_islet", "assets/sound/music/psalm.ogg")

  return true
end

asher_islet_quest = Quest:new("asher_islet_quest",
                              "ASHER_ISLET_QUEST_TITLE_SID",
                              "ASHER_SHORT_DESCRIPTION_SID",
                              "ASHER_ISLET_QUEST_DESCRIPTION_SID",
                              "ASHER_ISLET_QUEST_COMPLETE_SID",
                              "ASHER_ISLET_QUEST_REMINDER_SID",
                              truefn,
                              asher_islet_start_fn,
                              asher_islet_completion_condition_fn,
                              asher_islet_completion_fn)

if asher_islet_quest:execute() == false then
  clear_and_add_message("ASHER_SPEECH_TEXT_SID")
end

