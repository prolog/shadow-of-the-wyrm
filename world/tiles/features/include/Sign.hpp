#pragma once
#include "Feature.hpp"

class Sign : public Feature
{
  public:
    Sign(const std::string& new_text_sid);
    bool operator==(const Sign& s) const;

    virtual Feature* clone() override;
    virtual uchar get_symbol() const override;
    virtual bool get_is_blocking() const;
    virtual std::string get_text_sid() const;
    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

    virtual std::string get_description_sid() const override;
    virtual std::pair<std::string, std::vector<std::string>> get_description_and_replacement_sids() const override;

  protected:
    std::string text_sid;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
