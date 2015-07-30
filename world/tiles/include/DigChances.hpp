#pragma once
#include "ISerializable.hpp"

class DigChances : public ISerializable
{
  public:
    DigChances();
    DigChances(const int new_pct_chance_undead, const int new_pct_chance_item);
	bool DigChances::operator==(const DigChances& dc) const;

    void set_pct_chance_undead(const int new_pct_chance_undead);
    int get_pct_chance_undead() const;

    void set_pct_chance_item(const int new_pct_chance_item);
    int get_pct_chance_item() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream);

  protected:
    int pct_chance_undead;
    int pct_chance_item;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

