require('constants')
require('fn')
require('quest')

local pg_on_quest = "pitmistress_ghara_quest"

local function ghara_quest_start_fn()
  -- Set the creature's ID
  -- set_creature_id("carcassia_c2", some_y, some_x, "ghara_quest_crid")
end

local function ghara_quest_completion_condition_fn()
  return false
end

local function ghara_quest_completion_fn()
  -- ...

  return true
end

if get_creature_additional_property(PLAYER_ID, pg_on_quest) == "1" then  
else
  if add_confirmation_message("PITMISTRESS_GHARA_FIGHT_QUERY_SID") then
    clear_and_add_message("PITMISTRESS_GHARA_FIGHT_ACCEPT_SID")
    -- set_creature_additional_property(PLAYER_ID, pg_on_quest, "1")
  else
    clear_and_add_message("PITMISTRESS_GHARA_FIGHT_DECLINE_SID")
  end
end
