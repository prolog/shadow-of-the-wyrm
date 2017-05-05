#pragma once
#include <string>
#include "common.hpp"
#include "ISerializable.hpp"

// Depth is used to represent the character's general location in the
// world.  Each integer value represents 50 feet above or below ground.
class Depth : public ISerializable
{
  public:
    Depth();
    Depth(const int cur, const int min, const int max, const int increment);
    bool operator==(const Depth& d) const;

    void set_current(const int new_current);
    int get_current() const;

    void set_minimum(const int new_minimum);
    int get_minimum() const;

    void set_maximum(const int new_maximum);
    int get_maximum() const;

    void set_increment(const int new_increment);
    int get_increment() const;

    std::string str() const;

    Depth lower() const;
    Depth higher() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    // Negative depths: dungeons, caverns, etc.
    // Positive depths: towers, castles, etc.
    int current, minimum, maximum, increment;
    static int DEPTH_MULTIPLIER;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

