#pragma once
#include "ISerializable.hpp"
#include "ChampionTypes.hpp"

class DeityStatus : public ISerializable
{
  public:
    DeityStatus();
    ~DeityStatus();
    virtual bool operator==(const DeityStatus& status) const;
    
    void set_piety(const int new_piety);
    int get_piety() const;
    void increment_piety(const int inc_amount);
    void decrement_piety(const int dec_amount);

    void set_champion_type(const ChampionType new_champion_type);
    ChampionType get_champion_type() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;
    
  protected:
    int piety;
    ChampionType champion_type;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
