local trainable_stats = {["a"]=0, ["b"]=1, ["c"]=2, ["d"]=3, ["e"]=4, ["f"]=5, ["g"]=6}

add_message_with_pause("MELURA_SPEECH_TEXT_SID")
local keypress = add_char_message("MELURA_SPEECH_STATISTIC_SID")
local stat_enum = trainable_stats[keypress]

if stat_enum ~= nil then
  local payment = tonumber(add_prompt_message("MELURA_SPEECH_AMOUNT_SID"))
  local avail_funds = count_currency("player")

  if payment > avail_funds then
    clear_and_add_message("MELURA_NSF_SID")
  else
    -- TODO!    
  end
else
  clear_and_add_message("MELURA_BAD_INPUT_SID")
end

