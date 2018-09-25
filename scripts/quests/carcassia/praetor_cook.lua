require('constants')
require('quest')

local item_ids = {VEGETABLE1_ID, VEGETABLE2_ID, VEGETABLE3_ID, VEGETABLE4_ID, VEGETABLE5_ID, VEGETABLE6_ID}

local function cook_food_start_fn()
  add_message_with_pause("PRAETOR_COOK_FOOD_QUEST_START_SID")
  clear_and_add_message("PRAETOR_COOK_FOOD_QUEST_START2_SID")
end

local function cook_food_completion_condition_fn()
  local has_veggies = true

  for i,v in ipairs(item_ids) do
    if get_item_count(PLAYER_ID, v) < 1 then
      has_veggies = false
      break
    end
  end

  return has_veggies
end

local function cook_food_completion_fn()
  clear_and_add_message("PRAETOR_COOK_FOOD_QUEST_COMPLETE_SID")

  for i,v in ipairs(item_ids) do
    remove_object_from_player(v, 2)
  end

  add_object_to_player_tile("gain_attributes_potion")
  add_object_to_player_tile("carcassia_cook_key")

  return true
end

cook_food_quest = Quest:new("cook_food",
                            "PRAETOR_COOK_FOOD_QUEST_TITLE_SID",
                            "PRAETOR_COOK_SHORT_DESCRIPTION_SID",
                            "PRAETOR_COOK_FOOD_QUEST_DESCRIPTION_SID",
                            "PRAETOR_COOK_FOOD_QUEST_COMPLETE_SID",
                            "PRAETOR_COOK_FOOD_QUEST_REMINDER_SID",
                            truefn,
                            cook_food_start_fn,
                            cook_food_completion_condition_fn,
                            cook_food_completion_fn)

if cook_food_quest:execute() == false then
  clear_and_add_message("PRAETOR_COOK_SPEECH_TEXT_SID")
end