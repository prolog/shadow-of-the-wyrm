#pragma once
#include <map>
#include <string>
#include "common.hpp"
#include "ISerializable.hpp"

class StartingLocation : public ISerializable
{
  public:
    StartingLocation();
    StartingLocation(const std::string& ident, const Coordinate& sloc, const std::string& short_desc_sid, const std::string& desc_sid);
    bool operator==(const StartingLocation sl2) const;

    void set_id(const std::string& new_id);
    std::string get_id() const;

    void set_location(const Coordinate& new_location);
    Coordinate get_location() const;

    void set_short_description_sid(const std::string& new_short_description_sid);
    std::string get_short_description_sid() const;

    void set_description_sid(const std::string& new_description_sid);
    std::string get_description_sid() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::string id;
    Coordinate location;
    std::string short_description_sid;
    std::string description_sid;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using StartingLocationMap = std::map<std::string, StartingLocation>;