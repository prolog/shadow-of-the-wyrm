#pragma once
#include <boost/serialization/base_object.hpp>
#include "ISeason.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class Spring : public ISeason
{
  public:
    Spring();
    
    Season get_season() const;
    std::string get_description_sid() const;
    std::string get_new_season_message_sid() const;

    Season get_previous_season() const;
    Season get_next_season() const;
    
  protected:
    void initialize_months();

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<ISeason>(*this);
    }
};
