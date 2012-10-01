#pragma once
#include <string>
#include <set>
#include <boost/shared_ptr.hpp>
#include "CalendarTypes.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class ISeason
{
  public:
    virtual Season get_season() const = 0;
    virtual std::string get_description_sid() const = 0;
    virtual std::string get_new_season_message_sid() const = 0;

    virtual Season get_previous_season() const = 0;
    virtual Season get_next_season() const = 0;
    virtual std::set<Months> get_months_in_season() const;
    
  protected:
    virtual void initialize_months() = 0;
    
    std::set<Months> months_in_season;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & months_in_season;
    }
};

typedef boost::shared_ptr<ISeason> ISeasonPtr;
