#pragma once
#include "DisplayItemType.hpp"
#include "ItemTypes.hpp"

// Definitions of classes for all the item types.
class DefaultDisplayItemType : public DisplayItemType
{
  public:
    DefaultDisplayItemType();
};

class MiscDisplayItemType : public DisplayItemType
{
  public:
    MiscDisplayItemType();
};

class WeaponDisplayItemType : public DisplayItemType
{
  public:
    WeaponDisplayItemType();
};

class ArmourDisplayItemType : public DisplayItemType
{
  public:
    ArmourDisplayItemType();
};

class PotionDisplayItemType : public DisplayItemType
{
  public:
    PotionDisplayItemType();
};

class BookDisplayItemType : public DisplayItemType
{
  public:
    BookDisplayItemType();
};

class ScrollDisplayItemType : public DisplayItemType
{
  public:
    ScrollDisplayItemType();
};

class WandDisplayItemType : public DisplayItemType
{
  public:
    WandDisplayItemType();
};

class StaffDisplayItemType : public DisplayItemType
{
  public:
    StaffDisplayItemType();
};

class RingDisplayItemType : public DisplayItemType
{
  public:
    RingDisplayItemType();
};

class AmuletDisplayItemType : public DisplayItemType
{
  public:
    AmuletDisplayItemType();
};

class FoodDisplayItemType : public DisplayItemType
{
  public:
    FoodDisplayItemType();
};

class AmmunitionDisplayItemType : public DisplayItemType
{
  public:
    AmmunitionDisplayItemType();
};

class PlantDisplayItemType : public DisplayItemType
{
  public:
    PlantDisplayItemType();
};

class BoatDisplayItemType : public DisplayItemType
{
  public:
    BoatDisplayItemType();
};

class CurrencyDisplayItemType : public DisplayItemType
{
  public:
    CurrencyDisplayItemType();
};

class ToolsDisplayItemType : public DisplayItemType
{
  public:
    ToolsDisplayItemType();
};

class DisplayItemTypeFactory
{
  public:
    static DisplayItemTypePtr create(const ItemType item_type);

  protected:
    DisplayItemTypeFactory();
    ~DisplayItemTypeFactory();
};
