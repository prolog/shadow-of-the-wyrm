require('quest')

-- Common quests for various NPCs.
local function add_common_quest_reward()
  local reward_ids = {}
  
  if RNG_percent_chance(75) then
    reward_ids = {{LIGHTNING_WAND_ID, 1}, {MAGICI_SHARD_ID, RNG_range(2, 4)}, {STONEFLOWER_ID, RNG_range(2, 4)}, {CURRENCY_ID, RNG_range(20, 30)}, {UNCURSING_SCROLL_ID, RNG_range(2,3)}, {SPEED_POTION_ID, RNG_range(2, 4)}, {ETHER_POTION_ID, RNG_range(2, 4)}, {HEALING_POTION_ID, RNG_range(2,4)}}
  else
    reward_ids = {{GOLDEN_APPLE_ID, 1}, {SILVER_APPLE_ID, 1}, {ENCHANTING_SCROLL_ID, 1}, {GAIN_ATTRIBUTES_POTION_ID, 1}}
  end

  local reward = reward_ids[RNG_range(1, #reward_ids)]
  add_object_to_player_tile(reward[1], reward[2])
end

-- Long day/thirsty quest
local function thirsty_start_fn()
  clear_and_add_message("THIRSTY_QUEST_START_SID")
end

local function thirsty_completion_condition_fn()
  return player_has_item(GNOMISH_STOUT_ID)
end

local function thirsty_completion_fn()
  remove_object_from_player(GNOMISH_STOUT_ID)
  
  add_message("THIRSTY_QUEST_COMPLETE_SID")
  add_common_quest_reward()
  Quest:try_additional_quest_reward()
  
  return true
end

-- CommonQuest module.  Used to quests that can be used by a variety of
-- NPCs.
CommonQuests = {}
CommonQuests.__index = CommonQuests

local function get_quests(cr_id, sdesc_sid)
  local thirsty_quest = Quest:new("thirsty_" .. cr_id, 
                                  "THIRSTY_QUEST_TITLE_SID", 
                                  sdesc_sid,
                                  "THIRSTY_QUEST_DESCRIPTION_SID", 
                                  "THIRSTY_QUEST_COMPLETE_SID", 
                                  "THIRSTY_QUEST_REMINDER_SID", 
                                  truefn,
                                  thirsty_start_fn, 
                                  thirsty_completion_condition_fn, 
                                  thirsty_completion_fn)

  local quests = {{thirsty_quest, 10}}
  return quests
end

function CommonQuests:do_quests(creature_id)
  local sdesc_sid = get_creature_short_description_sid(creature_id)
  local quests = get_quests(creature_id, sdesc_sid)
  
  for i,v in ipairs(quests) do
    local do_quest = Quest:check_probabilistic_quest(creature_id, v[1].quest_id, v[2])
    
    if do_quest and v[1]:execute() then
      return true
    end
  end

  return false
end

