require('constants')
require('quest')

-- Tela's first quest is to kill a score of the first kill.

-- Look up the first kill.
--
-- If this functionality is ever needed elsewhere, move this to fn.lua
-- or the engine.
local function get_first_kill(cr_id)
  return get_creature_additional_property(cr_id, "CREATURE_PROPERTIES_FIRST_KILL_ID")
end

-- Check to see if the player has killed a score of the first kill.
-- If this is a unique, that won't work, and so Tela will consider the 
-- quest done at that point.
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

-- Quest to bring her some ingots.
local function tela_ingot_prereq_fn()
  return is_quest_completed("tela_creatures")
end

local function tela_ingot_start_fn()
  add_message_with_pause("TELA_INGOT_QUEST_START_SID")
  add_message_with_pause("TELA_INGOT_QUEST_START2_SID")
  add_message_with_pause("TELA_INGOT_QUEST_START3_SID")
  clear_and_add_message("TELA_INGOT_QUEST_START4_SID")

  add_object_to_player_tile("pick_axe")
  add_object_to_player_tile("digging_wand")
end

local function tela_ingot_completion_condition_fn()
  return (get_item_count(PLAYER_ID, IRON_INGOT_ID) >= 3)
end

local function tela_ingot_completion_fn()
  remove_object_from_player(IRON_INGOT_ID, 3)
  clear_and_add_message("TELA_INGOT_QUEST_COMPLETE_SID")
 
  local cur_amnt = RNG_range(200, 300)
  add_object_to_player_tile("coracle")
  add_object_to_player_tile(CURRENCY_ID, cur_amnt)

  return true
end

local tela_ingot_quest = Quest:new("tela_ingot",
                                   "TELA_INGOT_QUEST_TITLE_SID",
                                   "TELA_SHORT_DESCRIPTION_SID",
                                   "TELA_INGOT_QUEST_DESCRIPTION_SID",
                                   "TELA_INGOT_QUEST_COMPLETE_SID",
                                   "TELA_INGOT_QUEST_REMINDER_SID",
                                   tela_ingot_prereq_fn,
                                   tela_ingot_start_fn,
                                   tela_ingot_completion_condition_fn,
                                   tela_ingot_completion_fn)

-- Quest to slay Serat, who has been murdering adventurers in the
-- north-east dungeon.
local function tela_serat_prereq_fn()
  return is_quest_completed("tela_ingot")
end

local function tela_serat_start_fn()
  add_message_with_pause("TELA_SERAT_QUEST_START_SID")
  add_message_with_pause("TELA_SERAT_QUEST_START2_SID")
  clear_and_add_message("TELA_SERAT_QUEST_START3_SID")  
end

local function tela_serat_completion_condition_fn()
  return (get_num_creature_killed_global("serat") > 0)
end

local function tela_serat_completion_fn()
  add_message_with_pause("TELA_SERAT_QUEST_COMPLETE_SID")
  clear_and_add_message("TELA_SERAT_QUEST_COMPLETE2_SID")
  local cur_amnt = RNG_range(700, 1000)

  add_object_to_player_tile("gain_attributes_potion", 3)
  add_object_to_player_tile(CURRENCY_ID, cur_amnt)

  add_membership(PLAYER_ID, "carcassia_adventurer", "CARCASSIA_ADVENTURERS_MEMBERSHIP_SID")

  return true
end

local tela_serat_quest = Quest:new("tela_serat",
                                   "TELA_SERAT_QUEST_TITLE_SID",
                                   "TELA_SHORT_DESCRIPTION_SID",
                                   "TELA_SERAT_QUEST_DESCRIPTION_SID",
                                   "TELA_SERAT_QUEST_COMPLETE_SID",
                                   "TELA_SERAT_QUEST_REMINDER_SID",
                                   tela_serat_prereq_fn,
                                   tela_serat_start_fn,
                                   tela_serat_completion_condition_fn,
                                   tela_serat_completion_fn)

if tela_creatures_quest:execute() == false then
  if tela_ingot_quest:execute() == false then
    if tela_serat_quest:execute() == false then    
      clear_and_add_message("TELA_SPEECH_TEXT_SID")
    end
  end
end
