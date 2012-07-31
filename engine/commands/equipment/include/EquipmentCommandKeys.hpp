#pragma once
#include <string>

class EquipmentCommandKeys
{
  public:
    static const std::string WEAR_OR_REMOVE_HEAD;
    static const std::string WEAR_OR_REMOVE_NECK;
    static const std::string WEAR_OR_REMOVE_RIGHT_FINGER;
    static const std::string WEAR_OR_REMOVE_LEFT_FINGER;
    static const std::string WEAR_OR_REMOVE_WIELDED;
    static const std::string WEAR_OR_REMOVE_OFF_HAND;
    static const std::string WEAR_OR_REMOVE_BODY;
    static const std::string WEAR_OR_REMOVE_ABOUT_BODY;
    static const std::string WEAR_OR_REMOVE_FEET;
    static const std::string WEAR_OR_REMOVE_RANGED;
    static const std::string WEAR_OR_REMOVE_AMMUNITION;
    static const std::string YOUR_ITEMS;
    static const std::string EXIT_EQUIPMENT;

  protected:
    EquipmentCommandKeys();
    ~EquipmentCommandKeys();
};
