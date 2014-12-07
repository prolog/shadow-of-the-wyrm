require('quest')

-- Hild requires a large supply of whiteflower to be able to fulfill
-- her various orders.
local function hild_weaving_start_fn()
  add_message_with_pause("HILD_WEAVING_QUEST_START_SID")
  add_message_with_pause("HILD_WEAVING_QUEST_START2_SID")
  clear_and_add_message("HILD_WEAVING_QUEST_START3_SID")
end

-- 20 whiteflowers are required
local function hild_weaving_completion_condition_fn()
  return (get_item_count("player", "_whiteflower") >= 20)
end

-- Hild will teach weaving, if the player does not know it.
-- If the player knows how to weave, she presents the Mantle of Wintersea
-- instead.
local function hild_weaving_completion_fn()
  local weaving = 49
  local skill_value = get_skill_value("player", weaving)

  if (skill_value < 80) then
    -- If the player hasn't come close to mastering weaving, Hild
    -- will teach him or her a little more.
    set_skill_value("player", weaving, skill_value + 25)
    clear_and_add_message("HILD_WEAVING_QUEST_COMPLETE_SID")
  else
    -- Set the skill to the maximum value, and then grant the mantle.
    set_skill_value("player", weaving, 100)
    add_object_to_player_tile("wintersea_mantle")
    
    add_message_with_pause("HILD_WEAVING_QUEST_COMPLETE_SPECIAL_SID")
    add_message_with_pause("HILD_WEAVING_QUEST_COMPLETE_SPECIAL2_SID")
    clear_and_add_message("HILD_WEAVING_QUEST_COMPLETE_SPECIAL3_SID") 
  end

  -- JCD FIXME: Remove the 20 whiteflowers.
  return true
end

hild_quest = Quest:new("hild_weaving",
                       "HILD_WEAVING_QUEST_TITLE_SID",
                       "HILD_SHORT_DESCRIPTION_SID",
                       "HILD_WEAVING_QUEST_DESCRIPTION_SID",
                       "HILD_WEAVING_QUEST_COMPLETE_SID",
                       "HILD_WEAVING_QUEST_REMINDER_SID",
                       truefn,
                       hild_weaving_start_fn,
                       hild_weaving_completion_condition_fn,
                       hild_weaving_completion_fn)

if hild_quest:execute() == false then
  add_message("HILD_SPEECH_TEXT_SID")
end

