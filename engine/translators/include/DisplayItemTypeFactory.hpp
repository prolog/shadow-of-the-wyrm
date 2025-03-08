#pragma once
#include <map>
#include <vector>
#include "DisplayItemType.hpp"
#include "ItemTypes.hpp"

// Definitions of classes for all the item types.
class DefaultDisplayItemType : public DisplayItemType
{
  public:
    DefaultDisplayItemType();
    virtual ~DefaultDisplayItemType() = default;
};

class MiscDisplayItemType : public DisplayItemType
{
  public:
    MiscDisplayItemType();
    virtual ~MiscDisplayItemType() = default;
};

class WeaponDisplayItemType : public DisplayItemType
{
  public:
    WeaponDisplayItemType();
    virtual ~WeaponDisplayItemType() = default;
};

class ArmourDisplayItemType : public DisplayItemType
{
  public:
    ArmourDisplayItemType();
    virtual ~ArmourDisplayItemType() = default;
};

class PotionDisplayItemType : public DisplayItemType
{
  public:
    PotionDisplayItemType();
    virtual ~PotionDisplayItemType() = default;
};

class BookDisplayItemType : public DisplayItemType
{
  public:
    BookDisplayItemType();
    virtual ~BookDisplayItemType() = default;
};

class ScrollDisplayItemType : public DisplayItemType
{
  public:
    ScrollDisplayItemType();
    virtual ~ScrollDisplayItemType() = default;
};

class WandDisplayItemType : public DisplayItemType
{
  public:
    WandDisplayItemType();
    virtual ~WandDisplayItemType() = default;
};

class StaffDisplayItemType : public DisplayItemType
{
  public:
    StaffDisplayItemType();
    virtual ~StaffDisplayItemType() = default;
};

class RingDisplayItemType : public DisplayItemType
{
  public:
    RingDisplayItemType();
    virtual ~RingDisplayItemType() = default;
};

class AmuletDisplayItemType : public DisplayItemType
{
  public:
    AmuletDisplayItemType();
    virtual ~AmuletDisplayItemType() = default;
};

class FoodDisplayItemType : public DisplayItemType
{
  public:
    FoodDisplayItemType();
    virtual ~FoodDisplayItemType() = default;
};

class AmmunitionDisplayItemType : public DisplayItemType
{
  public:
    AmmunitionDisplayItemType();
    virtual ~AmmunitionDisplayItemType() = default;
};

class PlantDisplayItemType : public DisplayItemType
{
  public:
    PlantDisplayItemType();
    virtual ~PlantDisplayItemType() = default;
};

class BoatDisplayItemType : public DisplayItemType
{
  public:
    BoatDisplayItemType();
    virtual ~BoatDisplayItemType() = default;
};

class CurrencyDisplayItemType : public DisplayItemType
{
  public:
    CurrencyDisplayItemType();
    virtual ~CurrencyDisplayItemType() = default;
};

class ToolsDisplayItemType : public DisplayItemType
{
  public:
    ToolsDisplayItemType();
    virtual ~ToolsDisplayItemType() = default;
};

class DisplayItemTypeFactory
{
  public:
    static DisplayItemTypePtr create(const ItemType item_type);
    static std::vector<DisplayItemTypePtr> create(const int item_symbol);

  protected:
    DisplayItemTypeFactory();
    ~DisplayItemTypeFactory();

    static void initialize_map();

    static std::map<ItemType, DisplayItemTypePtr> display_map;
};
