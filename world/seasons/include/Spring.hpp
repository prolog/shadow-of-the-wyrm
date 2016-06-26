#pragma once
#include "ISeason.hpp"

class Spring : public ISeason
{
  public:
    Spring();
    
    Season get_season() const override;
    std::string get_description_sid() const override;
    std::string get_new_season_message_sid() const override;

    Season get_previous_season() const override;
    Season get_next_season() const override;

    ISeason* clone() override;
    
  protected:
    void initialize_months() override;
    void initialize_foragables() override;
    void initialize_herbs() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
