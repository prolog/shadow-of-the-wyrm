require('quest')

-- Cornel doesn't actually give a quest, since he'll die right
-- after, but he gives a locket that needs to be given to the
-- right person - Cadlind, in Isen Dun.
local cy, cx = get_creature_yx("cornel")

add_message_with_pause("CORNEL_LOCKET_SID")
add_message_with_pause("CORNEL_LOCKET2_SID")
add_message_with_pause("CORNEL_LOCKET3_SID")
add_message_with_pause("CORNEL_LOCKET4_SID")
add_message_with_pause("CORNEL_LOCKET5_SID")
clear_and_add_message("CORNEL_LOCKET6_SID")

add_object_to_tile("wave_locket", cy, cx)
remove_creature_from_map("cornel")


