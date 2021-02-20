require('constants')

local function do_trade(num_scrolls)
  local num_inkpots = num_scrolls * 3
  remove_object_from_player("_inkpot", num_inkpots)
  add_object_to_player_tile("_blank_scroll", num_scrolls)
  clear_and_add_message("THESILEA_TRADE_COMPLETE_SID")
end

local function no_deal()
  clear_and_add_message("THESILEA_TRADE_NO_DEAL_SID")
end

-- Thesilea will offer to trade a blank scroll for three inkpots.
local inkpots = get_item_count(PLAYER_ID, "_inkpot")
local num_scrolls_avail = math.floor(inkpots / 3)

if inkpots >= 3 then
  if num_scrolls_avail > 1 then
    local num_scrolls = tonumber(add_prompt_message("THESILEA_TRADE_MULTIPLE_SID"))
    
    if num_scrolls == nil then
      clear_and_add_message("THESILEA_NONSENSE_SID")
    elseif num_scrolls > num_scrolls_avail then
      clear_and_add_message("THESILEA_TRADE_BAD_NUMBER_SID")
    elseif num_scrolls <= 0 then
      no_deal()
    else
      do_trade(num_scrolls)
    end
  else
    if add_confirmation_message("THESILEA_TRADE_SINGLE_SID") then
      do_trade(1)
    else
      no_deal()
    end
  end
else
  add_message("THESILEA_SPEECH_TEXT_SID")
end