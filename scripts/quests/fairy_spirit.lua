require('constants')

local base_hp = get_creature_base_hp(PLAYER_ID)
local current_hp = get_creature_current_hp(PLAYER_ID)

local base_ap = get_creature_base_ap(PLAYER_ID)
local current_ap = get_creature_current_ap(PLAYER_ID)

if current_hp < base_hp then
  set_creature_current_hp(PLAYER_ID, base_hp)
end

if current_ap < base_ap then
  set_creature_current_ap(PLAYER_ID, base_ap)
end

add_message_with_pause("FAIRY_SPIRIT_HEAL_SID")
clear_and_add_message("FAIRY_SPIRIT_HEAL2_SID")

local spirit_id = args[SPEAKING_CREATURE_ID]
remove_creature_from_map(spirit_id) 
