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

class Weight
{
  public:
    Weight();
    ~Weight();

    void set_weight(const uint ounces);
    void set_weight(const uint pounds, const uint ounces);
    uint get_weight() const;
    double get_weight_in_lbs() const;
    
    static uint get_weight_in_oz_given_lbs(const uint pounds);
    
    std::string str() const;

  protected:
    uint ounces;

  private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & ounces;
    }
};
