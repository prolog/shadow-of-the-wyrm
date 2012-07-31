#pragma once

enum EquipmentWornLocation
{
  EQUIPMENT_WORN_NONE = -1,
  EQUIPMENT_WORN_HEAD = 0,
  EQUIPMENT_WORN_NECK = 1,
  EQUIPMENT_WORN_RIGHT_FINGER = 2,
  EQUIPMENT_WORN_LEFT_FINGER = 3,
  EQUIPMENT_WORN_WIELDED = 4,
  EQUIPMENT_WORN_OFF_HAND = 5,
  EQUIPMENT_WORN_BODY = 6,
  EQUIPMENT_WORN_ABOUT_BODY = 7,
  EQUIPMENT_WORN_FEET = 8,
  EQUIPMENT_WORN_RANGED_WEAPON = 9,
  EQUIPMENT_WORN_AMMUNITION = 10,
  EQUIPMENT_WORN_LAST = 11
};

inline EquipmentWornLocation operator--(EquipmentWornLocation &ewl, int)
{
  return ewl = EquipmentWornLocation(ewl-1);
}

inline EquipmentWornLocation operator++(EquipmentWornLocation &ewl, int)
{
  return ewl = EquipmentWornLocation(ewl+1);
}

