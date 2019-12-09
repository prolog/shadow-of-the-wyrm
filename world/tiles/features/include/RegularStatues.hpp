#pragma once
#include "Feature.hpp"
#include "Symbol.hpp"

// A number of lightweight regular statues that can be generated
// by the FeatureGenerator.
class RegularStatue : public Feature
{
  public:
    RegularStatue(const Symbol& new_symbol);

    virtual bool get_is_blocking() const override;

    // get_description_sid() not implemented because this is an abstract
    // parent class.

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};


class PetrifiedCorpseStatue : public RegularStatue
{
  public:
    PetrifiedCorpseStatue(const Symbol& new_symbol);
    PetrifiedCorpseStatue(const Symbol& new_symbol, const std::string& corpse_description_sid);
    bool operator==(const PetrifiedCorpseStatue& statue) const;

    void set_corpse_description_sid(const std::string& new_corpse_description_sid);
    std::string get_corpse_description_sid() const;

    virtual Feature* clone() override;
    
    std::pair<std::string, std::vector<std::string>> get_description_and_replacement_sids() const override;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::string get_description_sid() const override;

    std::string corpse_description_sid;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using PetrifiedCorpseStatuePtr = std::shared_ptr<PetrifiedCorpseStatue>;
