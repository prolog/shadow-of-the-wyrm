#pragma once
#include "common.hpp"
#include "Range.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class AgeInfo
{
  public:
    AgeInfo();
    AgeInfo(const Range<uint>& min, const Range<uint>& max);

    void set_starting_age(const Range<uint>& new_starting_age);
    Range<uint> get_starting_age() const;

    void set_maximum_age(const Range<uint>& new_maximum_age);
    Range<uint> get_maximum_age() const;

  protected:
    Range<uint> starting_age;
    Range<uint> maximum_age;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & starting_age & maximum_age;
    }
};

