require('constants')

if get_num_deities() == 0 then
  add_message_with_pause("THE_ARMOURER_GODSLAYER_SPEECH_TEXT_SID")
  clear_and_add_message("THE_ARMOURER_GODSLAYER_SPEECH_TEXT2_SID")
else
  local armourer_gift_key = "armourer_gift_generated"
  local gift_generated = get_creature_additional_property(PLAYER_ID, armourer_gift_key)

  if string.len(gift_generated) == 0 then
    -- Generate one of the three possible gifts.
    -- The shield has 75/25 divine/shadow, and is best against the eight
    -- "regular" deities.
    -- The helm has 75/25 shadow/divine, and provides the best protection
    -- against Sceadugenga.
    -- The mail is 50/50.
    if RNG_percent_chance(33) then
      add_object_to_player_tile("telarian_helm")
    elseif RNG_percent_chance(33) then
      add_object_to_player_tile("telarian_shield")
    else
      add_object_to_player_tile("telarian_mail")
    end

    add_message_with_pause("THE_ARMOURER_SPEECH_ARMOUR_SID")
    add_message_with_pause("THE_ARMOURER_SPEECH_ARMOUR2_SID")
    clear_and_add_message("THE_ARMOURER_SPEECH_ARMOUR3_SID")

    set_creature_additional_property(PLAYER_ID, armourer_gift_key, "1")
  else
    clear_and_add_message("THE_ARMOURER_SPEECH_TEXT_SID")
  end
end
