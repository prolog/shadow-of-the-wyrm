#pragma once
#include <string>
#include <boost/shared_ptr.hpp>
#include "Colours.hpp"
#include "ISerializable.hpp"
#include "MaterialTypes.hpp"

enum MaterialType;

class Material : public ISerializable
{
  public:
    virtual ~Material() {};

    // The type of the material
    virtual MaterialType get_type() const = 0;
    
    // The name of the material
    virtual std::string get_name_sid() const = 0;

    // The material's properties when exposed to the appropriate
    // damage type.
    virtual bool get_is_flammable() const = 0;
    virtual bool get_is_explosive() const = 0;
    virtual bool get_is_corrodible() const = 0;
    virtual bool get_can_rust() const = 0;
    
    // The colour of the material, for use in text-based displays.
    virtual Colour get_colour() const;
    
    virtual Material* clone() = 0;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<Material> MaterialPtr;
