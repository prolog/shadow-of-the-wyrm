require('quest')

-- Lalo's grotto quest
local function lalos_grotto_start_fn()
  add_message_with_pause("ILRU_SPEECH_TEXT_SID")
  add_message_with_pause("LALOS_GROTTO_QUEST_START_SID")
  add_message_with_pause("LALOS_GROTTO_QUEST_START2_SID")
  add_message("LALOS_GROTTO_QUEST_START3_SID")
end

local function lalos_grotto_completion_condition_fn()
  return (get_num_creature_killed_global("lalo") > 0)
end

local function lalos_grotto_completion_fn()
  add_message("LALOS_GROTTO_QUEST_COMPLETE_SID")
  add_object_to_player_tile("faerie_shield")
  return true
end

-- Ilru's quest is to slay Lalo, a wood elf corrupted by dark magic
-- who resides in a grotto to the north-west.
grotto_quest = Quest:new("lalos_grotto", 
                         "LALOS_GROTTO_QUEST_TITLE_SID", 
                         "ILRU_SHORT_DESCRIPTION_SID", 
                         "LALOS_GROTTO_DESCRIPTION_SID", 
                         "LALOS_GROTTO_QUEST_COMPLETE_SID", 
                         "LALOS_GROTTO_QUEST_REMINDER_SID", 
                         truefn,
                         lalos_grotto_start_fn, 
                         lalos_grotto_completion_condition_fn, 
                         lalos_grotto_completion_fn)

if grotto_quest:execute() == false then
  add_message("ILRU_SPEECH_TEXT_SID")
end

