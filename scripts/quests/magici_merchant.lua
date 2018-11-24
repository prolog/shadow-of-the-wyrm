require('constants')
require('merchant_common')

-- Magici merchants sell the stuff at hugely inflated prices.
local magici_cost = 500

merchant_common.chat(PLAYER_ID, MAGICI_SHARD_ID, magici_cost, "MAGICI_MERCHANT_OFFER_SID", "MAGICI_MERCHANT_ACCEPT_SID", "MAGICI_MERCHANT_DECLINE_SID", "MAGICI_MERCHANT_INSUFFICIENT_FUNDS_SID")
