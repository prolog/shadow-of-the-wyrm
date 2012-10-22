#pragma once
#include <string>
#include "common.hpp"
#include "ISerializable.hpp"

// Depth is used to represent the character's general location in the
// world.  Each integer value represents 25 feet above or below ground.
class Depth : public ISerializable
{
  public:
    Depth();
    Depth(const int cur, const int max);

    void set_current(const int new_current);
    int get_current() const;

    void set_maximum(const int new_maximum);
    int get_maximum() const;

    std::string str() const;

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

  protected:
    // Negative depths: dungeons, caverns, etc.
    // Positive depths: towers, castles, etc.
    int current, maximum;
    static int DEPTH_MULTIPLIER;

  private:
    ClassIdentifier internal_class_identifier() const;
};

