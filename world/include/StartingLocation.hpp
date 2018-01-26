#pragma once
#include <string>
#include "common.hpp"
#include "ISerializable.hpp"

class StartingLocation : public ISerializable
{
  public:
    StartingLocation();
    StartingLocation(const Coordinate& sloc, const std::string& desc_sid);
    bool operator==(const StartingLocation sl2) const;

    void set_location(const Coordinate& new_location);
    Coordinate get_location() const;

    void set_description_sid(const std::string& new_description_sid);
    std::string get_description_sid() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    Coordinate location;
    std::string description_sid;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

