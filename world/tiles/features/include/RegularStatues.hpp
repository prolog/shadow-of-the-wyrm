#pragma once
#include "Feature.hpp"

// A number of lightweight regular statues that can be generated
// by the StatueGenerator.
class RegularStatue : public Feature
{
  public:
    RegularStatue();

    virtual bool handle();
    virtual bool kick();
    virtual bool get_is_blocking() const;

    virtual uchar get_symbol() const;

    // get_description_sid() not implemented because this is an abstract
    // parent class.

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};


class PetrifiedCorpseStatue : public RegularStatue
{
  public:
    PetrifiedCorpseStatue();
    PetrifiedCorpseStatue(const std::string& corpse_description_sid);
    bool operator==(const PetrifiedCorpseStatue& statue) const;

    void set_corpse_description_sid(const std::string& new_corpse_description_sid);
    std::string get_corpse_description_sid() const;

    virtual Feature* clone();
    
    std::pair<std::string, std::vector<std::string>> get_description_and_replacement_sids() const;

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

  protected:
    std::string get_description_sid() const;

    std::string corpse_description_sid;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<PetrifiedCorpseStatue> PetrifiedCorpseStatuePtr;
