require('constants')
require('quest')

-- Lish gives a quest to bring her silverweed.
local function lish_silverweed_start_fn()
  add_message_with_pause("LISH_SILVERWEED_QUEST_START_SID")
  clear_and_add_message("LISH_SILVERWEED_QUEST_START2_SID")
end

local function lish_silverweed_completion_condition_fn()
  return (get_item_count(PLAYER_ID, "silverweed") >= 4)
end

local function lish_silverweed_completion_fn()
  add_message_with_pause("LISH_SILVERWEED_QUEST_COMPLETE_SID")
  clear_and_add_message("LISH_SILVERWEED_QUEST_COMPLETE2_SID")

  add_spell_castings(PLAYER_ID, "c_01_minor_healing", RNG_range(5, 10))
  add_spell_castings(PLAYER_ID, "c_02_flame_dart", RNG_range(5, 10))
  remove_object_from_player("silverweed", 4)

  return true  
end

lish_quest = Quest:new("lish_silverweed",
                       "LISH_SILVERWEED_QUEST_TITLE_SID",
                       "LISH_SHORT_DESCRIPTION_SID",
                       "LISH_SILVERWEED_QUEST_DESCRIPTION_SID",
                       "LISH_SILVERWEED_QUEST_COMPLETE_SID",
                       "LISH_SILVERWEED_QUEST_REMINDER_SID",
                       truefn,
                       lish_silverweed_start_fn,
                       lish_silverweed_completion_condition_fn,
                       lish_silverweed_completion_fn)

if lish_quest:execute() == false then
  add_message("LISH_SPEECH_TEXT_SID")
end

                       
