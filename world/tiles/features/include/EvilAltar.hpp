#pragma once
#include "Altar.hpp"

// A convenience class that sets up an evil altar appropriately.
class EvilAltar : public Altar
{
  public:
    EvilAltar();
    EvilAltar(const std::string& new_deity_id);
    virtual Feature* clone() override;

  protected:
    std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
