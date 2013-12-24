#pragma once
#include <unordered_map>
#include "CreatureFeatures.hpp"
#include "ISerializable.hpp"

// I can't decide whether it's sad or awesome when, two and a half years
// into writing my roguelike, I'm busy adding a mechanic for measuring
// blood alcohol content, rather than defining enough content to actually
// release this damn thing.
class Blood : public ISerializable
{
  public:
    // Need a default version for serialization.
    Blood();

    // A creature's size determines the number of litres of blood
    Blood(CreatureSize size);

    bool operator==(const Blood& b) const;

    void set_litres(const float new_litres);
    float get_litres() const;

    void increment_grams_alcohol(const float incr_amount);
    void decrement_grams_alcohol(const float decr_amount);
    void set_grams_alcohol(const float new_grams_alcohol);
    float get_grams_alcohol() const;

    // Don't set blood alcohol content directly - this is calculated when 
    // setting grams of alcohol in the blood.
    float get_blood_alcohol_content() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    void initialize_litres_by_size_map();
    void calculate_blood_alcohol_content();

    float litres;
    float grams_alcohol;
    float blood_alcohol_content;
    static std::unordered_map<CreatureSize, float> litres_by_size_map;
    const static float DEFAULT_LITRES_OF_BLOOD;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

