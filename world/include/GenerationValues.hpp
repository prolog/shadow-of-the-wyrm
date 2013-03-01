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
    bool operator==(const GenerationValues& cgv);

    void set_current(const int new_current);
    int incr_current();
    int get_current() const;

    void set_maximum(const int new_maximum);
    int get_maximum() const;
    bool is_maximum_reached() const;

    void set_danger_level(const uint new_danger_level);
    uint get_danger_level() const;
    
    void set_rarity(const Rarity new_rarity);
    Rarity get_rarity() const;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  protected:
    // The current number that has been generated.
    int current;

    // The maximum number that can be generated, if non-negative.  If negative, ignored.
    int maximum;

    // The "danger level" at which the entity may start appearing,
    // if it is not out of depth/danger-depth.
    uint danger_level;

    // The more rare something is, the less chance of it getting generated in a given spawn.
    Rarity rarity;

  private:
    ClassIdentifier internal_class_identifier() const;
};

typedef std::map<std::string, GenerationValues> GenerationValuesMap;
