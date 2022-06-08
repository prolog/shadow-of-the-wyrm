#pragma once

enum struct AttackType
{
  ATTACK_TYPE_UNDEFINED = -1,
  ATTACK_TYPE_MELEE_PRIMARY = 0,
  ATTACK_TYPE_MELEE_SECONDARY = 1,
  ATTACK_TYPE_RANGED = 2,
  ATTACK_TYPE_MAGICAL = 3,
  ATTACK_TYPE_MAGICAL_WANDS = 4,
  // Used for attacks like kicking, etc., which are always unarmed and make 
  // no use of anything in the inventory or equipment.
  ATTACK_TYPE_MELEE_TERTIARY_UNARMED = 5
};

enum struct AttackSequenceType
{
  ATTACK_SEQUENCE_INITIAL = 0,
  ATTACK_SEQUENCE_COUNTER = 1,
  ATTACK_SEQUENCE_FOLLOW_THROUGH = 2
};
