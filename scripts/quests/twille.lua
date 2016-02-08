require('quest')

-- Twille's quest involves fetching an old manuscript from the monastery
-- at Stonewall.
local function twille_book_start_fn()
  add_message_with_pause("TWILLE_BOOK_QUEST_START_SID")
  add_message_with_pause("TWILLE_BOOK_QUEST_START2_SID")
  clear_and_add_message("TWILLE_BOOK_QUEST_START3_SID")
end

local function twille_book_completion_condition_fn()
  return player_has_item("history_kell_empire") == true
end

local function twille_book_completion_fn()
  add_message_with_pause("TWILLE_BOOK_QUEST_COMPLETE_SID")
  add_message_with_pause("TWILLE_BOOK_QUEST_COMPLETE2_SID")
  clear_and_add_message("TWILLE_BOOK_QUEST_COMPLETE3_SID")
  remove_object_from_player("history_kell_empire")
  add_object_to_player_tile("amagari")
end

twille_quest = Quest:new("twille_book",
                         "TWILLE_BOOK_QUEST_TITLE_SID",
                         "TWILLE_SHORT_DESCRIPTION_SID",
                         "TWILLE_BOOK_QUEST_DESCRIPTION_SID",
                         "TWILLE_BOOK_QUEST_COMPLETE_SID",
                         "TWILLE_BOOK_QUEST_REMINDER_SID",
                         truefn,
                         twille_book_start_fn,
                         twille_book_completion_condition_fn,
                         twille_book_completion_fn)

if twille_quest:execute() == false then
  add_message_with_pause("TWILLE_SPEECH_TEXT_SID")
  add_message_with_pause("TWILLE_SPEECH2_TEXT_SID")
  clear_and_add_message("TWILLE_SPEECH3_TEXT_SID")
end

