require('constants')

local function trade_magici()
  -- Add a random spellbook to the player's tile.
  local spellbook_ids = get_spellbooks()
  local sp_size = table.getn(spellbook_ids)

  if sp_size > 0 then
    local spellbook = spellbook_ids[RNG_range(1, sp_size)]
  
    add_object_to_player_tile(spellbook)
    clear_and_add_message("HRETHEL_TRADE_DEAL_SID")

    -- Remove the score of magici shards.
    remove_object_from_player(MAGICI_SHARD_ID, 20)
  end
end

local function no_deal()
  clear_and_add_message("HRETHEL_TRADE_NO_DEAL_SID")
end

-- Hrethel will offer a random spellbook in exchange for 20 magici shards.
local magici_cnt = get_item_count(PLAYER_ID, MAGICI_SHARD_ID)

if magici_cnt >= 20 then
  if add_confirmation_message("HRETHEL_TRADE_SID") then
    trade_magici()
  else
    no_deal()
  end
else
  add_message("HRETHEL_SPEECH_TEXT_SID")
end
