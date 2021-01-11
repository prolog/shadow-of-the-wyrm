require('constants')
require('quest')

local function stolen_goods_start_fn()
  add_message_with_pause("ACEY_STOLEN_GOODS_QUEST_START_SID")
  add_message_with_pause("ACEY_STOLEN_GOODS_QUEST_START2_SID")
  clear_and_add_message("ACEY_STOLEN_GOODS_QUEST_START3_SID")

  add_object_to_player_tile(STOLEN_GOODS_ID)
end

local function stolen_goods_completion_condition_fn()
  return (get_creature_additional_property(PLAYER_ID, QUEST_ACEY_STOLEN_GOODS_COMPLETE) == "1")
end

local function stolen_goods_completion_fn()
  remove_creature_additional_property(PLAYER_ID, QUEST_ACEY_STOLEN_GOODS_COMPLETE)
  add_message_with_pause("ACEY_STOLEN_GOODS_QUEST_COMPLETE_SID")
  clear_and_add_message("ACEY_STOLEN_GOODS_QUEST_COMPLETE2_SID")

  add_object_to_player_tile(CURRENCY_ID, RNG_range(100, 200))
  add_object_to_player_tile(GOLDEN_APPLE_ID, RNG_range(3, 5))
  add_object_to_player_tile(SILVER_APPLE_ID, RNG_range(3, 5))

  return true
end

acey_sg_quest = Quest:new("acey_stolen_goods",
                          "ACEY_STOLEN_GOODS_QUEST_TITLE_SID",
			  "ACEY_SHORT_DESCRIPTION_SID",
			  "ACEY_STOLEN_GOODS_QUEST_DESCRIPTION_SID",
			  "ACEY_STOLEN_GOODS_QUEST_COMPLETE_SID",
			  "ACEY_STOLEN_GOODS_QUEST_REMINDER_SID",
			  truefn,
			  stolen_goods_start_fn,
			  stolen_goods_completion_condition_fn,
			  stolen_goods_completion_fn)

if acey_sg_quest:execute() == false then
  clear_and_add_message("ACEY_SPEECH_TEXT_SID")
end
