require('quest')

-- Cynwise is one of three inhabitants of Isen Dun who really, really wants
-- the Sun Gem.  Her quest can only be done if neither the Blacksmith or
-- the Ploughman's quest for the gem have been completed.
local function cynwise_sun_gem_precond_fn()
  return not ((is_quest_completed("ploughman_sungem")) or
              (is_quest_completed("blacksmith_sungem")))
end

local function cynwise_sun_gem_start_fn()
  add_message_with_pause("CYNWISE_SUNGEM_QUEST_START_SID")
  add_message_with_pause("CYNWISE_SUNGEM_QUEST_START2_SID")
  clear_and_add_message("CYNWISE_SUNGEM_QUEST_START3_SID")
end

local function cynwise_sun_gem_completion_condition_fn()
  return (player_has_item("sun_gem") == true)
end

local function cynwise_sun_gem_completion_fn()
  add_message_with_pause("CYNWISE_SUNGEM_QUEST_COMPLETE_SID")

  local literacy_value = get_skill_value("player", 28)

  if (literacy_value > 0) then
    clear_and_add_message("CYNWISE_SUNGEM_QUEST_COMPLETE2_SID")
    add_object_to_player_tile("identify_scroll", 4)
  else
    add_object_to_player_tile("identify_scroll", 2)
    literacy_value = RNG_range(3, 15)
    set_skill_value("player", 28, literacy_value)
    clear_and_add_message("CYNWISE_SUNGEM_QUEST_COMPLETE_LITERACY_SID")
  end

  remove_object_from_player("sun_gem")
  remove_active_quest("blacksmith_sungem")
  remove_active_quest("ploughman_sungem")

  return true
end

cynwise_sungem_quest = Quest:new("cynwise_sungem",
                                 "CYNWISE_SUNGEM_QUEST_TITLE_SID",
                                 "CYNWISE_SHORT_DESCRIPTION_SID",
                                 "CYNWISE_SUNGEM_DESCRIPTION_SID",
                                 "CYNWISE_SUNGEM_QUEST_COMPLETE_SID",
                                 "CYNWISE_SUNGEM_QUEST_REMINDER_SID",
                                 cynwise_sun_gem_precond_fn,
                                 cynwise_sun_gem_start_fn,
                                 cynwise_sun_gem_completion_condition_fn,
                                 cynwise_sun_gem_completion_fn)

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

wintersea_quest = Quest:new("cynwise_wintersea",
                         "CYNWISE_WINTERSEA_QUEST_TITLE_SID",
                         "CYNWISE_DESCRIPTION_SID",
                         "CYNWISE_WINTERSEA_DESCRIPTION_SID",
                         "CYNWISE_WINTERSEA_QUEST_COMPLETE_SID",
                         "CYNWISE_WINTERSEA_QUEST_REMINDER_SID",
                         truefn,
                         cynwise_wintersea_start_fn,
                         cynwise_wintersea_completion_condition_fn,
                         cynwise_wintersea_completion_fn)

-- Aeschburh quest: find the source of the blight in Aeschburh, and
-- extinguish it.
local function cynwise_burh_start_fn()
  add_message_with_pause("CYNWISE_AESCHBURH_QUEST_START_SID")
  add_message_with_pause("CYNWISE_AESCHBURH_QUEST_START2_SID")
  add_message_with_pause("CYNWISE_AESCHBURH_QUEST_START3_SID")
  clear_and_add_message("CYNWISE_AESCHBURH_QUEST_START4_SID")
end

local function cynwise_burh_completion_fn()
  -- Reward is the Shroud of Cynehild
  add_message_with_pause("CYNWISE_AESCHBURH_QUEST_COMPLETE_SID")
  clear_and_add_message("CYNWISE_AESCHBURH_QUEST_COMPLETE2_SID")
  add_object_to_player_tile("cynehild_shroud")
  return true
end

local function cynwise_burh_completion_condition_fn()
  return (get_num_creature_killed_global("pirrha") > 0) 
end

cynwise_aeschburh_quest = Quest:new("cynwise_aeschburh_quest",
                                    "CYNWISE_AESCHBURH_QUEST_TITLE_SID",
                                    "CYNWISE_SHORT_DESCRIPTION_SID",
                                    "CYNWISE_AESCHBURH_DESCRIPTION_SID",
                                    "CYNWISE_AESCHBURH_QUEST_COMPLETE_SID",
                                    "CYNWISE_AESCHBURH_QUEST_REMINDER_SID",
                                    truefn,
                                    cynwise_burh_start_fn,
                                    cynwise_burh_completion_condition_fn,
                                    cynwise_burh_completion_fn)


-- Handle quest ordering for Cynwise.
-- The Sun Gem quest comes first, then Wintersea, followed by Aeschburh.
if cynwise_sungem_quest:execute() == false then
  if wintersea_quest:execute() == false then
    if cynwise_aeschburh_quest:execute() == false then
      local replace = {get_player_title()}
      add_message("CYNWISE_SPEECH_TEXT_SID", replace)
    end
  end
end
