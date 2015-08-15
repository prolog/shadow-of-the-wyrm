#include "Creature.hpp"
#include "StatusAilmentTextKeys.hpp"

using namespace std;

// Status ailment text keys:
const string StatusAilmentTextKeys::STATUS_HUNGER_STUFFED          = "STATUS_HUNGER_STUFFED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_STUFFED  = "STATUS_MESSAGE_HUNGER_STUFFED";
const string StatusAilmentTextKeys::STATUS_HUNGER_FULL             = "STATUS_HUNGER_FULL";
const string StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_FULL     = "STATUS_MESSAGE_HUNGER_FULL";
const string StatusAilmentTextKeys::STATUS_HUNGER_NORMAL           = "STATUS_HUNGER_NORMAL";
const string StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_NORMAL   = "STATUS_MESSAGE_HUNGER_NORMAL";
const string StatusAilmentTextKeys::STATUS_HUNGER_HUNGRY           = "STATUS_HUNGER_HUNGRY";
const string StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_HUNGRY   = "STATUS_MESSAGE_HUNGER_HUNGRY";
const string StatusAilmentTextKeys::STATUS_HUNGER_STARVING         = "STATUS_HUNGER_STARVING";
const string StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_STARVING = "STATUS_MESSAGE_HUNGER_STARVING";
const string StatusAilmentTextKeys::STATUS_HUNGER_DYING            = "STATUS_HUNGER_DYING";
const string StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_DYING    = "STATUS_MESSAGE_HUNGER_DYING";

const string StatusAilmentTextKeys::STATUS_BURDEN_UNBURDENED = "STATUS_BURDEN_UNBURDENED";
const string StatusAilmentTextKeys::STATUS_BURDEN_BURDENED = "STATUS_BURDEN_BURDENED";
const string StatusAilmentTextKeys::STATUS_BURDEN_STRAINED = "STATUS_BURDEN_STRAINED";
const string StatusAilmentTextKeys::STATUS_BURDEN_OVERBURDENED = "STATUS_BURDEN_OVERBURDENED";

const string StatusAilmentTextKeys::STATUS_POISON = "STATUS_POISON";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_POISONED = "STATUS_MESSAGE_PLAYER_POISONED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_POISON_CURED = "STATUS_MESSAGE_PLAYER_POISON_CURED";

const string StatusAilmentTextKeys::STATUS_MUTE = "STATUS_MUTE";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_MUTED = "STATUS_MESSAGE_PLAYER_MUTED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_MUTENESS_CURED = "STATUS_MESSAGE_PLAYER_MUTENESS_CURED";

const string StatusAilmentTextKeys::STATUS_PARALYSIS = "STATUS_PARALYSIS";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_PARALYZED = "STATUS_MESSAGE_PLAYER_PARALYZED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_PARALYSIS_CURED = "STATUS_MESSAGE_PLAYER_PARALYSIS_CURED";

const string StatusAilmentTextKeys::STATUS_SLOWNESS = "STATUS_SLOWNESS";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_SLOWED = "STATUS_MESSAGE_PLAYER_SLOWED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_SLOWNESS_CURED = "STATUS_MESSAGE_PLAYER_SLOWNESS_CURED";

const string StatusAilmentTextKeys::STATUS_HASTE = "STATUS_HASTE";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_HASTED = "STATUS_MESSAGE_PLAYER_HASTED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_HASTE_DONE = "STATUS_MESSAGE_PLAYER_HASTE_DONE";

const string StatusAilmentTextKeys::STATUS_STONE = "STATUS_STONE";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STONE = "STATUS_MESSAGE_PLAYER_STONE";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STONE_CURED = "STATUS_MESSAGE_PLAYER_STONE_CURED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_STONE_FINALIZE = "STATUS_MESSAGE_STONE_FINALIZE";
const string StatusAilmentTextKeys::STATUS_MESSAGE_STONE_CRUMBLE = "STATUS_MESSAGE_CORPSE_CRUMBLE";

const string StatusAilmentTextKeys::STATUS_BLOODIED = "STATUS_BLOODIED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_BLOODIED = "STATUS_MESSAGE_PLAYER_BLOODIED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_BLOODIED_CURED = "STATUS_MESSAGE_PLAYER_BLOODIED_CURED";

