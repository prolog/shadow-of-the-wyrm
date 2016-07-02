#pragma once
#include "ISerializable.hpp"
#include <string>
#include <vector>

class DigChances : public ISerializable
{
  public:
    DigChances();
    DigChances(const int new_pct_chance_undead, const int new_pct_chance_item, const std::vector<std::string>& new_item_ids);

  	bool DigChances::operator==(const DigChances& dc) const;

    void set_pct_chance_undead(const int new_pct_chance_undead);
    int get_pct_chance_undead() const;

    void set_pct_chance_item(const int new_pct_chance_item);
    int get_pct_chance_item() const;

    void set_item_ids(const std::vector<std::string>& new_item_ids);
    std::vector<std::string> get_item_ids() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream);

  protected:
    int pct_chance_undead;
    int pct_chance_item;
    std::vector<std::string> item_ids;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

