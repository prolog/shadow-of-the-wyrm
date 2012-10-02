#pragma once
#include <boost/serialization/base_object.hpp>
#include "Feature.hpp"
#include "IOfferable.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class Altar : public Feature, public IOfferable
{
  public:
    Altar(const std::string& new_deity_id, MaterialPtr new_material);
    virtual ~Altar() {};

    virtual bool handle();
    virtual bool kick();
    virtual bool offer();
    
    virtual uchar get_symbol() const;
        
  protected:
    std::string deity_id;

  private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Feature>(*this);
      ar & boost::serialization::base_object<IOfferable>(*this);
      ar & deity_id;
    }
};
