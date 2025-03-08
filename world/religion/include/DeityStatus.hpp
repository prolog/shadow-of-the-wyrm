#pragma once
#include "ISerializable.hpp"
#include "ChampionTypes.hpp"

class DeityStatus : public ISerializable
{
  public:
    DeityStatus();
    ~DeityStatus();
    bool operator==(const DeityStatus& status) const;
    
    void set_piety(const int new_piety);
    int get_piety() const;
    void increment_piety(const int inc_amount);
    void decrement_piety(const int dec_amount);

    void set_piety_regen_bonus(const int new_piety_regen_bonus);
    int get_piety_regen_bonus() const;

    void set_champion_type(const ChampionType new_champion_type);
    ChampionType get_champion_type() const;

    void set_null(const bool new_null);
    bool get_null() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;
    
  protected:
    int piety; // Base relations with the deity
    int piety_regen_bonus; // Per-tick bonus for regenerating piety - higher is better
    ChampionType champion_type;
    bool null; // Does this represent a deity for which piety shouldn't apply (ie, godlessness)

  private:
    ClassIdentifier internal_class_identifier() const override;
};
