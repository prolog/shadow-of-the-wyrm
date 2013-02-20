Quest = require('quest')

-- Create the first quest: Bandits in the Barrow
bandit_quest = Quest.create("hrimgar_bandits", "HRIMGAR_BANDIT_QUEST_TITLE_SID", "HRIMGAR_SHORT_DESCRIPTION_SID", "HRIMGAR_BANDIT_DESCRIPTION_SID")

if is_quest_completed(bandit_quest.quest_id) then
  add_message("HRIMGAR_SPEECH_TEXT_SID")
elseif is_on_quest(bandit_quest.quest_id) then
  if get_num_creature_killed_global("garros") == 1 then
    add_message("HRIMGAR_BANDIT_QUEST_COMPLETE_SID")
    add_object_to_player_tile("boathouse_key")
    mark_quest_completed(bandit_quest.quest_id)
  else
    add_message("HRIMGAR_BANDIT_QUEST_REMINDER_SID")
  end
else
  add_new_quest(bandit_quest.quest_id, bandit_quest)
  add_message_with_pause("HRIMGAR_SPEECH_TEXT_SID")
  add_message_with_pause("HRIMGAR_BANDIT_QUEST_START_SID")
  add_message_with_pause("HRIMGAR_BANDIT_QUEST_START2_SID")
  add_message("HRIMGAR_BANDIT_QUEST_START3_SID")
end
