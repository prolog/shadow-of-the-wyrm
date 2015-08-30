#pragma once
#include <map>
#include "common.hpp"
#include "ISerializable.hpp"
#include "RarityTypes.hpp"

// A general-purpose class used to track some basic info about items or creatures
// to determine what to generate.  Further necessary values (HP, exp, etc) for 
// creatures can be found in CreatureGenerationValues.hpp.
class GenerationValues : public ISerializable
{
  public:
    GenerationValues();
    virtual ~GenerationValues();
    bool operator==(const GenerationValues& cgv) const;

    void set_current(const int new_current);
    int incr_current();
    int get_current() const;

    void set_maximum(const int new_maximum);
    int get_maximum() const;
    bool is_maximum_reached() const;

    void set_danger_level(const int new_danger_level);
    int get_danger_level() const;
    
    void set_rarity(const Rarity new_rarity);
    Rarity get_rarity() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    // The current number that has been generated.
    int current;

    // The maximum number that can be generated, if non-negative.  If negative, ignored.
    int maximum;

    // The "danger level" at which the entity may start appearing,
    // if it is not out of depth/danger-depth.
    int danger_level;

    // The more rare something is, the less chance of it getting generated in a given spawn.
    Rarity rarity;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using GenerationValuesMap = std::map<std::string, GenerationValues>;
