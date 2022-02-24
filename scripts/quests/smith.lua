require('constants')
require('quest')

local cr_id = args[SPEAKING_CREATURE_ID]

-- Smith quest details
local function smith_start_fn()
  add_message_with_pause("SMITH_QUEST_START_SID")
  clear_and_add_message("SMITH_QUEST_START2_SID")
end

local function smith_completion_condition_fn()
  return (get_item_count(PLAYER_ID, IRON_INGOT_ID) >= 3 and
          get_item_count(PLAYER_ID, COAL_ID) >= 3)
end

local function smith_completion_fn()
  remove_object_from_player(IRON_INGOT_ID, 3)
  remove_object_from_player(COAL_ID, 3)

  add_message("SMITH_QUEST_COMPLETE_SID")
  add_object_to_player_tile(CURRENCY_ID, RNG_range(100, 200))

  -- Create a good weapon based on the player's highest melee skill
  local highest = get_highest_melee_skill(PLAYER_ID)
  
  local smithed_objs = {[1000] = {BATTLE_AXE_ID, GREAT_AXE_ID},
                        [1001] = {SHORT_SWORD_ID},
			[1002] = {BROAD_SWORD_ID, GREAT_SWORD_ID},
			[1003] = {MACE_ID, IRON_HAMMER_ID},
			[1004] = {DAGGER_ID},
			[1005] = {CYPRESS_ROD_ID},
			[1006] = {SPEAR_ID, LONG_SPEAR_ID},
			[1007] = {IRON_CLAW_ID},
			[1008] = {THORN_WHIP_ID},
			[1009] = {CROWBAR_ID}}

  local weapon_ids = smithed_objs[highest]
  local weapon_id = weapon_ids[RNG_range(1, #weapon_ids)]
  
  if weapon_id == nil then
    weapon_id = DAGGER_ID
  end

  add_object_to_player_tile(weapon_id, 1, "", 0, RNG_range(3, 5))
  
  Quest:try_additional_quest_reward()  
  return true
end

local q_id = "smith_" .. cr_id

smith_quest = Quest:new(q_id, 
                        "SMITH_QUEST_TITLE_SID", 
                        "SMITH_SHORT_DESCRIPTION_SID", 
                        "SMITH_QUEST_DESCRIPTION_SID", 
                        "SMITH_QUEST_COMPLETE_SID", 
                        "SMITH_QUEST_REMINDER_SID", 
                        truefn,
                        smith_start_fn, 
                        smith_completion_condition_fn, 
                        smith_completion_fn)

local do_quest = Quest:check_probabilistic_quest(cr_id, q_id, 50)

if do_quest == true then
  do_quest = smith_quest:execute()
end

if do_quest == false then
  clear_and_add_message("SMITH_SPEECH_TEXT_SID")
end
