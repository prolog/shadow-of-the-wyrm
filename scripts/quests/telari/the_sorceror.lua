require('constants')

add_message_with_pause("THE_SORCEROR_GATEWAY_TEXT_SID")

local function drain_hp_and_ap(cr_id)
  local new_base_hp = get_creature_base_hp(cr_id) * 0.75
  local cur_hp = get_creature_current_hp(cr_id)
  local new_base_ap = get_creature_base_ap(cr_id) * 0.75
  local cur_ap = get_creature_current_ap(cr_id)

  if new_base_hp >= 1 then
    set_creature_base_hp(cr_id, new_base_hp)

    if new_base_hp < cur_hp then
      set_creature_current_hp(cr_id, new_base_hp)
    end
  end

  if new_base_ap >= 1 then
    set_creature_base_ap(cr_id, new_base_ap)

    if new_base_ap < cur_ap then
      set_creature_current_ap(cr_id, new_base_ap)
    end
  end
end

if has_artifact_in_inventory(PLAYER_ID) then
  add_message_with_pause("THE_SORCEROR_ARTIFACT_TEXT_SID")
  
  local winner = get_creature_additional_property(PLAYER_ID, "CREATURE_PROPERTIES_WINNER")
  local drain = true

  -- People who've completed either ending are immune to the draining
  -- effects of travelling from Telari back to the world.
  if string.len(winner) > 0 then
    drain = false
  else
    add_message_with_pause("THE_SORCEROR_GATEWAY_TEXT2_SID")
  end

  local selected, art_id, base_id = select_item(PLAYER_ID, CITEM_FILTER_ARTIFACT)

  if selected then
    if drain == true then
      drain_hp_and_ap(PLAYER_ID)
    end

    remove_object_from_player(base_id)
    load_map(PLAYER_ID, WORLD_MAP_ID)
  end
else
  clear_and_add_message("THE_SORCEROR_NO_ARTIFACT_TEXT_SID")
end

