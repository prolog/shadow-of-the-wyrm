#pragma once
#include "Feature.hpp"
#include "Symbol.hpp"

class Sarcophagus : public Feature
{
  public:
    Sarcophagus(const Symbol& new_symbol);
    Sarcophagus(const Symbol& new_symbol, const MaterialType material);
    bool operator==(const Sarcophagus& sar) const;

    virtual Feature* clone() override;

    virtual std::pair<std::string, std::vector<std::string>> get_description_and_replacement_sids() const override;

    virtual void set_inscription_sid(const std::string& new_inscription_sid);
    virtual std::string get_inscription_sid() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    virtual std::string get_description_sid() const override;

    std::string inscription_sid;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using SarcophagusPtr = std::shared_ptr<Sarcophagus>;
