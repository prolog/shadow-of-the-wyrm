#pragma once
#include <string>
#include "ISerializable.hpp"

class HungerClock : public ISerializable
{
  public:
    HungerClock();

    void set_requires_food(const bool requires_food);
    bool get_requires_food() const;

    // Can be "Stuffed", "Full", "" (neither full nor hungry), "Hungry",
    // or "Starving!"
    // std::string get_hunger_level_description() const;

    bool is_stuffed() const;
    bool is_full() const;
    bool is_hungry() const;
    bool is_starving() const;
    bool is_dead() const;

    void set_hunger(const int new_hunger_level);
    int get_hunger() const;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  protected:
    bool requires_food;
    int hunger;

  private:
    ClassIdentifier internal_class_identifier() const;
};

