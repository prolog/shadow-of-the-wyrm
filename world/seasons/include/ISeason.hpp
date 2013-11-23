#pragma once
#include <string>
#include <set>
#include <memory>
#include "CalendarTypes.hpp"
#include "ISerializable.hpp"

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

    virtual ISeason* clone() = 0;

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);
    
  protected:
    virtual void initialize_months() = 0;
    
    std::set<Months> months_in_season;

  private:
    virtual ClassIdentifier internal_class_identifier() const = 0;
};

typedef std::shared_ptr<ISeason> ISeasonPtr;
