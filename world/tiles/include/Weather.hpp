#pragma once
#include <memory>
#include "ISerializable.hpp"

class Weather : public ISerializable
{
  public:
    Weather(const std::string& wind_speed);
    bool operator==(const Weather& w) const;

    void set_wind_speed(const int new_wind_speed);
    int get_wind_speed() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    int wind_speed;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using WeatherPtr = std::unique_ptr<Weather>;


