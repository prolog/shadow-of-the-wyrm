#pragma once
#include <map>
#include <string>
#include <set>
#include <memory>
#include <vector>
#include "CalendarTypes.hpp"
#include "ISerializable.hpp"
#include "tiles.hpp"

class ISeason : public ISerializable
{
  public:
    virtual bool operator==(ISeason& season) const;

    virtual Season get_season() const = 0;
    virtual std::string get_description_sid() const = 0;
    virtual std::string get_new_season_message_sid() const = 0;

    virtual Season get_previous_season() const = 0;
    virtual Season get_next_season() const = 0;
    virtual std::set<Months> get_months_in_season() const;

    std::map<TileType, std::vector<std::string>> get_foragables() const;
    std::map<TileType, std::vector<std::string>> get_herbs() const;

    virtual ISeason* clone() = 0;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;
    
  protected:
    virtual void initialize_months() = 0;
    virtual void initialize_foragables() = 0;
    virtual void initialize_herbs() = 0;
    
    std::set<Months> months_in_season;
    std::map<TileType, std::vector<std::string>> foragables;
    std::map<TileType, std::vector<std::string>> herbs;

  private:
    virtual ClassIdentifier internal_class_identifier() const = 0;
};

using ISeasonPtr = std::shared_ptr<ISeason>;
