#pragma once
#include "ISeason.hpp"

class Summer : public ISeason
{
  public:
    Summer();
    
    Season get_season() const;
    std::string get_description_sid() const;

    Season get_previous_season() const;
    Season get_next_season() const;
    
  protected:
    void initialize_months();
};
