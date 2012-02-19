#pragma once
#include <string>

class EquipmentCommandKeys
{
  public:
    static std::string WEAR_OR_REMOVE_HEAD;
    static std::string WEAR_OR_REMOVE_NECK;
    static std::string WEAR_OR_REMOVE_RIGHT_FINGER;
    static std::string WEAR_OR_REMOVE_LEFT_FINGER;
    static std::string WEAR_OR_REMOVE_RIGHT_HAND;
    static std::string WEAR_OR_REMOVE_LEFT_HAND;
    static std::string WEAR_OR_REMOVE_BODY;
    static std::string WEAR_OR_REMOVE_ABOUT_BODY;
    static std::string WEAR_OR_REMOVE_FEET;
    static std::string YOUR_ITEMS;
    static std::string EXIT_EQUIPMENT;

  protected:
    EquipmentCommandKeys();
    ~EquipmentCommandKeys();
};
