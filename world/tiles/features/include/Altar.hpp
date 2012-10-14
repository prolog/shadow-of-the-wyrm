#pragma once
#include "Feature.hpp"

class Altar : public Feature
{
  public:
    Altar(const std::string& new_deity_id, MaterialPtr new_material);
    virtual ~Altar() {};

    virtual bool can_offer() const;

    virtual bool handle();
    virtual bool kick();
    virtual bool offer();
    
    virtual uchar get_symbol() const;
        
  protected:
    std::string deity_id;
};
