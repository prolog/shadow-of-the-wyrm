require('constants')
require('quest')

local gol_gift_key = "golgoa_gift_generated"
local pl_val = get_creature_additional_property(PLAYER_ID, gol_gift_key)

-- Quest: deliver the ring of the high tower to Stoneheim
local function wizard_quest_precondition_fn()
  return has_membership(PLAYER_ID, HIGH_TOWER_GUILD_ID)
end

local function wizard_quest_start_fn()
  add_message_with_pause("GOLGOA_WIZARD_QUEST_START_SID")
  add_message_with_pause("GOLGOA_WIZARD_QUEST_START2_SID")
  clear_and_add_message("GOLGOA_WIZARD_QUEST_START3_SID")

  local map_id = "stoneheim"
  generate_adventurer(map_id, 5, 32, RNG_range(6,15), "", "wizard")
  set_chat_script(map_id, 5, 32, "quests/stoneheim/new_wizard.lua")

  add_object_to_player_tile("wizard_staff", 1, "stoneheim_quest=1")
  add_object_to_player_tile("wizard_robes", 1, "stoneheim_quest=1")
end

local function wizard_quest_completion_condition_fn()
  return (get_creature_additional_property(PLAYER_ID, QUEST_GOLGOA_WIZARD_COMPLETE) == "1")
end

local function wizard_quest_completion_fn()
  clear_and_add_message("GOLGOA_WIZARD_QUEST_COMPLETE_SID")

  add_object_to_player_tile(CURRENCY_ID, RNG_range(300, 600))
  add_object_to_player_tile(GAIN_ATTRIBUTES_POTION_ID)

  return true
end

wizard_quest = Quest:new("golgoa_wizard",
                         "GOLGOA_WIZARD_QUEST_TITLE_SID",
			 "GOLGOA_SHORT_DESCRIPTION_SID",
			 "GOLGOA_WIZARD_QUEST_DESCRIPTION_SID",
			 "GOLGOA_WIZARD_QUEST_COMPLETE_SID",
			 "GOLGOA_WIZARD_QUEST_REMINDER_SID",
			 wizard_quest_precondition_fn,
			 wizard_quest_start_fn,
			 wizard_quest_completion_condition_fn,
			 wizard_quest_completion_fn)

if has_membership(PLAYER_ID, HIGH_TOWER_GUILD_ID) and string.len(pl_val) == 0 then
  add_spell_castings(PLAYER_ID, "a_02_dragon_breath", RNG_range(4,6))
  add_spell_castings(PLAYER_ID, "a_09_frost_bolt", RNG_range(10,15))

  add_message_with_pause("GOLGOA_GIFT_TEXT_SID")
  clear_and_add_message("GOLGOA_GIFT_TEXT2_SID")

  set_creature_additional_property(PLAYER_ID, gol_gift_key, "1")
else
  if has_membership(PLAYER_ID, THIEVES_GUILD_ID) then
    clear_and_add_message("GOLGOA_THIEVES_GUILD_MEMBER_SID")
  else
    if wizard_quest:execute() == false then
      clear_and_add_message("GOLGOA_SPEECH_TEXT_SID")
    end
  end
end
