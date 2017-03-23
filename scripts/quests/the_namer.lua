require('constants')
require('quest')

local function the_namer_stone_start_fn()
  add_message_with_pause("THE_NAMER_STONE_TEXT_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT2_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT3_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT4_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT5_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT6_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT7_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT8_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT9_SID")
  add_message_with_pause("THE_NAMER_STONE_TEXT10_SID")
  clear_and_add_message("THE_NAMER_STONE_TEXT11_SID")

  add_object_to_player_tile("naming_stone")
end

local function the_namer_stone_completion_condition_fn()
  local celeste_killed = (get_num_creature_killed_global("celeste") > 0)
  local aurelion_killed = (get_num_creature_killed_global("aurelion") > 0)
  local thelady_killed = (get_num_creature_killed_global("thelady") > 0)
  local vedere_killed = (get_num_creature_killed_global("vedere") > 0)
  local voros_killed = (get_num_creature_killed_global("voros") > 0)
  local thetrickster_killed = (get_num_creature_killed_global("thetrickster") > 0)
  local shiver_killed = (get_num_creature_killed_global("shiver") > 0)
  local urgoth_killed = (get_num_creature_killed_global("urgoth") > 0)
  local sceadugenga_killed = (get_num_creature_killed_global("sceadugenga") > 0)

  local done_quest = celeste_killed and aurelion_killed and thelady_killed and vedere_killed and voros_killed and thetrickster_killed and shiver_killed and urgoth_killed and sceadugenga_killed

  log(CLOG_ERROR, "Done quest? " .. tostring(done_quest))

  return done_quest
end

local function the_namer_stone_completion_fn()
  add_message_with_pause("THE_NAMER_STONE_QUEST_COMPLETE_SID")
  add_message_with_pause("THE_NAMER_STONE_QUEST_COMPLETE2_SID")
  add_message_with_pause("THE_NAMER_STONE_QUEST_COMPLETE3_SID")
  clear_and_add_message("THE_NAMER_STONE_QUEST_COMPLETE4_SID")
end

namer_quest = Quest:new("namer_stone",
                        "THE_NAMER_STONE_QUEST_TITLE_SID",
                        "THE_NAMER_SHORT_DESCRIPTION_SID",
                        "THE_NAMER_STONE_QUEST_DESCRIPTION_SID",
                        "THE_NAMER_STONE_QUEST_COMPLETE_SID",
                        "THE_NAMER_STONE_QUEST_REMINDER_SID",
                        truefn,
                        the_namer_stone_start_fn,
                        the_namer_stone_completion_condition_fn,
                        the_namer_stone_completion_fn)

if namer_quest:execute() == false then
  clear_and_add_message("THE_NAMER_SPEECH_TEXT_SID")
end        
                        



