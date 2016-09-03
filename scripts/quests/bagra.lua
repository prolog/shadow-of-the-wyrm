require('quest')

-- Bagra will use her black magic to create an unholy dagger from the three
-- relics.  This dagger can be given to Amaurosis to split the universe in
-- two and cause its destruction.
local function bagra_shrine_precond_fn()
  return not (is_quest_completed("blacksmith_shrine"))
end

local function bagra_shrine_start_fn()
  add_message_with_pause("BAGRA_SHRINE_QUEST_START_SID")
  add_message_with_pause("BAGRA_SHRINE_QUEST_START2_SID")
  add_message_with_pause("BAGRA_SHRINE_QUEST_START3_SID")
  clear_and_add_message("BAGRA_SHRINE_QUEST_START4_SID")
end


local function bagra_shrine_completion_condition_fn()
  return (player_has_item("heart_heaven") == true and player_has_item("heart_world") == true and player_has_item("heart_world_beyond") == true)
end

local function bagra_shrine_completion_fn()
  add_message_with_pause("BAGRA_SHRINE_QUEST_COMPLETE_SID")
  add_message_with_pause("BAGRA_SHRINE_QUEST_COMPLETE2_SID")
  add_message_with_pause("BAGRA_SHRINE_QUEST_COMPLETE3_SID")
  clear_and_add_message("BAGRA_SHRINE_QUEST_COMPLETE4_SID")

  add_object_to_player_tile("hearts_needle")
  remove_object_from_player("heart_heaven")
  remove_object_from_player("heart_world")
  remove_object_from_player("heart_world_beyond")
  remove_active_quest("blacksmith_shrine")

  -- Bagra wants to give the knife to Amaurosis herself.
  set_hostility("bagra", "player")

  return true
end

shrine_quest = Quest:new("bagra_shrine",
                         "BAGRA_SHRINE_QUEST_TITLE_SID",
                         "BAGRA_DESCRIPTION_SID",
                         "BAGRA_SHRINE_DESCRIPTION_SID",
                         "BAGRA_SHRINE_QUEST_COMPLETE_SID",
                         "BAGRA_SHRINE_QUEST_REMINDER_SID",
                         bagra_shrine_precond_fn,
                         bagra_shrine_start_fn,
                         bagra_shrine_completion_condition_fn,
                         bagra_shrine_completion_fn)


if shrine_quest:execute() == false then
  add_message("BAGRA_SPEECH_TEXT_SID")
end
