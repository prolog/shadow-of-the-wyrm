require('constants')

local literacy = get_skill_value(PLAYER_ID, CSKILL_GENERAL_LITERACY)
local cantrips = get_skill_value(PLAYER_ID, CSKILL_MAGIC_CANTRIPS)

if cantrips == 0 then
  if literacy == 0 then
    clear_and_add_message("HEDGE_WIZARD_LITERACY_SID")
  else
    local currency = get_item_count(PLAYER_ID, CURRENCY_ID)

    if currency >= 3000 then
      if add_confirmation_message("HEDGE_WIZARD_CANTRIPS_SID") then
        clear_and_add_message("HEDGE_WIZARD_CANTRIPS_ACCEPT_SID")
        remove_object_from_player(CURRENCY_ID, 3000)

        local cantrips_val = RNG_range(5, 30)
        set_skill_value(PLAYER_ID, CSKILL_MAGIC_CANTRIPS, cantrips_val)
        add_object_to_player_tile("flame_dart_spellbook")
      else
        clear_and_add_message("HEDGE_WIZARD_CANTRIPS_DECLINE_SID")
      end
    else
      clear_and_add_message("HEDGE_WIZARD_NSF_SID")
    end
  end
else
  clear_and_add_message("HEDGE_WIZARD_SPEECH_TEXT_SID")
end
