#pragma once
#include "ISeason.hpp"

class Autumn : public ISeason
{
  public:
    Autumn();
    
    Season get_season() const;
    std::string get_description_sid() const;
    std::string get_new_season_message_sid() const;

    Season get_previous_season() const;
    Season get_next_season() const;
    
  protected:
    void initialize_months();
};

