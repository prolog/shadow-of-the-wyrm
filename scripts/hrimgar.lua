Quest = require('quest')

-- Create the first quest: Bandits in the Barrow
bandit_quest = Quest.create("hrimgar_bandits", "HRIMGAR_BANDIT_QUEST_TITLE_SID", "HRIMGAR_SHORT_DESCRIPTION_SID", "HRIMGAR_BANDIT_DESCRIPTION_SID")

add_new_quest(bandit_quest.quest_id, bandit_quest)
add_message_with_pause("HRIMGAR_SPEECH_TEXT_SID")
add_message_with_pause("HRIMGAR_BANDIT_QUEST_START_SID")
add_message_with_pause("HRIMGAR_BANDIT_QUEST_START2_SID")
add_message("HRIMGAR_BANDIT_QUEST_START3_SID")

