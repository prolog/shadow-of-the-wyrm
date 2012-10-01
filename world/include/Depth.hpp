#pragma once
#include <string>
#include "common.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

// Depth is used to represent the character's general location in the
// world.  Each integer value represents 25 feet above or below ground.
class Depth
{
  public:
    Depth();
    Depth(const int cur, const int max);

    void set_current(const int new_current);
    int get_current() const;

    void set_maximum(const int new_maximum);
    int get_maximum() const;

    std::string str() const;

  protected:
    // Negative depths: dungeons, caverns, etc.
    // Positive depths: towers, castles, etc.
    int current, maximum;
    static const int DEPTH_MULTIPLIER;

  private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & current & maximum & const_cast<int&>(DEPTH_MULTIPLIER);
    }
};

