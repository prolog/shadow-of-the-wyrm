#pragma once
#include "Feature.hpp"

class Altar : public Feature
{
  public:
    Altar(const std::string& new_deity_id, const MaterialType new_material);
    virtual ~Altar() {};
    virtual bool operator==(const Altar& altar) const;

    virtual bool can_offer() const override;

    virtual bool handle(std::shared_ptr<Tile>, std::shared_ptr<Creature>) override;
    virtual bool kick() override;
    virtual bool offer() override;

    virtual std::string get_deity_id() const;
    
    virtual uchar get_symbol() const override;

    virtual float get_piety_loss_multiplier() const override;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;
        
  protected:
    std::string deity_id;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
