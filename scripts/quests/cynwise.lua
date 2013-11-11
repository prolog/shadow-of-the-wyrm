require('quest')

-- Wintersea Keep quest details
local function cynwise_wintersea_start_fn()
  add_message_with_pause("CYNWISE_WINTERSEA_QUEST_START_SID")
  add_message_with_pause("CYNWISE_WINTERSEA_QUEST_START2_SID")
  clear_and_add_message("CYNWISE_WINTERSEA_QUEST_START3_SID")
end

local function cynwise_wintersea_completion_condition_fn()
  return player_has_item("silver_branch") == true
end

local function cynwise_wintersea_completion_fn()
  -- Does the player have Herbalism?
  if get_skill_value("player", 22) == 0 then
    set_skill_value("player", 22, RNG_range(15, 20))
    -- Give the player some skill in Herbalism.
    add_message("CYNWISE_WINTERSEA_QUEST_COMPLETE_HERBALISM_SID")
  else
    magic_skill_value = get_skill_value("player", 31)
    -- If the player has Herbalism, and has Magic, and has not maxed out
    -- Magic, Cynwise will teach the player.
    if (magic_skill_value > 0 and magic_skill_value < 100) then
      new_magic_value = magic_skill_value + RNG_range(15, 20)
      set_skill_value("player", 31, new_magic_value)
      add_message("CYNWISE_WINTERSEA_QUEST_COMPLETE_MAGIC_SID")
    else
      -- Has Herbalism, but doesn't have Magic: Cynwise has nothing
      -- to teach, and provides some money.
      add_object_to_player_tile("_currency", 150);
      add_message("CYNWISE_WINTERSEA_QUEST_COMPLETE_CURRENCY_SID")
    end
  end

  remove_object_from_player("silver_branch")
  return true
end

cynwise_quest = Quest:new("cynwise_wintersea",
                         "CYNWISE_WINTERSEA_QUEST_TITLE_SID",
                         "CYNWISE_DESCRIPTION_SID",
                         "CYNWISE_WINTERSEA_DESCRIPTION_SID",
                         "CYNWISE_WINTERSEA_QUEST_COMPLETE_SID",
                         "CYNWISE_WINTERSEA_QUEST_REMINDER_SID",
                         truefn,
                         cynwise_wintersea_start_fn,
                         cynwise_wintersea_completion_condition_fn,
                         cynwise_wintersea_completion_fn)

if cynwise_quest:execute() == false then
  add_message("CYNWISE_SPEECH_TEXT_SID")
end
