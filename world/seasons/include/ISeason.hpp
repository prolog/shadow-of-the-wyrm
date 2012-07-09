#pragma once
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "CalendarTypes.hpp"

class ISeason
{
  public:
    virtual Season get_season() const = 0;
    virtual std::string get_description_sid() const = 0;

    virtual Season get_previous_season() const = 0;
    virtual Season get_next_season() const = 0;
    virtual std::vector<Months> get_months_in_season() const;
    
  protected:
    virtual void initialize_months() = 0;
    
    std::vector<Months> months_in_season;
};

typedef boost::shared_ptr<ISeason> ISeasonPtr;