const string StatusAilmentTextKeys::STATUS_STUNNED = "STATUS_STUNNED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STUNNED = "STATUS_MESSAGE_PLAYER_STUNNED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STUNNED_CURED = "STATUS_MESSAGE_PLAYER_STUNNED_CURED";

const string StatusAilmentTextKeys::STATUS_EXPOSED = "STATUS_EXPOSED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_EXPOSED = "STATUS_MESSAGE_PLAYER_EXPOSED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_EXPOSED_CURED = "STATUS_MESSAGE_PLAYER_EXPOSED_CURED";

const string StatusAilmentTextKeys::STATUS_DISFIGURED = "STATUS_DISFIGURED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_DISFIGURED = "STATUS_MESSAGE_PLAYER_DISFIGURED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_DISFIGURED_CURED = "STATUS_MESSAGE_PLAYER_DISFIGURED_CURED";

const string StatusAilmentTextKeys::STATUS_IMMOBILE = "STATUS_IMMOBILE";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_IMMOBILE = "STATUS_MESSAGE_PLAYER_IMMOBILE";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_IMMOBILE_CURED = "STATUS_MESSAGE_PLAYER_IMMOBILE_CURED";

const string StatusAilmentTextKeys::STATUS_BLINDED = "STATUS_BLINDED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_BLINDED = "STATUS_MESSAGE_PLAYER_BLINDED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_BLINDNESS_CURED = "STATUS_MESSAGE_PLAYER_BLINDNESS_CURED";

const string StatusAilmentTextKeys::STATUS_INCORPOREAL = "STATUS_INCORPOREAL";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_INCORPOREAL = "STATUS_MESSAGE_PLAYER_INCORPOREAL";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_INCORPOREAL_CURED = "STATUS_MESSAGE_PLAYER_INCORPOREAL_CURED";

const string StatusAilmentTextKeys::STATUS_DRUNK = "STATUS_DRUNK";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_DRUNK = "STATUS_MESSAGE_PLAYER_DRUNK";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_SOBER = "STATUS_MESSAGE_PLAYER_SOBER";

const string StatusAilmentTextKeys::STATUS_FLYING = "STATUS_FLYING";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_FLYING = "STATUS_MESSAGE_PLAYER_FLYING";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_FLYING_CURED = "STATUS_MESSAGE_PLAYER_FLYING_CURED";

const string StatusAilmentTextKeys::STATUS_TIMEWALK = "STATUS_TIMEWALK";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_TIMEWALK = "STATUS_MESSAGE_PLAYER_TIMEWALK";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_TIMEWALK_CURED = "STATUS_MESSAGE_PLAYER_TIMEWALK_CURED";

// public functions
const string StatusAilmentTextKeys::get_npc_poisoned_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_POISONED);
}

const string StatusAilmentTextKeys::get_npc_undo_poison_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_POISON);
}

const string StatusAilmentTextKeys::get_npc_muted_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_MUTED);
}

const string StatusAilmentTextKeys::get_npc_undo_muteness_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_MUTENESS);
}

const string StatusAilmentTextKeys::get_npc_paralyzed_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_PARALYZED);
}

const string StatusAilmentTextKeys::get_npc_undo_paralysis_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_PARALYSIS);
}

const string StatusAilmentTextKeys::get_npc_slowed_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_SLOWED);
}

const string StatusAilmentTextKeys::get_npc_undo_slowness_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_SLOWNESS);
}

const string StatusAilmentTextKeys::get_npc_hasted_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_HASTED);
}

const string StatusAilmentTextKeys::get_npc_undo_haste_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_HASTE);
}

const string StatusAilmentTextKeys::get_npc_stone_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_STONE);
}

const string StatusAilmentTextKeys::get_npc_undo_stone_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_STONE);
}

const string StatusAilmentTextKeys::get_npc_bloodied_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_BLOODIED);
}

const string StatusAilmentTextKeys::get_npc_undo_bloodied_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_BLOODIED);
}

const string StatusAilmentTextKeys::get_npc_stunned_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_STUNNED);
}

const string StatusAilmentTextKeys::get_npc_undo_stunned_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_STUNNED);
}

const string StatusAilmentTextKeys::get_npc_exposed_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_EXPOSED);
}

const string StatusAilmentTextKeys::get_npc_undo_exposed_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_EXPOSED);
}

const string StatusAilmentTextKeys::get_npc_disfigured_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_DISFIGURED);
}

const string StatusAilmentTextKeys::get_npc_undo_disfigured_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_DISFIGURED);
}

