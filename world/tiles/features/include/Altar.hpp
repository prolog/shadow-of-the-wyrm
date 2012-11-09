#pragma once
#include "Feature.hpp"

class Altar : public Feature
{
  public:
    Altar(const std::string& new_deity_id, const MaterialType new_material);
    virtual ~Altar() {};

    virtual bool can_offer() const;

    virtual bool handle();
    virtual bool kick();
    virtual bool offer();

    virtual std::string get_deity_id() const;
    
    virtual uchar get_symbol() const;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);
        
  protected:
    std::string deity_id;

  private:
    ClassIdentifier internal_class_identifier() const;
};
