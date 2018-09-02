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

-- Axander's second quest is to avenge the death of an emissary brought
-- to bring religion to the Snakelings.
local function axander_sithrin_start_fn()
  add_message_with_pause("AXANDER_SITHRIN_QUEST_START_SID")
  add_message_with_pause("AXANDER_SITHRIN_QUEST_START2_SID")
  add_message_with_pause("AXANDER_SITHRIN_QUEST_START3_SID")
  clear_and_add_message("AXANDER_SITHRIN_QUEST_START4_SID")
end

local function axander_sithrin_completion_condition_fn()
  return player_has_item("talmai_body")
end

local function axander_sithrin_completion_fn()
  remove_object_from_player("talmai_body")

  add_message_with_pause("AXANDER_SITHRIN_QUEST_COMPLETE_SID")
  add_message_with_pause("AXANDER_SITHRIN_QUEST_COMPLETE2_SID")
  add_message_with_pause("AXANDER_SITHRIN_QUEST_COMPLETE3_SID")
  clear_and_add_message("AXANDER_SITHRIN_QUEST_COMPLETE4_SID")

  local cur_regen = get_creature_piety_regen_bonus(PLAYER_ID)
  local new_regen = cur_regen

  if cur_regen <= 1 then
    new_regen = 5
  else
    new_regen = cur_regen * 2
  end

  set_creature_piety_regen_bonus(PLAYER_ID, new_regen)
  add_membership(PLAYER_ID, "fellowship_nine", "CARCASSIA_FELLOWSHIP_NINE_MEMBERSHIP_SID")

  return true
end

local sithrin_quest = Quest:new("axander_sithrin",
                                "AXANDER_SITHRIN_QUEST_TITLE_SID",
                                "AXANDER_SHORT_DESCRIPTION_SID",
                                "AXANDER_SITHRIN_QUEST_DESCRIPTION_SID",
                                "AXANDER_SITHRIN_QUEST_COMPLETE_SID",
                                "AXANDER_SITHRIN_QUEST_REMINDER_SID",
                                truefn,
                                axander_sithrin_start_fn,
                                axander_sithrin_completion_condition_fn,
                                axander_sithrin_completion_fn)

if spellbook_quest:execute() == false then
  if sithrin_quest:execute() == false then
    clear_and_add_message("AXANDER_SPEECH_TEXT_SID")
  end
end

