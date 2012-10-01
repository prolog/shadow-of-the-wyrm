#pragma once
#include "common.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

template<class T>
class Range
{
  public:
    Range(const T& new_min, const T& new_max)
    : min(new_min), max(new_max) {}

    void set_min(const T& new_min) { min = new_min; }
    int get_min() const { return min; }

    void set_max(const T& new_max) { max = new_max; }
    int get_max() const { return max; }

  protected:
    T min;
    T max;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & min & max;
    }
};

