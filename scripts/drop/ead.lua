require('constants')
require('drop')
require('ead_common')

local function ead_elysian_coin(dropping_creature_id, shopkeeper_id, item_id, item_base_id, drop_y, drop_x)
  if item_base_id == ELYSIAN_COIN_ID and dropping_creature_id == PLAYER_ID then
    add_message_with_pause("EAD_COIN_DROP_SID")
    add_message_with_pause("EAD_TELARI_CONFIRM_SID")

    ead_common.send_to_telari(dropping_creature_id)
  end
end

local ead_fn = ead_elysian_coin

drop.set_drop_fn("ead", ead_elysian_coin)