const string StatusAilmentTextKeys::get_npc_immobile_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_IMMOBILE);
}

const string StatusAilmentTextKeys::get_npc_undo_immobile_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_IMMOBILE);
}

const string StatusAilmentTextKeys::get_npc_blinded_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_BLINDED);
}

const string StatusAilmentTextKeys::get_npc_undo_blindness_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_BLINDNESS);
}

const string StatusAilmentTextKeys::get_npc_incorporeal_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_INCORPOREAL);
}

const string StatusAilmentTextKeys::get_npc_undo_incorporeal_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_INCORPOREAL);
}

const string StatusAilmentTextKeys::get_npc_drunk_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_DRUNK);
}

const string StatusAilmentTextKeys::get_npc_sober_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_SOBER);
}

const string StatusAilmentTextKeys::get_npc_flying_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_FLYING);
}

const string StatusAilmentTextKeys::get_npc_undo_flying_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_FLYING);
}

const string StatusAilmentTextKeys::get_npc_timewalk_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_TIMEWALK);
}

const string StatusAilmentTextKeys::get_npc_undo_timewalk_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_TIMEWALK);
}

// Protected
const string StatusAilmentTextKeys::get_general_npc_message(const string& npc_sid, const string& message_sid)
{
  string npc = StringTable::get(npc_sid);
  string message = StringTable::get(message_sid);

  boost::replace_first(message, "%s", npc);
  message[0] = toupper(message[0]);

  return message;
}

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_POISONED = "STATUS_MESSAGE_NPC_POISONED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_POISON = "STATUS_MESSAGE_NPC_UNDO_POISON";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_MUTED = "STATUS_MESSAGE_NPC_MUTED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_MUTENESS = "STATUS_MESSAGE_NPC_UNDO_MUTENESS";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_PARALYZED = "STATUS_MESSAGE_NPC_PARALYZED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_PARALYSIS = "STATUS_MESSAGE_NPC_UNDO_PARALYSIS";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_SLOWED = "STATUS_MESSAGE_NPC_SLOWED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_SLOWNESS = "STATUS_MESSAGE_NPC_UNDO_SLOWNESS";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_HASTED = "STATUS_MESSAGE_NPC_HASTED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_HASTE = "STATUS_MESSAGE_NPC_UNDO_HASTE";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_STONE = "STATUS_MESSAGE_NPC_STONE";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_STONE = "STATUS_MESSAGE_NPC_UNDO_STONE";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_BLOODIED = "STATUS_MESSAGE_NPC_BLOODIED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_BLOODIED = "STATUS_MESSAGE_NPC_UNDO_BLOODIED";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_STUNNED = "STATUS_MESSAGE_NPC_STUNNED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_STUNNED = "STATUS_MESSAGE_NPC_UNDO_STUNNED";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_EXPOSED = "STATUS_MESSAGE_NPC_EXPOSED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_EXPOSED = "STATUS_MESSAGE_NPC_UNDO_EXPOSED";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_DISFIGURED = "STATUS_MESSAGE_NPC_DISFIGURED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_DISFIGURED = "STATUS_MESSAGE_NPC_UNDO_DISFIGURED";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_IMMOBILE = "STATUS_MESSAGE_NPC_IMMOBILE";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_IMMOBILE = "STATUS_MESSAGE_NPC_UNDO_IMMOBILE";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_BLINDED = "STATUS_MESSAGE_NPC_BLINDED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_BLINDNESS = "STATUS_MESSAGE_NPC_UNDO_BLINDNESS";
const string StatusAilmentTextKeys::STATUS_MESSAGE_BLIND_RANGED_COMBAT = "STATUS_MESSAGE_BLIND_RANGED_COMBAT";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_INCORPOREAL = "STATUS_MESSAGE_NPC_INCORPOREAL";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_INCORPOREAL = "STATUS_MESSAGE_NPC_UNDO_INCORPOREAL";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_DRUNK = "STATUS_MESSAGE_NPC_DRUNK";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_SOBER = "STATUS_MESSAGE_NPC_SOBER";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_FLYING = "STATUS_MESSAGE_NPC_FLYING";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_FLYING = "STATUS_MESSAGE_NPC_UNDO_FLYING";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_TIMEWALK = "STATUS_MESSAGE_NPC_TIMEWALK";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_TIMEWALK = "STATUS_MESSAGE_NPC_UNDO_TIMEWALK";