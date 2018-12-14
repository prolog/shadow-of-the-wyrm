require('constants')

local glich_gift_key = "glich_gift_generated"
local gift_generated = get_creature_additional_property(PLAYER_ID, glich_gift_key)


if string.len(gift_generated) == 0 then
  local glich_gifts = {{GOLDEN_APPLE_ID, 1},
                       {SILVER_APPLE_ID, 1},
                       {SILVERWEED_ID, 3},
                       {WHITEFLOWER_ID, 10}}

  local glich_gift = glich_gifts[RNG_range(1, #glich_gifts)]

  add_message_with_pause("GLICH_GIFT_SPEECH_TEXT_SID")
  clear_and_add_message("GLICH_GIFT_SPEECH_TEXT2_SID")

  add_object_to_player_tile(glich_gift[1], glich_gift[2])
  local gift_generated_val = "1"

  if RNG_percent_chance(10) then
    -- Intentional glitch in Glich! :)
    gift_generated_val = ""
  end
  set_creature_additional_property(PLAYER_ID, glich_gift_key, gift_generated_val)
else
  clear_and_add_message("GLICH_SPEECH_TEXT_SID")
end
