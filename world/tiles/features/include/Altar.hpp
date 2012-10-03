#pragma once
#include "Feature.hpp"
#include "IOfferable.hpp"

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
};
