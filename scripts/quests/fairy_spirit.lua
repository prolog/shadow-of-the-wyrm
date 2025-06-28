require('constants')

local new_base_hp = get_creature_base_hp(PLAYER_ID) + 1
local new_base_ap = get_creature_base_ap(PLAYER_ID) + 1

set_creature_base_hp(PLAYER_ID, new_base_hp)
set_creature_base_ap(PLAYER_ID, new_base_ap)
set_creature_current_hp(PLAYER_ID, new_base_hp)
set_creature_current_ap(PLAYER_ID, new_base_ap)
remove_negative_statuses_from_creature(PLAYER_ID)

play_music_event(CMUSIC_EVENT_FAIRY, false)
add_message_with_pause("FAIRY_SPIRIT_HEAL_SID")
clear_and_add_message("FAIRY_SPIRIT_HEAL2_SID")

local spirit_id = args[SPEAKING_CREATURE_ID]
remove_creature_from_map(spirit_id) 

play_map_music(get_current_map_id())
