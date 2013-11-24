#pragma once
#include "ISeason.hpp"

class Winter : public ISeason
{
  public:
    Winter();
    
    Season get_season() const;
    std::string get_description_sid() const;
    std::string get_new_season_message_sid() const;

    Season get_previous_season() const;
    Season get_next_season() const;

    ISeason* clone();
    
  protected:
    void initialize_months();

  private:
    ClassIdentifier internal_class_identifier() const override;
};
