require('constants')
require('quest')

-- Look up the first kill.
--
-- If this functionality is ever needed elsewhere, move this to fn.lua
-- or the engine.
local function get_first_kill(cr_id)
  return get_creature_additional_property(cr_id, "CREATURE_PROPERTIES_FIRST_KILL_ID")
end

-- Tela's first quest is to kill a score of the first creature the player 
-- killed.
--
-- If the first creature killed is a unique, obviously a score doesn't work.  
-- Tela will consider the quest done at that point.
local function tela_creatures_start_fn()
  local first_kill = get_first_kill(PLAYER_ID)
  set_creature_additional_property(PLAYER_ID, "first_kill_initial_count_tela", tostring(get_num_creature_killed_global(first_kill)))

  add_message_with_pause("TELA_CREATURES_QUEST_START_SID")
  add_message_with_pause("TELA_CREATURES_QUEST_START2_SID")
  clear_and_add_message("TELA_CREATURES_QUEST_START3_SID")
end

local function tela_creatures_prereq_fn()
  local prereq_satisfied = true
  local first_kill = get_first_kill(PLAYER_ID)

  if string.len(first_kill) == 0 then
    add_message_with_pause("TELA_CREATURES_QUEST_PREREQ_SID")
    prereq_satisfied = false
  end

  return prereq_satisfied
end

local function tela_creatures_completion_condition_fn()
  local first_kill = get_first_kill(PLAYER_ID)
  local start_count = get_creature_additional_property(PLAYER_ID, "first_kill_initial_count_tela")
  local cr_count = get_num_creature_killed_global(first_kill)

  if is_unique(first_kill) then
    add_message_with_pause("TELA_CREATURES_QUEST_UNIQUE_SID")
    return true
  else
    -- May not have been set yet - the quest might not have been
    -- triggered.
    if start_count == "" then
      return false
    end

    if tonumber(cr_count) >= tonumber(start_count) + 20 then
      return true
    end
  end

  return false
end

local function tela_creatures_completion_fn()
  clear_and_add_message("TELA_CREATURES_QUEST_COMPLETE_SID")
  add_object_to_player_tile(CURRENCY_ID, 250)

  return true
end

local tela_creatures_quest = Quest:new("tela_creatures",
                                       "TELA_CREATURES_QUEST_TITLE_SID",
                                       "TELA_SHORT_DESCRIPTION_SID",
                                       "TELA_CREATURES_QUEST_DESCRIPTION_SID",
                                       "TELA_CREATURES_QUEST_COMPLETE_SID",
                                       "TELA_CREATURES_QUEST_REMINDER_SID",
                                       tela_creatures_prereq_fn,
                                       tela_creatures_start_fn,
                                       tela_creatures_completion_condition_fn,
                                       tela_creatures_completion_fn)

if tela_creatures_quest:execute() == false then
  clear_and_add_message("TELA_SPEECH_TEXT_SID")
end
