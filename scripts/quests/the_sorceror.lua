require('constants')

add_message_with_pause("THE_SORCEROR_GATEWAY_TEXT_SID")

if has_artifact_in_inventory(PLAYER_ID) then
  add_message_with_pause("THE_SORCEROR_ARTIFACT_TEXT_SID")
  local selected, art_id, base_id = select_item(PLAYER_ID, CITEM_FILTER_ARTIFACT)

  if selected then
    remove_object_from_player(base_id)
    add_message_with_pause("THE_SORCEROR_ARTIFACT_CONFIRM_TEXT_SID")
    load_map(PLAYER_ID, WORLD_MAP_ID)
  end
else
  clear_and_add_message("THE_SORCEROR_NO_ARTIFACT_TEXT_SID")
end
