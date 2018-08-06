require('constants')
require('quest')

-- Axander's first quest is to retrieve a stolen spellbook.
local function axander_spellbook_start_fn()
  add_message_with_pause("AXANDER_SPELLBOOK_QUEST_START_SID")
  add_message_with_pause("AXANDER_SPELLBOOK_QUEST_START2_SID")
  clear_and_add_message("AXANDER_SPELLBOOK_QUEST_START3_SID")
end

local function axander_spellbook_completion_condition_fn()
  return player_has_item("smite_spellbook")
end

local function axander_spellbook_completion_fn()
  remove_object_from_player("smite_spellbook")
  add_object_to_player_tile(CURRENCY_ID, 100)
  clear_and_add_message("AXANDER_SPELLBOOK_QUEST_COMPLETE_SID")

  return true
end

local spellbook_quest = Quest:new("axander_spellbook",
                                  "AXANDER_SPELLBOOK_QUEST_TITLE_SID",
                                  "AXANDER_SHORT_DESCRIPTION_SID",
                                  "AXANDER_SPELLBOOK_QUEST_DESCRIPTION_SID",
                                  "AXANDER_SPELLBOOK_QUEST_COMPLETE_SID",
                                  "AXANDER_SPELLBOOK_QUEST_REMINDER_SID",
                                  truefn,
                                  axander_spellbook_start_fn,
                                  axander_spellbook_completion_condition_fn,
                                  axander_spellbook_completion_fn)

if spellbook_quest:execute() == false then
  clear_and_add_message("AXANDER_SPEECH_TEXT_SID")
end

