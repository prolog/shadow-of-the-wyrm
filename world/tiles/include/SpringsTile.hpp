#pragma once
#include "Tile.hpp"

enum struct SpringsTemperature
{
  SPRINGS_TEMPERATURE_COOL = 10,
  SPRINGS_TEMPERATURE_HOT = 60
};

class SpringsTile : public Tile
{
  public:
    SpringsTile();
    bool operator==(const SpringsTile& sp) const;

    TileType get_tile_type() const override;
    TileSuperType get_tile_super_type() const;
    WaterType get_water_type() const override;
    
    std::string get_tile_description_sid() const override;

    virtual Tile* clone() override;

    virtual void set_temperature(const int new_temperature);
    virtual int get_temperature() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    int temperature;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

