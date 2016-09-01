require('constants')

local trainable_stats = {["a"]=0, ["b"]=1, ["c"]=2, ["d"]=3, ["e"]=4, ["f"]=5, ["g"]=6}

add_message_with_pause("MELURA_SPEECH_TEXT_SID")
local keypress = add_char_message("MELURA_SPEECH_STATISTIC_SID")
local stat_enum = trainable_stats[keypress]

if stat_enum ~= nil then
  local payment = tonumber(add_prompt_message("MELURA_SPEECH_AMOUNT_SID"))
  local avail_funds = count_currency(PLAYER_ID)

  if payment > avail_funds then
    clear_and_add_message("MELURA_NSF_SID")
  else
    -- The number of marks to add to the stat.
    local improve_amt = math.floor(payment / 100)

    -- The chance to add another mark, after the guaranteed number of
    -- marks are added.
    local improve_chance = payment % 100

    -- Take the player's money.
    remove_object_from_player(CURRENCY_ID, payment)

    -- Improve the player's stats: always mark the stat, as Melura's
    -- training is that good.
    mark_stat(PLAYER_ID, stat_enum, improve_amt, true)

    if RNG_percent_chance(improve_chance) then
      mark_stat(PLAYER_ID, stat_enum, 1, true)
    end

    clear_and_add_message("MELURA_STAT_IMPROVED_SID")
  end
else
  clear_and_add_message("MELURA_BAD_INPUT_SID")
end

