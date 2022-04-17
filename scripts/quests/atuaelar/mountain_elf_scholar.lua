local speeches = {{"MOUNTAIN_ELF_SCHOLAR_SPEECH_TEXT_SID"}, {"MOUNTAIN_ELF_SCHOLAR_CARCASSIA_SID", "MOUNTAIN_ELF_SCHOLAR_CARCASSIA2_SID"}}

local speech = speeches[RNG_range(1, #speeches)]

for i = 1, #speech do
  local fn = add_message_with_pause
  
  if i == #speech then
    fn = clear_and_add_message
  end

  fn(speech[i])
end

