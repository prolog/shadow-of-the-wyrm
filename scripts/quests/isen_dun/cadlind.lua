require('quest')

local function cadlind_locket_quest_start_fn()
  -- Intentionally does nothing.  Cadlind's quest isn't really a
  -- traditional quest with an intro speech - she just reacts
  -- to being given back the locket she gave to Cornel.
end

local function cadlind_locket_quest_precond_fn()
  return player_has_item("wave_locket") == true
end

local function cadlind_locket_quest_completion_condition_fn()
  return cadlind_locket_quest_precond_fn()
end

local function cadlind_locket_quest_completion_fn()
  add_message_with_pause("CADLIND_LOCKET_QUEST_COMPLETE_SID")
  add_message_with_pause("CADLIND_LOCKET_QUEST_COMPLETE2_SID")
  add_message_with_pause("CADLIND_LOCKET_QUEST_COMPLETE3_SID")
  add_message_with_pause("CADLIND_LOCKET_QUEST_COMPLETE4_SID")
  clear_and_add_message("CADLIND_LOCKET_QUEST_COMPLETE5_SID")

  remove_object_from_player("wave_locket")
  add_object_to_player_tile("scrimshaw_hairpin")
  remove_creature_from_map("cadlind")

  return true
end

local chat_topics = {"CADLIND_SPEECH_TEXT_SID",
                     "CADLIND_SPEECH_TEXT2_SID",
                     "CADLIND_SPEECH_TEXT3_SID"}

-- Most strings are empty because the quest is either unattainable,
-- or already complete, based on whether the player has the wave
-- locket from Cornel.  However, it does show up in the completed
-- quests in the character dump.
cadlind_locket_quest = Quest:new("cadlind_locket_quest",
                                 "CADLIND_LOCKET_QUEST_TITLE_SID",
                                 "CADLIND_DESCRIPTION_SID",
                                 "CADLIND_LOCKET_QUEST_DESCRIPTION_SID",
                                 "",
                                 "",
                                 cadlind_locket_quest_precond_fn,
                                 cadlind_locket_quest_start_fn,
                                 cadlind_locket_quest_completion_condition_fn,
                                 cadlind_locket_quest_completion_fn)

if cadlind_locket_quest:execute() == false then
    clear_and_add_message(chat_topics[RNG_range(1, table.getn(chat_topics))])
end

