require('constants')
module(..., package.seeall)

-- Common file for the membership checking/trade/etc code for the high tower
-- students that would otherwise be duplicated.
function chat(item_id, item_cnt, trade_item_id, trade_sid, accept_sid, decline_sid, default_sid)
  local item = get_item_count(PLAYER_ID, item_id)

  if has_membership(PLAYER_ID, HIGH_TOWER_GUILD_ID) then
    if item >= item_cnt then
      if add_confirmation_message(trade_sid) then
        clear_and_add_message(accept_sid)

        remove_object_from_player(item_id, item_cnt)
        add_object_to_player_tile(trade_item_id)
      else
        clear_and_add_message(decline_sid)
      end
    else
      clear_and_add_message(trade_sid)
    end
  else
    clear_and_add_message(default_sid)
  end
end

