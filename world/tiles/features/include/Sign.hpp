#pragma once
#include "Feature.hpp"
#include "Symbol.hpp"

class Sign : public Feature
{
  public:
    Sign(const Symbol& new_symbol, const std::string& new_text_sid);

    virtual Feature* clone() override;
    virtual bool get_is_blocking() const;

    virtual std::pair<std::string, std::vector<std::string>> get_description_and_replacement_sids() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
