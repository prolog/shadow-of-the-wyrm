require('constants')

if player_has_item(FORGED_DOCUMENTS_ID) then
  local hf_cnt = count_creature_humanoid_followers(PLAYER_ID)

  if hf_cnt == 2 then
    remove_object_from_player(FORGED_DOCUMENTS_ID)
    add_object_to_player_tile(CARCASSIA_STASH_KEY_ID)

    clear_and_add_message("BALABIN_TRANSFER_KEY_SID")
  else
    clear_and_add_message("BALABIN_UNEXPECTED_PARTY_SID")

    set_hostility(SPEAKING_CREATURE_ID, PLAYER_ID)
    summon_monsters_around_creature({CARCASSIAN_GUARD_ID, CARCASSIAN_BLACKKNIFE_ID}, PLAYER_ID, RNG_range(3, 6), true)
  end
else
  clear_and_add_message("BALABIN_SPEECH_TEXT_SID")
end
