require('constants')
require('fn')
require('quest')

local function ghara_quest_start_fn()
end

local function ghara_quest_completion_condition_fn()
  return false
end

local function ghara_quest_completion_fn()
  -- ...

  return true
end

clear_and_add_message("PITMISTRESS_GHARA_SPEECH_TEXT_SID")
