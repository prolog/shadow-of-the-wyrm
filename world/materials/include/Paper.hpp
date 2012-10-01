#pragma once
#include <boost/serialization/base_object.hpp>
#include "Material.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class Paper : public Material
{
  public:
    MaterialType get_type() const;
    std::string get_name_sid() const;

    bool get_is_flammable() const;
    bool get_is_explosive() const;
    bool get_is_corrodible() const;
    bool get_can_rust() const;
    
    virtual Colour get_colour() const;
    
    Material* clone();

  private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Material>(*this);
    }
};
